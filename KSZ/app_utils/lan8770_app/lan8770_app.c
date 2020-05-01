//Version: 0.3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>

#include <libmnl/libmnl.h>
#include <linux/genetlink.h>

//#define DEBUG

static int phynl_fam;
static int reg_value=0;
static int seq_num=0;
static int mcgroup_id;
static pthread_mutex_t gmu;

#define LINK_DOWN 0
#define LINK_UP 1

typedef enum {
	CABLE_OK=0,
	OPEN_WIRE,
	SHORT_CIRCUITED,
	DIAGNOSTIC_ERROR,
} CABLE_DIAG;

enum {
	PHYNL_CMD_NOOP,
	PHYNL_CMD_EVENT,	/* only for notifications */
	PHYNL_CMD_RDWR_REG, //PHYNL_CMD_WAKE,
	PHYNL_CMD_SLEEP,

	__PHYNL_CMD_CNT,
	PHYNL_CMD_MAX = (__PHYNL_CMD_CNT - 1)
};

enum {
	PHYNL_ATTR_NOOP,
	PHYNL_ATTR_REGACCESS,//WAKE_ATTR_PHYACCESS,	/* phyaccess nested types */
	WAKE_ATTR_NOTIFICATION,
	__PHYNL_ATTR_CNT,
	PHYNL_ATTR_MAX = (__PHYNL_ATTR_CNT - 1)
};

/* phyaccess nested types */
#define	PHYACC_ATTR_MODE_READ		0
#define	PHYACC_ATTR_MODE_WRITE		1
#define PHYACC_ATTR_MODE_MODIFY		2

#define	PHYACC_ATTR_BANK_SMI		0
#define	PHYACC_ATTR_BANK_MISC		1
#define	PHYACC_ATTR_BANK_PCS		2
#define	PHYACC_ATTR_BANK_AFE		3
#define	PHYACC_ATTR_BANK_DSP		4
#define	PHYACC_ATTR_BANK_INSTRUMENT	5

enum {
	PHYACC_ATTR_NOOP,
	PHYACC_ATTR_IFNAME,
	PHYACC_ATTR_MODE,
	PHYACC_ATTR_BANK_ADDR,
	PHYACC_ATTR_OFFSET_ADDR,
	PHYACC_ATTR_VAL,

	__PHYACC_ATTR_CNT,
	PHYACC_ATTR_MAX = (__PHYACC_ATTR_CNT - 1)
};

#define	WAKENOTI_ATTR_STATUS_OK		0
#define	WAKENOTI_ATTR_STATUS_ABORT	1
#define	WAKENOTI_ATTR_STATUS_FAILURE	2

enum {
	WAKENOTI_ATTR_NOOP,
	WAKENOTI_ATTR_STATUS,

	__WAKENOTI_ATTR_CNT,
	WAKENOTI_ATTR_MAX = (__WAKENOTI_ATTR_CNT - 1)
};

struct access_ereg_val {
	int  mode;
	int  bank;
	unsigned short offset;
	unsigned short val;
	unsigned short mask;
};

static int cmd_notification_cb(const struct nlmsghdr *nlhdr, void *data)
{
	struct nlattr *attr;
	int type;
	int ret=-1;
	pthread_mutex_lock(&gmu);
	mnl_attr_for_each(attr, nlhdr, GENL_HDRLEN) {
		type = mnl_attr_get_type(attr);
		if (type == WAKE_ATTR_NOTIFICATION) {
			struct nlattr *nestattr;
			int nesttype;
			/* do nest decoding */
			mnl_attr_for_each_nested(nestattr, attr) {
				nesttype = mnl_attr_get_type(nestattr);
				if (nesttype == WAKENOTI_ATTR_STATUS) {
					printf("got WAKE NOTIFICATION : %d MNL_CB_OK=%d\n", mnl_attr_get_u32(nestattr),MNL_CB_OK);
					fflush(stdout);
					ret= MNL_CB_OK;
				}
			}
		}
	}

	pthread_mutex_unlock(&gmu);
	return ret;

}

static int cmd_rdwr_reg_cb /*cmd_wake_cb*/(const struct nlmsghdr *nlhdr, void *data)
{
	struct nlattr *attr;
	int type;
	pthread_mutex_lock(&gmu);
	mnl_attr_for_each(attr, nlhdr, GENL_HDRLEN) {
		type = mnl_attr_get_type(attr);

		if (type == PHYNL_ATTR_REGACCESS/*WAKE_ATTR_PHYACCESS*/) {
			struct nlattr *nestattr;
			int nesttype;
			/* do nest decoding */
			mnl_attr_for_each_nested(nestattr, attr) {
				nesttype = mnl_attr_get_type(nestattr);
				switch (nesttype) {
				case PHYACC_ATTR_MODE:
					//printf("PHY Access Mode : %s\n",
					//(mnl_attr_get_u16(nestattr) == PHYACC_ATTR_MODE_READ) ? "Read" : "Write");
					break;
				case PHYACC_ATTR_BANK_ADDR:
					//printf("PHY Bank Addr : %d\n", mnl_attr_get_u16(nestattr));
					break;
				case PHYACC_ATTR_OFFSET_ADDR:
					//printf("PHY Offset Addr : 0x%x\n", mnl_attr_get_u16(nestattr));
					break;
				case PHYACC_ATTR_VAL:
					reg_value=mnl_attr_get_u16(nestattr);
					//printf("PHY value : 0x%04x\n", reg_value);
					break;
				}
			}
		}
	}
	pthread_mutex_unlock(&gmu);
	return MNL_CB_OK;
}

struct attr_tb_info {
	const struct nlattr **tb;
	unsigned int max_type;
};

int attr_cb(const struct nlattr *attr, void *data)
{
	const struct attr_tb_info *tb_info = data;
	int type = mnl_attr_get_type(attr);

	if (type >= 0 && type <= tb_info->max_type)
		tb_info->tb[type] = attr;

	return MNL_CB_OK;
}

static void find_monitor_group(struct nlattr *nest)
{
	const struct nlattr *grp_tb[CTRL_ATTR_MCAST_GRP_MAX + 1] = {};
	struct attr_tb_info grp_tb_info = { (grp_tb), (MNL_ARRAY_SIZE(grp_tb) - 1) };
	struct nlattr *grp_attr;
	int ret;

	mnl_attr_for_each_nested(grp_attr, nest) {
		ret = mnl_attr_parse_nested(grp_attr, attr_cb, &grp_tb_info);
		if (ret < 0)
			return;
		if (!grp_tb[CTRL_ATTR_MCAST_GRP_NAME] ||
			!grp_tb[CTRL_ATTR_MCAST_GRP_ID])
			continue;

		mcgroup_id = mnl_attr_get_u32(grp_tb[CTRL_ATTR_MCAST_GRP_ID]);
		printf("GroupID = %d\n", mcgroup_id);
		printf("GroupName = %s\n", mnl_attr_get_str(grp_tb[CTRL_ATTR_MCAST_GRP_NAME]));
		return;
	}
}

static int ethnl_family_cb(const struct nlmsghdr *nlhdr, void *data)
{
	struct nlattr *attr;
	int type;

	phynl_fam = 0;
	pthread_mutex_lock(&gmu);
	mnl_attr_for_each(attr, nlhdr, GENL_HDRLEN) {
		type = mnl_attr_get_type(attr);
		if (type == CTRL_ATTR_FAMILY_ID) {
			phynl_fam = mnl_attr_get_u16(attr);
		}
		if (type == CTRL_ATTR_MCAST_GROUPS) {
			find_monitor_group(attr);
		}
	}
	pthread_mutex_unlock(&gmu);
	return (phynl_fam ? MNL_CB_OK : MNL_CB_ERROR);
}

static void parse_one_mc_group(struct nlattr *attr)
{
	/*
	struct nlattr *tb[CTRL_ATTR_MCAST_GRP_MAX + 1];

	mnl_attr_parse_nested(attr, ethnl_family_cb, NULL);

	if (tb[CTRL_ATTR_MCAST_GRP_NAME] && tb[CTRL_ATTR_MCAST_GRP_ID]) {
		printf("%s ->%d\n",
				mnl_attr_get_str(tb[CTRL_ATTR_MCAST_GRP_NAME]),
				mnl_attr_get_u32(tb[CTRL_ATTR_MCAST_GRP_ID]));
	}
	*/
}

static void parse_mc_grps(struct nlattr *nested)
{
	struct nlattr *attr;
	const char *mcast_grp_name;
	int mcast_grp_id;

	mnl_attr_for_each_nested(attr, nested)
	parse_one_mc_group(attr);
}

static int access_reg(struct mnl_socket *nl, int family, const char * ifname, int mode, int bank, int offset, int value)
{
	char buf[256];/*don't use MNL_SOCKET_BUFFER_SIZE, it may be too big for function stack,
	it defined in libmnl.h ->define MNL_SOXKET_BUFFER_SIZE (sysconf(_SC_PAGESIZE)< 8192L ? sysconf(_SC_PAGESIZE) : 8291L)*/
	struct nlmsghdr *nlh;
	struct genlmsghdr *genl;
	int hdrsize,len,ret;
	struct nlattr *nest;

	memset(buf, 0, sizeof(buf));

	hdrsize = sizeof(struct genlmsghdr);
	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type =  family;	/* get value from step 1 */
	nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK;
	nlh->nlmsg_seq = ++seq_num;

	hdrsize = sizeof(struct genlmsghdr);
	genl = mnl_nlmsg_put_extra_header(nlh, hdrsize);
	genl->cmd = PHYNL_CMD_RDWR_REG; //PHYNL_CMD_WAKE;	/* cmd is defined in module */
	genl->version = 1;

	/* start nest attrs */
	nest = mnl_attr_nest_start(nlh, PHYNL_ATTR_REGACCESS/*WAKE_ATTR_PHYACCESS*/);
	if (!nest) {
		perror("mnl_attr_nest_start");
		exit(EXIT_FAILURE);
	}

	/* pass device name to kernel */
	mnl_attr_put_strz(nlh, PHYACC_ATTR_IFNAME, ifname/*argv[1]*/);
	/* phy access mode */
	mnl_attr_put_u16(nlh, PHYACC_ATTR_MODE, mode/*PHYACC_ATTR_MODE_READ*/);
	/* set phy bank */
	mnl_attr_put_u16(nlh, PHYACC_ATTR_BANK_ADDR, bank/*PHYACC_ATTR_BANK_SMI*/);
	/* set phy addr */
	mnl_attr_put_u16(nlh, PHYACC_ATTR_OFFSET_ADDR, offset/*0x16*/);

	if(mode==PHYACC_ATTR_MODE_WRITE)
		mnl_attr_put_u16(nlh, PHYACC_ATTR_VAL, value/*0x5678*/);

	/* end nest attrs */
	mnl_attr_nest_end(nlh, nest);

	if (mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) < 0) {
		perror("mnl_socket_sendto");
		exit(EXIT_FAILURE);
	}

	while ((len = mnl_socket_recvfrom(nl, buf, sizeof(buf))) > 0) {
		ret = mnl_cb_run(buf, len, seq_num, 0, cmd_rdwr_reg_cb,/*cmd_wake_cb,*/ NULL);
		if (ret <= 0)
			break;
	}

	if (ret == -1) {
		perror("fatal error: access_reg failed");
		exit(EXIT_FAILURE);
	}
	return reg_value;
}

static void ReadModWriteRegister(struct mnl_socket *nl, int family, const char * ifname, int bank, int regAddr, unsigned short data, unsigned short mask)
{
	unsigned short regData = 0x0;
	regData=access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, bank, regAddr, 0);
	regData = (regData & (mask ^ 0xFFFF)) | data;
	access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, bank, regAddr, regData);
}

static void phy_init(struct mnl_socket *nl, int family, const char * ifname)
{
	static const struct access_ereg_val init[] = {
		/* TX Amplitude = 5 */
		{PHYACC_ATTR_MODE_MODIFY, PHYACC_ATTR_BANK_AFE, 0x0B,
		 0x000A, 0x001E},
		/* Clear SMI interrupts */
		{PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_SMI, 0x18,
		 0, 0},
		/* Clear MISC interrupts */
		{PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_MISC, 0x08,
		 0, 0},
		/* Turn on TC10 Ring Oscillator (ROSC) */
		{PHYACC_ATTR_MODE_MODIFY, PHYACC_ATTR_BANK_MISC, 0x20,
		 0x0020, 0x0020},
		/* WUR Detect Length to 1.2uS, LPC Detect Length to 1.09uS */
		{PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_PCS, 0x20,
		 0x283C, 0},
		/* Wake_In Debounce Length to 39uS, Wake_Out Length to 79uS */
		{PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_MISC, 0x21,
		 0x274F, 0},
		/* Enable Auto Wake Forward to Wake_Out, ROSC on, Sleep,
		 * and Wake_In to wake PHY
		 */
		{PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_MISC, 0x20,
		 0x80A7, 0},
		/* Enable WUP Auto Fwd, Enable Wake on MDI, Wakeup Debouncer
		 * to 128 uS
		 */
		{PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_MISC, 0x24,
		 0xF110, 0},
		/* Enable HW Init */
		{PHYACC_ATTR_MODE_MODIFY, PHYACC_ATTR_BANK_SMI, 0x1A,
		 0x0100, 0x0100},
	};
	int rc, i;

	/* Start manual initialization procedures in Managed Mode */
	ReadModWriteRegister(nl,phynl_fam,ifname, PHYACC_ATTR_BANK_SMI,
					0x1a, 0x0000, 0x0100);
	if (rc < 0)
		printf ("phy init error %x\n", rc);	

	/* Soft Reset the SMI block */
	ReadModWriteRegister(nl,phynl_fam,ifname, PHYACC_ATTR_BANK_SMI,
					0x00, 0x8000, 0x8000);
	if (rc < 0)
		printf ("phy init error %x\n", rc);	

	/* Wait for the self-clearing bit to be cleared */
	sleep(1);
	rc = access_reg(nl,phynl_fam,ifname, PHYACC_ATTR_MODE_READ,
			 PHYACC_ATTR_BANK_SMI, 0x00, 0);
	if ((rc & 0x8000) != 0)
		printf ("phy init error reset timeout\n");	

	/* PHY Initialization */
	for (i = 0; i < (sizeof(init) / sizeof(init[0])); i++) {
		if (init[i].mode == PHYACC_ATTR_MODE_MODIFY) {
			ReadModWriteRegister(nl,phynl_fam,ifname, init[i].bank,
							init[i].offset,
							init[i].val,
							init[i].mask);
		} else {
			access_reg(nl,phynl_fam,ifname, init[i].mode, init[i].bank, init[i].offset, init[i].val);
		}
		if (rc < 0)
			printf ("phy init error %x\n", rc);	
	}
	printf ("phy init done %d registers after soft reset\n", i);	
}

static void * notify_thread(void * p)
{
	int i=0,len,ret;
	struct mnl_socket *nl =(struct mnl_socket *)p;
	char buf[256];/*cannot use MNL_SOCKET_BUFFER_SIZE, it may be too big for thead stack,
	it defined in libmnl.h ->define MNL_SOXKET_BUFFER_SIZE (sysconf(_SC_PAGESIZE)< 8192L ? sysconf(_SC_PAGESIZE) : 8291L)*/
	printf("+notify thread created nl=0x%lx \n", (unsigned long)nl);
	usleep(300*1000);
	do {

		len = mnl_socket_recvfrom(nl, buf, sizeof(buf));
		if (len < 0)
			exit;

		ret = mnl_cb_run(buf, len, 0, 0, cmd_notification_cb, NULL);
		if (ret <= 0)
			break;
	} while (1);

	return NULL;
}

static int get_link_status(struct mnl_socket *nl, int family,const char * ifname)
{

	unsigned short reg_0A_data, reg_11_data, pcs_descram_st;
	/* bit 12 remote recceiver status; bit 13 local receiver status */
	reg_0A_data=access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_SMI, 0xA,0);
	/*bit 0 link status; bit 2:1 tx mode status; bit 3 scrambler lock status*/
	reg_11_data=access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_SMI, 0x11,0);
	/* get pcs descrambler state */
	access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_SMI, 0x12,9<<11);//WriteRegister(0x12, 9 << 11);
	pcs_descram_st = access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_PCS, 0x16,0);//ReadRegister(2, 0x16);
	pcs_descram_st = (pcs_descram_st >> 2) & 0x7;


	if(((reg_0A_data & 0x3000) == 0x3000) && ((reg_11_data & 0x0D) == 0x0D)) {
		if(pcs_descram_st == 0x0) {
			return LINK_DOWN;
		} else {
			return LINK_UP;
		}
	} else {
		return LINK_DOWN;
	}

}


static unsigned long long get_current_time()
{
	struct timeval te;
	unsigned long long milliseconds;
	gettimeofday(&te,NULL);
	milliseconds=te.tv_sec*1000 + te.tv_usec/1000;
	return milliseconds;
}

/*
 * Execute the Cable Diagnostic tests, and returns a string with the state of the cable.
 */
CABLE_DIAG get_cable_diagnostic(struct mnl_socket *nl, int family, const char * ifname)
{
	bool bDone = false, diagTimeout = false, bFault = false;

	unsigned long diagWait, currentTick;
	unsigned short gainIdxHybrid = 0, posPeakTimeHybrid = 0;
	unsigned short gainIdx = 0, posPeak = 0, negPeak = 0, posPeakTime = 0, negPeakTime = 0;
	unsigned short posPeakCycleHybrid = 0, posPeakInPhasesHybrid = 0, posPeakPhaseHybrid = 0;
	unsigned short posPeakCycle = 0, posPeakInPhases = 0, posPeakPhase = 0, negPeakCycle = 0, negPeakInPhases = 0, negPeakPhase = 0;
	float wavePropagationVelocity = 0.6811 * 2.9979;
	unsigned short detect = -1;
	float distance = -1;
	unsigned short noiseMargin = 20, timeMargin = 89, maxDistance = 35, jitterVariation = 30;
	unsigned short minTimeDifference = 96, maxTimeDifference = 96 + timeMargin;
	unsigned short tempReg = 0;

	// IOP_33 debug, increase maxDistance by 10
	maxDistance = 45;

	 // Reset(HARD_RESET);
	 /*soft reset */
   ReadModWriteRegister(nl, family, ifname, PHYACC_ATTR_BANK_SMI,0x0,0x8000,0x8000);
	 sleep(1);/*sleep 1 second */
	 //ReadModWriteRegister(0, 0x1A, 0x0100, 0x0100);
	 ReadModWriteRegister(nl, family, ifname, PHYACC_ATTR_BANK_SMI,0x1A,0x0100,0x0100);
	
	 // direct bank 0 access
	 tempReg = 0;
	//ReadRegister(0x00, &tempReg);
   tempReg=access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_SMI, 0x00,0);

	if (tempReg != 0x2100) {																								// check if part is alive - if not, return diagnostic error
		return DIAGNOSTIC_ERROR;
	}
	// direct bank 0 access
	tempReg = 0;
	//D ReadRegister(0x0A, &tempReg);
  tempReg=access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_SMI, 0x0A,0);
   
	if ((tempReg & 0x4000) != 0x4000) {
		printf("DUT is Slave \n");																				// master/slave specific writes
		// ReadModWriteRegister(3, 0x0E, 0x0005, 0x0007);
		ReadModWriteRegister(nl, family, ifname, PHYACC_ATTR_BANK_AFE,0x0E,0x0005,0x0007);
		// ReadModWriteRegister(0, 0x1A, 0x0008, 0x0008);
		ReadModWriteRegister(nl, family, ifname, PHYACC_ATTR_BANK_SMI,0x1A,0x8,0x8);
	}
	else {
		printf("DUT is Master \n");
		// ReadModWriteRegister(0, 0x10, 0x0000, 0x0040);
		ReadModWriteRegister(nl, family, ifname, PHYACC_ATTR_BANK_SMI,0x10,0x8,0x40);
	}

	//D WriteRegister(4, 93, 0);																													// DSP configuration
	//D WriteRegister(4, 94, 10);
	//D WriteRegister(4, 95, 90);
	//D WriteRegister(4, 92, 60);
	//D WriteRegister(4, 79, 31);
  access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 93, 0); /*min wait*/
  access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 94, 10);/*max wait*/
  access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 95, 90);/*pulse cycle*/
  access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 92, 60);/*cbl diag thresh*/
  access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 79, 31);/* max gain*/

	//ReadModWriteRegister(4, 55, 0x0000, 0x0038);																					// clock align for each iteration
  ReadModWriteRegister(nl, family, ifname, PHYACC_ATTR_BANK_DSP,55,0x0,0x0038);/*clock align for each iteration*/
 
	gainIdxHybrid = 0;			// don't really need this line since it defaults to 0
	posPeakInPhasesHybrid = 0;	// don't really need this line since it defaults to 0

	// BLOCK_DELAY(50);																																   // wait 50ms
  usleep(50*1000);
	// WriteRegister(4, 94, 70);																												   // max cycle wait config
	access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 94, 70);/*max wait*/
	bDone = false;

	printf("starting Cable diagnostics \n");
	access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 90, 0x1);/* start cable diag*/

	while((access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_DSP, 90,0) & 0x02) !=0x02) {
		;
	}/* wait for cable diag to finish*/
	access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 90, 0x0);/* stop cable diag*/
	bDone=true;  

	gainIdx = access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_DSP, 151,0); //ReadRegister(4, 151);																											  // read non-hybrid results
	posPeak = access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_DSP, 153,0); //ReadRegister(4, 153);
	negPeak = access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_DSP, 154,0); //ReadRegister(4, 154);
	posPeakTime =access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_DSP, 156,0);// ReadRegister(4, 156);
	negPeakTime =access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_DSP, 157,0);// ReadRegister(4, 157);

	posPeakCycle = (posPeakTime >> 7) & 0x7F;																					   // calculate non-hybrid values
	posPeakPhase = posPeakTime & 0x7F;
	posPeakInPhases = (posPeakCycle * 96) + posPeakPhase;
	negPeakCycle = (negPeakTime >> 7) & 0x7F;
	negPeakPhase = negPeakTime & 0x7F;
	negPeakInPhases = (negPeakCycle * 96) + negPeakPhase;

	// process values
	if ((posPeakInPhases > negPeakInPhases) &&
		((posPeakInPhases - negPeakInPhases) >= minTimeDifference) &&
		((posPeakInPhases - negPeakInPhases) < maxTimeDifference) &&
		(posPeakInPhasesHybrid < posPeakInPhases) &&
		(posPeakInPhasesHybrid < (negPeakInPhases + jitterVariation))) {
		detect = 2;
		distance = (negPeakInPhases - posPeakInPhasesHybrid) * 156.2499 * 0.0001 * wavePropagationVelocity * 0.5;
	}
	else if ((negPeakInPhases > posPeakInPhases) &&
		((negPeakInPhases - posPeakInPhases) >= minTimeDifference) &&
		((negPeakInPhases - posPeakInPhases) < maxTimeDifference) &&
		(posPeakInPhasesHybrid < negPeakInPhases) &&
		(posPeakInPhasesHybrid < (posPeakInPhases + jitterVariation))) {
		detect = 1;
		distance = (posPeakInPhases - posPeakInPhasesHybrid) * 156.2499 * 0.0001 * wavePropagationVelocity * 0.5;
	}

	if ((posPeak > noiseMargin) && (negPeak > noiseMargin) && (distance < maxDistance) && (gainIdx >= 0)) {
		if ((detect == 1) || (detect == 2)) {
			bFault = true;
		}
	}

	if (!bFault) {
		detect = 0;
		distance = 0;
	}


	switch (detect) {
	case 0:
		return CABLE_OK;
		break;
	case 1:
		printf("Distance to the fault is %f meters \n", distance);
		return OPEN_WIRE;
		break;
	case 2:
		printf("Distance to the fault is %f meters \n", distance);
		return SHORT_CIRCUITED;
		break;
	default:
		return DIAGNOSTIC_ERROR;
	}

}

static unsigned char  get_sqi(struct mnl_socket *nl, int family, const char * ifname) {
	
	unsigned short rawTable[200] = {0};
	unsigned char  linkTable[200] = {1};
	unsigned short temp;
	float sqiAvg = 0, linkAvg = 0;
	int sqiNum;
	int linkTemp,i,j;
	bool writeSuccess;
	
	access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 0x04, 0x1D66);
	writeSuccess=(access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_DSP, 0x04, 0)==0x1D66)?true:false;
	if (writeSuccess)
		writeSuccess = access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 0x2E, 0x9572);
	// below effectively throws away first reading
	ReadModWriteRegister(nl, family, ifname, PHYACC_ATTR_BANK_DSP,0xD,0x01,0x01); 	/*update DSP d130/131*/
	usleep(50);/* required delay before reading DSP d131 otherwise it will return a high value on first read*/
	for (i = 0; i < 200; i++) {
		access_reg(nl, family, ifname, PHYACC_ATTR_MODE_WRITE, PHYACC_ATTR_BANK_DSP, 0x0D, 0x01);//an_write(descr, DSP, 0x0D, 0x0001, false);
		rawTable[i] = access_reg(nl, family, ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_DSP, 0x83, 0x0);//an_read(descr, DSP, 0x83);
		linkTable[i] = get_link_status(nl, family, ifname);;
		usleep(10);//delay_ms(5);
	}
	
	/*Sorting arrays*/
	
	for (i = 0; i < 200; i++) {
		for (j = 0; j < 200; j++) {
			if (rawTable[j] > rawTable[i]) {
				temp = rawTable[i];
				rawTable[i] = rawTable[j];
				rawTable[j] = temp;
				
				linkTemp = linkTable[i];
				linkTable[i] = linkTable[j];
				linkTable[j] = linkTemp;
			}
		}
	}
	
	/*Discarding outliers*/
	
	for (i = 0; i < 200; i++) {
		if ((i >= 40) && (i <= 160)) {
			sqiAvg += rawTable[i];
		}
		
		linkAvg += linkTable[i];
	}
	
	/*Calculating SQI number*/
	
	sqiAvg /= 120;
	linkAvg /= 200;
	
	if (sqiAvg >= 299) {
		sqiNum = 0;
	} else if ((sqiAvg <= 298) && (sqiAvg >=237)) {
		sqiNum = 1;
	} else if ((sqiAvg <= 236) && (sqiAvg >=189)) {
		sqiNum = 2;
	} else if ((sqiAvg <= 188) && (sqiAvg >=150)) {
		sqiNum = 3;
	} else if ((sqiAvg <= 149) && (sqiAvg >=119)) {
		sqiNum = 4;
	} else if ((sqiAvg <= 118) && (sqiAvg >=94)) {
		sqiNum = 5;
	} else if ((sqiAvg <= 93) && (sqiAvg >=75)) {
		sqiNum = 6;
	} else if ((sqiAvg <= 74) && (sqiAvg >=0)) {
		sqiNum = 7;
	} else {
		sqiNum = 8;
	}
	
	if (linkAvg != LINK_UP) {
		sqiNum = 0;
	}
	
	printf("result sqiNum =%d \n",sqiNum);
	return sqiNum;
}

static bool is_empty_line(const char * pin)
{
	while(*pin!='\0') {
		if(*pin==' ' || *pin=='\n' || *pin=='\r' || *pin=='\t') {
			pin++;
			continue;
		} else
			return false;
	}
	return true;
}

static char __1st_char(char * pin, char * * ppout )
{
	while(*pin!='\0') {
		if(*pin==' ' || *pin=='\t') {
			pin++;
		} else {
			*ppout=pin;
			return *pin;
		}
	}
	return '\0';
}

static void remove_newline(char * pin)
{
	while(*pin!='\0') {
		if(*pin=='\n' || *pin=='\r') {
			*pin='\0';
			return;
		}
		pin++;
	}
}

static bool cmd_process(char * pcmd,struct mnl_socket *nl, int family,const char * ifname)
{
	char s[32], *pout, c;
	int i,bank,offset,value,ret,mask;

	if(is_empty_line(pcmd))
		return true;

	c=__1st_char(pcmd,&pout);

	if(c=='#') /*comment line*/
		return true;
	pcmd=pout;
	remove_newline(pcmd);
	i=sscanf(pcmd,"%s %x %x ",&s[0], &bank, &offset);
	if(bank<0 || bank>5)
		goto ecmd;
	if(i !=3)
		goto ecmd;
	if(s[0]!='w' && s[0] !='r')
		goto ecmd;
	if(s[0]=='w') {
		i=sscanf(pcmd,"%s %x %x %x",&s[0], &bank, &offset,&value);
		if(i!=4)
			goto ecmd;
		printf("%s \n",pcmd);
		ret=access_reg(nl,family,ifname,PHYACC_ATTR_MODE_WRITE,bank,offset,value);
	} else {
		if(s[1]=='w') {
			i=sscanf(pcmd,"%s %x %x %x %x",&s[0], &bank, &offset,&value,&mask);
			if(i!=5)
				goto ecmd;
			printf("%s \n",pcmd);
			ReadModWriteRegister(nl, family, ifname, bank, offset, value, mask);
		} else {
			ret=access_reg(nl,family,ifname,PHYACC_ATTR_MODE_READ,bank,offset,0);
			printf("%s [value=0x%x]\n", pcmd,ret);
		}

	}
	return true;
ecmd:
	printf("syntax error: %s \n",pcmd);
	return false;
}

int main(int argc, char *argv[])
{
	struct mnl_socket *nl,*nl_notif;
	char buf[MNL_SOCKET_BUFFER_SIZE];
	struct nlmsghdr *nlh;
	struct genlmsghdr *genl;
	int ret, len, numbytes, hdrsize;
	unsigned int seq;
	struct nlattr *nest;
	pthread_t thread_id;


	char ifname[64], sbuf[128],c;
	if(argc != 2) {
		printf("syntax: lan8770_app DEVNAME \n" );
		return 0;
	}

	pthread_mutex_init(&gmu,NULL);
	strcpy(ifname,argv[1]);
	seq = time(NULL);
	seq_num=seq;
	/*
	 * step1 : find "microchipphy" netlink family and get family id
	 *
	 * This is a necessary init procedure before other calls to
	 * our own netlink module
	 */
	memset(buf, 0, sizeof(buf));
	nlh = mnl_nlmsg_put_header(buf);
	nlh->nlmsg_type = GENL_ID_CTRL;
	nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_ACK;
	nlh->nlmsg_seq = seq;

	hdrsize = sizeof(struct genlmsghdr);
	genl = mnl_nlmsg_put_extra_header(nlh, hdrsize);
	genl->cmd = CTRL_CMD_GETFAMILY;
	genl->version = 1;

	/* get genl family id */
	mnl_attr_put_strz(nlh, CTRL_ATTR_FAMILY_NAME, "microchipphy");

	nl = mnl_socket_open(NETLINK_GENERIC);
	if (nl == NULL) {
		perror("mnl_socket_open");
		exit(EXIT_FAILURE);
	}

	if (mnl_socket_bind(nl, 0, 0) < 0) {
		perror("mnl_socket_bind");
		exit(EXIT_FAILURE);
	}

	if (mnl_socket_sendto(nl, nlh, nlh->nlmsg_len) < 0) {
		perror("mnl_socket_sendto");
		exit(EXIT_FAILURE);
	}

	/* ethnl_family_cb is called and get phynl_fam */
	while ((len = mnl_socket_recvfrom(nl, buf, sizeof(buf))) > 0) {
		ret = mnl_cb_run(buf, len, seq, 0, ethnl_family_cb, NULL);
		if (ret <= 0)
			break;
	}

	if (ret == -1) {
		perror("error 1");
		exit(EXIT_FAILURE);
	}

	/* Add mcgroup_id of phy_monitor to Netlink membership */
	ret = mnl_socket_setsockopt(nl, NETLINK_ADD_MEMBERSHIP, &mcgroup_id, sizeof(mcgroup_id));
	if (ret < 0) {
		perror("mnl_socket_setscoketopt()");
		exit(ret);
	}

	nl_notif = mnl_socket_open(NETLINK_GENERIC);
	if (nl == NULL) {
		perror("mnl_socket_open");
		exit(EXIT_FAILURE);
	}

	if (mnl_socket_bind(nl_notif, 0, 0) < 0) {
		perror("mnl_socket_bind");
		exit(EXIT_FAILURE);
	}
	/* Add mcgroup_id of phy_monitor to Netlink membership */
	ret = mnl_socket_setsockopt(nl_notif, NETLINK_ADD_MEMBERSHIP, &mcgroup_id, sizeof(mcgroup_id));
	if (ret < 0) {
		perror("mnl_socket_setscoketopt()");
		exit(ret);
	}

	/*create a thread to wait notification*/
	pthread_create(&thread_id,NULL, notify_thread,nl_notif);

//	printf("++initialize the phy true=%d false=%d\n", true, false);
//	phy_init(nl,phynl_fam,ifname);

	printf("-------------------input the command index-----------------------------------\n\n");
	while(1) {
		int mask=0, tmp;
		int i,bank, offset, value;
		char s[64];
		FILE * fp;
		printf("\n");
		printf("(1) phy sleep \n");
		printf("(2) phy wake up\n");
		printf("(3) read wake register\n");
		printf("(4) read/write a register\n");
		printf("(5) cable diagnostic\n");
		printf("(6) run script file\n");
		printf("(7) get link status\n");
		printf("(8) get master/slave\n");
		printf("(9) set master/slave \n");
		printf("(a) soft reset\n");
		printf("(b) re-initialize phy\n");
		printf("(c) SQI test (method 1)\n");
		printf("(q) exit\n");
		printf(">");
		fgets(sbuf,sizeof(sbuf),stdin);
		sscanf(sbuf,"%c",&c);
		switch(c) {
		case '1':
			mask=0x1000;
			ret=access_reg(nl,phynl_fam,ifname,PHYACC_ATTR_MODE_READ,PHYACC_ATTR_BANK_SMI,0x10,0);
			tmp=(ret & (mask ^ 0xFFFF))|0x1000;
			ret=access_reg(nl,phynl_fam,ifname,PHYACC_ATTR_MODE_WRITE,PHYACC_ATTR_BANK_SMI,0x10,tmp);
			printf("sleep: write data=0x%x \n",tmp);
			break;

		case '2':
			mask=0x2000;
			ret=access_reg(nl,phynl_fam,ifname,PHYACC_ATTR_MODE_READ,PHYACC_ATTR_BANK_SMI,0x10,0);
			tmp=(ret & (mask ^ 0xFFFF))|0x2000;
			ret=access_reg(nl,phynl_fam,ifname,PHYACC_ATTR_MODE_WRITE,PHYACC_ATTR_BANK_SMI,0x10,tmp);
			printf("wake: write data=0x%x \n",tmp);
			break;

		case '3':
			ret=access_reg(nl,phynl_fam,ifname,PHYACC_ATTR_MODE_READ,PHYACC_ATTR_BANK_MISC,0x22,0);
			printf("misc 0x22 value=0x%x \n",ret);
			break;

		case '4':

xi:
			printf("syntax: r/w/rw bank(0-5) offset [value] [mask]\n");
			printf(">");
			fgets(sbuf,sizeof(sbuf),stdin);
			i=sscanf(sbuf,"%s %x %x ",&s[0], &bank, &offset);
			if(bank<0 || bank>5)
				goto xi;
			if(i !=3)
				goto xi;
			if(s[0]!='w' && s[0] !='r')
				goto xi;
			if(s[0]=='w') {
				i=sscanf(sbuf,"%s %x %x %x",&s[0], &bank, &offset,&value);
				if(i!=4)
					goto xi;
				printf("write bank=%d offset=0x%x value=0x%x\n",bank,  offset, value);
				ret=access_reg(nl,phynl_fam,ifname,PHYACC_ATTR_MODE_WRITE,bank,offset,value);
			} else {
				if(s[1]=='w') {
					i=sscanf(sbuf,"%s %x %x %x %x",&s[0], &bank, &offset,&value,&mask);
					printf("i=%d \n",i);
					if(i!=5)
						goto xi;
					printf("ReadModWrite bank=%d offset=0x%x value=0x%x mask=0x%x \n",bank,  offset, value, mask);
					ReadModWriteRegister(nl, phynl_fam, ifname, bank, offset, value, mask);
				} else {
					ret=access_reg(nl,phynl_fam,ifname,PHYACC_ATTR_MODE_READ,bank,offset,0);
					printf("readback bank=%d offset=0x%x value=0x%x \n",bank,offset, ret);
				}
			}

			break;

		case '5':
			ret=get_cable_diagnostic(nl,phynl_fam,ifname);
			if(ret==CABLE_OK)
				printf("Cable OK \n");
			else if(ret==OPEN_WIRE)
				printf("Open Wire \n");
			else if(ret==SHORT_CIRCUITED)
				printf("Short Circuit \n");
			else
				printf("diagnostic error \n");
			break;

		case '6':
			printf("input file name\n");
			printf(">");
			fgets(sbuf,sizeof(sbuf),stdin);
			remove_newline(sbuf);
			fp=fopen(sbuf,"rb");
			if(!fp)
				printf("failed to open file %s \n",sbuf);
			else {
				while(fgets(sbuf,sizeof(sbuf),fp)!=NULL) {
					if(cmd_process(sbuf,nl,phynl_fam,ifname)==false)
						break;
				}
				fclose(fp);
			}
			break;

		case '7':
			if(get_link_status(nl,phynl_fam,ifname)==LINK_UP)
				printf("Link is up\n");
			else
				printf("Link is down \n");
			break;

		case '8':
			if( (access_reg(nl,phynl_fam,ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_SMI, 0x0A, 0)& 0x4000) != 0x4000)
				printf("The DUT is slave\n");
			else
				printf("The DUT is master\n");
			break;
		case '9':
			if( (access_reg(nl,phynl_fam,ifname, PHYACC_ATTR_MODE_READ, PHYACC_ATTR_BANK_SMI, 0x0A, 0)& 0x4000) != 0x4000)
				printf("The DUT is slave\n");
			else
				printf("The DUT is master\n");
y1:
			printf("type(1) for master, (2) for slave\n");
			printf(">");
			fgets(sbuf,sizeof(sbuf),stdin);
			sscanf(sbuf,"%c",&c);
			switch(c) {
			case '1':
				ReadModWriteRegister(nl, phynl_fam, ifname,PHYACC_ATTR_BANK_SMI, 0x09, 0x1800, 0x1800);
				break;

			case '2':
				ReadModWriteRegister(nl, phynl_fam, ifname,PHYACC_ATTR_BANK_SMI, 0x09, 0x1000, 0x1800);
				break;

			default:
				goto y1;
			}
			/*need to do soft reset*/
			ReadModWriteRegister(nl, phynl_fam, ifname,PHYACC_ATTR_BANK_SMI,0x0,0x8000,0x8000);
			usleep(50*1000);
			break;

		case 'a':
			ReadModWriteRegister(nl, phynl_fam, ifname,PHYACC_ATTR_BANK_SMI,0x0,0x8000,0x8000);
			usleep(50*1000);
			printf("soft reset done\n");
			break;

		case 'b':
			phy_init(nl,phynl_fam,ifname);
			break;

		case 'c':
			get_sqi(nl,phynl_fam,ifname);
			break;

		case 'q':
			goto __exit;
			break;
		default:
			printf("unknow command\n");
			break;
		}

	}
__exit:
	pthread_cancel(thread_id);
	mnl_socket_close(nl);

	return 0;
}

