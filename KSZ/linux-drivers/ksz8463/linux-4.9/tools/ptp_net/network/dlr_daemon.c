/*********************************************************************************************************
Copyright (C) 2016-2017 Microchip Technology Inc. and its subsidiaries (Microchip).  All rights reserved.

You are permitted to use the software and its derivatives with Microchip products. 
See the license agreement accompanying this software, 
if any, for additional info regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. 
IN NO EVENT SHALL MICROCHIP, SMSC, OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, 
STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR 
EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
OR OTHER SIMILAR COSTS. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP AND ITS LICENSORS LIABILITY WILL NOT EXCEED 
THE AMOUNT OF FEES, IF ANY, THAT YOU PAID DIRECTLY TO MICROCHIP TO USE THIS SOFTWARE.  MICROCHIP PROVIDES THIS SOFTWARE 
CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE TERMS.

Author:  David Cai <david.cai@microchip.com>         

*********************************************************************************************************/


#include "wnp.h"
#include "unpifi.h"
#include "datatype.h"


#include <net/if.h>
#include <linux/sockios.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <sys/timeb.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "wrapthread.h"
#include "DLR_HSR_def.h"
#define USE_DEV_IOCTL

#include "ksz_sw_api.c"
#include "ksz_dlr_api.c"


//#define USE_NOTIFY
//defbie RUN_FOREGROUND
static Boolean debugmsg=MCHP_FALSE;

#define IPBUFSIZE			32
#define MYBUFSIZ 512
#define  MAX_NODES 3

#define mhp_mutex	pthread_mutex_t
#define mhp_mutex_init(x)  pthread_mutex_init(x, NULL)
#define mph_lock(x) pthread_mutex_lock(x)
#define mph_unlock(x)  pthread_mutex_unlock(x)

static mhp_mutex g_mutex;
static struct dev_info dlrdev;
static DLR_SUPERVISOR_STATUS m_nodeType=DLR_RING_NODE;
static DLR_NET_STATUS  net_status=DLR_RING_FAULT;
static int all_nodes=0;
static struct ksz_dlr_active_node  * gpnode_list=NULL; 
static char m_sendbuf[MYBUFSIZ];
static DLR_NODE_INFO m_nodeinfo;
static DLR_SUPERVISOR  m_supinfo;
static Boolean get_ip(char * pv);
static char * get_word(char * pin, char ** ppnext);
static const char * check_ip(char *  pv);
static Boolean get_mac(char * pv);
static Boolean wait_event_ack(DLR_HSR_EVENT event);
static char value[MYBUFSIZ];
static char cmdbuf[MYBUFSIZ];
static Boolean fTaskExit=MCHP_FALSE;

#ifdef USE_NOTIFY
static pthread_t taskT;
#endif
char devname[20];
static char server_ip[32];

//static DLR_NODE_INFO nodeay[MAX_NODES]={{{"192.168.1.100"}, {0x00,0x10,0xA1,0x83,0x82,0x01}},
//{{"192.168.1.102"}, {0x00,0x10,0xA1,0x00,0x00,0x51}},{{"192.168.1.101"},{0x00,0x10,0xA1,0x00,0x00,0x54}}};

/* functions*/
static int get_node_index(const char * ip);
static const char * check_ip(char *  pv);
static Boolean get_mac(char * pv);
static char * get_word(char * pin, char ** ppnext);
static Boolean get_ip(char * pv);
static void printCmdString(unsigned long cmdid);
static Boolean wait_event_ack(DLR_HSR_EVENT event);
static void cmdProcess(CMD_PKT * pcmd, const char * prmtip);
static void print_status(u8 status);
static int linux_kbhit(void);
static void send_event(DLR_HSR_EVENT event,unsigned char * pdata, int data_size);
static void handle_dlr_msg(u16 cmd, void *data, int len);
static void *NotificationTask(void *param);
static void print_network(u8 network);
static void print_node(struct ksz_dlr_active_node *node);
static void console_cmd(int key);
static void check_network();
static Boolean build_node_list();
static Boolean notify_dlr_manager(DLR_HSR_EVENT event,unsigned char * pdata, int data_size);
static void convertip(char * buf,struct ksz_dlr_active_node *node);


static Boolean notify_dlr_manager(DLR_HSR_EVENT event,unsigned char * pdata, int data_size)
{
			int result,i;
			if(strlen(server_ip)==0){
			 
			 if(debugmsg){	
					printf(". ");
				}
				return MCHP_FALSE;
		  }
		  
		  for(i=0;i<3;i++){
					send_event(event,pdata,data_size);	
					/*wait for event ack*/
					result=wait_event_ack(event);
					if(result)
						break;
				}		 		 
		 return MCHP_TRUE; 
}

static Boolean build_node_list()
{
	u16 cnt;
	int rc;
	u16 list_size;
	u8 err;
	struct ksz_dlr_active_node * plist;
  void *fd = &dlrdev;
	if(gpnode_list){ 
			free(gpnode_list);
			gpnode_list=NULL;
			all_nodes=0;
		}
	cnt=0; /* initialize the node count to zero*/
  /* ask driver for how many nodes*/
  rc=get_dlr_ring_part_cnt(fd,&cnt);
	if(rc) {/*error*/
	  printf("%s: get_dlr_ring_part_cnt error rc=%d \n",__FUNCTION__,rc);
	  return MCHP_FALSE;
	}	
  
  //printf("get_dlr_ring_part_cnt rc=%d cnt=%d \n",rc,cnt);
  
  if(!cnt) { /* it may happen, at first DLR start time*/
  	return MCHP_FALSE;
  }
  list_size=cnt * sizeof(struct ksz_dlr_active_node);
	/*allocate memory for node list*/
	plist=(struct ksz_dlr_active_node *)malloc(list_size+32);	 	
	rc = get_dlr_ring_part_list(fd,plist,&list_size,&err);
	if(rc){
		printf("%s: get_dlr_ring_part_lis error rc=%d \n",__FUNCTION__,rc);
	  return MCHP_FALSE;
	}		 	
	all_nodes=cnt;
	gpnode_list=plist;
	return MCHP_TRUE;	
}

/* in the idle time, periodically check the network*/
void check_network()
{
 u8 node_type,network;
 //DLR_SUPERVISOR_STATUS old_node_type;
 //DLR_NET_STATUS old_net_status;
 int rc;
 void *fd = &dlrdev;
 struct ksz_dlr_super_cfg cfg;
 DLR_SUPERVISOR_SELECTED_INFO  suinfo;			
 struct ksz_dlr_active_node ksz_node;	
 DLR_RING_FAULT_INFO  fault_info;
	/* get node type */
	rc=get_dlr_super_status(fd,&node_type);
	
	if(rc) {/*error*/
	  printf("%s: get_dlr_super_status error rc=%d \n",__FUNCTION__,rc);
	  return;
	}
	
	rc=get_dlr_network(fd,&network);
	if(rc){
	  printf("%s: get_dlr_network error rc=%d \n",__FUNCTION__,rc);
	  return;
	}
	//old_node_type=m_nodeType;
	//printf("(%d %d) ",node_type,m_nodeType);
	if(node_type==DLR_ACTIVE_SUPER && m_nodeType !=node_type){// && network==DLR_NET_NORMAL){
			
			/*get suppervisor configuration parameters*/
			rc=get_dlr_super_cfg(fd, &cfg);
			if(rc){
				printf("%s: get_dlr_super_cfg error rc=%d \n",__FUNCTION__,rc);
	  		return;
			}		 	
			
			 /* a new suppervisor happen, we need to update the node list*/
			/*the build node list may fail, it may happen at first time DLR network start, and 
			set a suppervisor, but the network still be broken (not connect to ring )yet*/ 
			build_node_list();
		
			
			m_supinfo.enable=1;
			m_supinfo.beacon_interval=cfg.beacon_interval;
			m_supinfo.beacon_timeout=cfg.beacon_timeout;
			m_supinfo.precedence=cfg.prec;
			m_supinfo.vlanid=cfg.vid;
			
			strcpy(suinfo.ipv4,m_nodeinfo.ipv4);
			memcpy(&suinfo.mac[0],&m_nodeinfo.mac[0],6);
			suinfo.beacon_interval=cfg.beacon_interval;
			suinfo.beacon_timeout=cfg.beacon_timeout;
			suinfo.precedence=cfg.prec;
			suinfo.vlanid=cfg.vid;
			
		  get_dlr_network(fd,(u8 *)&net_status); /*update net_status*/
			/*now we need to resport to DLR manager*/
		  if(notify_dlr_manager(DLR_SUPERVISOR_SELECTED,(unsigned char *)&suinfo,sizeof(suinfo))){
					if(debugmsg)	{
							printf("new supervisor notify the DLR manager\n");
					}
					m_nodeType=node_type; /*every thing is ok, then we update the  m_nodeType*/			
			}
					 		 
		
	}
	
	if((m_nodeType !=node_type)  && (node_type!=DLR_ACTIVE_SUPER)){
		/*node type changes, such as from DLR_ACTIVE_SUPER to DLR_BACKUP_SUPER*/
		if(debugmsg){	
				printf("AA m_nodeType=%d node_type=%d \n",m_nodeType,node_type);
		 }
		 m_nodeType=node_type;
	}
	/*now we check the network status*/
	rc=get_dlr_network(fd,&network);
	if(rc){
	  printf("%s: get_dlr_network error rc=%d \n",__FUNCTION__,rc);
	  return;
	}
	
	if(net_status != network && network != DLR_NET_NORMAL){
		/*network become broken, let get broken location, if I am a suppervisor*/
		if(debugmsg){	
			printf("network may broken old=%d new=%d \n",net_status,network);
		}
		if(m_nodeType==DLR_ACTIVE_SUPER){
			
			if(!gpnode_list) /*only may happen at begining with ring broken*/
			   build_node_list();
		
		rc=get_dlr_active_node(fd, 0, &ksz_node);
		if(rc){
		 printf("%s: get_dlr_active_node (0) rc=%d \n",__FUNCTION__,rc);
	   return;
		}				
	if(debugmsg){	
		print_node(&ksz_node);
	}
	
		convertip(&fault_info.last_active_node_on_port1.ipv4[0],&ksz_node);
		memcpy(&fault_info.last_active_node_on_port1.mac[0], &ksz_node.addr[0],6);
		rc=get_dlr_active_node(fd, 1, &ksz_node);
		if(rc){
		 printf("%s: get_dlr_active_node (1) rc=%d \n",__FUNCTION__,rc);
	   return;
		}				 		
	if(debugmsg){	
		print_node(&ksz_node);
	 }
   		
		    convertip(&fault_info.last_active_node_on_port2.ipv4[0],&ksz_node);
		    memcpy(&fault_info.last_active_node_on_port2.mac[0], &ksz_node.addr[0],6);
		/*check if these nodes are valid node or not, because driver's timing issue, some time the suppervisor
		has not collect all broken node's infomation yet*/
		if(get_node_index(&fault_info.last_active_node_on_port1.ipv4[0])<0){
			printf("(2)last_active_node(1) ip is invalid\n");
			return;
		} 
	
		if(get_node_index(&fault_info.last_active_node_on_port2.ipv4[0])<0){
			printf("last_active_node(2) ip is invalid\n");
			return;
		} 
	 if(debugmsg) {
		 printf("ring broken notify the DLR manager\n");
		}
		 if( notify_dlr_manager(DLR_RING_FAULT_DETECTED,(unsigned char *)&fault_info,sizeof(DLR_RING_FAULT_INFO ))){
		    net_status=network;	
		 }
		
	 }
		
	}
	
	if(net_status != network && network == DLR_NET_NORMAL){
		/*network restored, if I am a suppervisor*/
		if(m_nodeType==DLR_ACTIVE_SUPER){
		
			/*after network restored, it may change the nodes number or position, for example added a new node*/
			/* we need to rebuild node list*/
			if(!build_node_list()){
				printf("ring restored, but fail to get node list \n");
				return;
			}
		if(debugmsg){	
			printf("ring restored, notify DLR manager \n");
		}
			/*notify the DLR manager*/
			if(notify_dlr_manager(DLR_RING_RESTORED,NULL,0)){
				net_status=network;	
			}	
		}
	}
}


static int get_node_index(const char * ip)
{
	int i=0;
	char ipv4[32];
	if(!gpnode_list){
	  printf("no 	gpnode_list???\n");
	  return -1;
	}
	
	for(i=0;i<all_nodes;i++){
	
		convertip(&ipv4[0],(gpnode_list+i));
		if(strcmp(ip,&ipv4[0])==0)
			return i;
	}
	
	return -1;
}
																																				
static const char * check_ip(char *  pv)
{
        int k;
        int n0,n1,n2,n3;
        static char ipaddr[32];
        k=sscanf(pv,"%d.%d.%d.%d",&n0,&n1,&n2,&n3);
        if(k!=4)
                return NULL;

        if(n0>255 || n1>255 || n2>255 || n3>255)
                return NULL;

        if(n0<0 || n1<0 || n2<0 || n3<0)
                return NULL;
        ipaddr[0]='\0';
        sprintf(ipaddr,"%d.%d.%d.%d",n0,n1,n2,n3);
        return ipaddr;
}

static Boolean get_mac(char * pv)
{
        FILE * fp;
        char *pFind;
        sprintf(cmdbuf,"ifconfig %s | grep HWaddr", devname);
        fp = popen(cmdbuf, "r");
        if (fp == NULL) {
                printf("Fail to open pipe\n");
                return MCHP_FALSE;
        }
        value[0]='\0';
        if(fgets(value, MYBUFSIZ, fp) != NULL) {
                ;//printf("%s", value);
        }
        pclose(fp);
        if(!strlen(value))
                return MCHP_FALSE;
        pFind=strstr(value,"HWaddr");
        pFind+=strlen("HWaddr");
        strcpy(pv,pFind);
        return MCHP_TRUE;

}
static char * get_word(char * pin, char ** ppnext)
{
        static char word[128];
        char * ps, c;
        if(!pin)
        	return NULL;
        // first skip left speace
        while(*pin!='\0') {
                if(*pin>=0x21 && *pin<='z')
                        break;
                pin++;
        }
        ps=pin;
        while(*ps!='\0') {

                if(*ps==' ' || * ps=='\t') {
                        c=*ps;
                        *ps='\0';
                        strcpy(word,pin);
                        *ps=c;
                        *ppnext=ps;
                        return word;
                }
                ps++;

        }
        if(ps==pin) // no word;
                return NULL;
        *ppnext=NULL;
        strcpy(word,pin);
        return word;
}


static Boolean get_ip(char * pv)
{
        FILE * fp;
        char * pword, * pnext;
        sprintf(cmdbuf,"ifconfig %s | grep inet | cut -d\":\" -f2", devname);
        fp = popen(cmdbuf, "r");
        if (fp == NULL) {
                printf("Fail to open pipe\n");
                return MCHP_FALSE;
        }
        value[0]='\0';
        if(fgets(value, MYBUFSIZ, fp) != NULL) {
                ;//printf("%s", value);
        }
        pclose(fp);
        if(strlen(value)<8)// the ip address format is at least 8 char long
                return MCHP_FALSE;

        pword=get_word(value,&pnext);

        if( check_ip(pword)==NULL) {
                printf("Error: Fail to detect local network connection\n");
                return MCHP_FALSE;
        }
        strncpy(pv,pword,IPBUFSIZE);
        return MCHP_TRUE;
}


static void printCmdString(unsigned long cmdid)
{
	 switch(cmdid){
			case DLR_QUERY_NETWORK:
			printf("cmd='DLR_QUERY_NETWORK'\n");
			break;
			
			case DLR_GET_NET_STATUS:
			printf("cmd='DLR_GET_NET_STATUS'\n");
			break;
			case DLR_GET_SUPERVISOR_STATUS:
			printf("cmd='DLR_GET_SUPERVISOR_STATUS'\n");
			break;
			case DLR_GET_SUPERVISOR:
            printf("cmd='DLR_GET_SUPERVISOR'\n");
			break;
			case DLR_SET_SUPERVISOR:
			printf("cmd='DLR_SET_SUPERVISOR'\n");
			break;
			case  DLR_GET_FAULTS_COUNT:
			printf("cmd='DLR_GET_FAULTS_COUNT'\n");
			break;
			case DLR_GET_RING_NODES:
			printf("cmd='DLR_GET_RING_NODES'\n");
			break;
			case  DLR_GET_RING_NODES_LIST:
			printf("cmd='DLR_GET_RING_NODES_LIST'\n");
			break;

			case DLR_GET_RING_FAULT_INFO:
			printf("cmd='DLR_GET_RING_FAULT_INFO'\n");
			break;

			case DLR_GET_SUPERVISOR_ADDR:
			printf("cmd='DLR_GET_SUPERVISOR_ADDR'\n");
			break;
			
			default:
            printf("unknow command =%d \n",(int)cmdid);
			break;
		}

}

static Boolean wait_event_ack(DLR_HSR_EVENT event)
{
	 struct sockaddr_in name;
   int result,sockfd;
   const int reuseFlag=1;
   	sockfd=socket(AF_INET,SOCK_DGRAM,0);
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuseFlag, sizeof reuseFlag) < 0){
		 		close(sockfd);
        printf("%s: fail to set  SO_REUSEADDR in EventPortReceivng\n",__FUNCTION__);
		 		return MCHP_FALSE;
		}
	
		memset(&name,0,sizeof(struct sockaddr_in));
		name.sin_family = AF_INET;
		name.sin_port = htons(EVENT_PORT);
		name.sin_addr.s_addr = INADDR_ANY;
		result=bind(sockfd, (struct sockaddr*)&name, sizeof name);
		if(result <0){
			printf("%s: socket bind error\n",__FUNCTION__);
			return MCHP_FALSE;
		}
	
	while(1) {
                struct timeval timeout;
                fd_set set;
                int result;
                timeout.tv_sec=0;//ONE_SECOND;
                timeout.tv_usec=(300*1000); //300 ms

                FD_ZERO( &set );
                FD_SET(sockfd, &set );
                result = select( FD_SETSIZE, &set, NULL, NULL, &timeout );
							  if(result<0) {
                        printf ("%s socket_select() failed, close current socket \n",__FUNCTION__);
                        fflush(stdout);
                        close(sockfd);
                        return MCHP_FALSE;
                } else if(result ==0) {
                	  printf("%s: timeout to get event ack\n",__FUNCTION__);
                	  fflush(stdout);
                	  close(sockfd);
										return MCHP_FALSE;
								}
								else {
												char rbuf[512];
                        int n_read;
                        EVENT_PKT * pevepkt;
                        socklen_t len;     
                        Boolean f=MCHP_FALSE;
                        unsigned long magic, ev;                  
                        struct sockaddr clientAddr; /*client address*/
                        len=sizeof(struct sockaddr);
                        n_read=recvfrom(sockfd,(unsigned char*)rbuf,sizeof(rbuf),0,&clientAddr,&len);
        								/*check to see if it is a waiting event ack*/
        								pevepkt=(EVENT_PKT *)&rbuf[0];
        								magic=ntohl(pevepkt->magic_number);
											  //printf("evt size=%d magic=0x%x event=%d\n",n_read,magic,ntohl(pevepkt->event));
											  if(magic==DEMO_MAGICNUMBER){
											  	  ev=ntohl(pevepkt->event);
											  	  if(ev==EVENT_ACK){
        											//printf("!get event ack size=%d \n",n_read);
        											f=MCHP_TRUE;
        										}
        								}
        								fflush(stdout);
        								close(sockfd);
        								return f;
        					}
        }
								
}

static void cmdProcess(CMD_PKT * pcmd, const char * prmtip)
{
	int sockfd,result;
	struct sockaddr_in servaddr;
	EVENT_PKT eve;
	CMD_PKT * pcmdsend;
	unsigned short port;
	int i,rc,reuseFlag;
	u8 err;
	u16 cnt=0;
	u8 status=0;
	struct ksz_dlr_super_cfg cfg;
	struct ksz_dlr_active_node ksz_node;
	void *fd = &dlrdev;
	unsigned long cmdsize=ntohl(pcmd->pktsize);
	unsigned long magic=ntohl(pcmd->magic_number);

	if(magic==DEMO_MAGICNUMBER){
	unsigned long cmdid=ntohl(pcmd->cmd);
	if(debugmsg)	  
		  printCmdString(cmdid);
    
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseFlag, sizeof reuseFlag) < 0){
		      printf("(2)setsockopt SO_REUSEADDR failed\n");
		  		return ;
	}
				
	servaddr.sin_family = AF_INET;
	if(cmdid==DLR_QUERY_NETWORK)
		servaddr.sin_port= htons(EVENT_PORT);
	else{
		port=CMD_PORT;//EVENT_PORT;//CMD_PORT-m_index+100;
		servaddr.sin_port=htons(port);
//		printf("sendback port =%d \n",port);
	}
	servaddr.sin_addr.s_addr=inet_addr(prmtip);
	eve.magic_number=htonl(DEMO_MAGICNUMBER);
	/*prepare the cmd send packet*/
	pcmdsend=(CMD_PKT*)&m_sendbuf[0];
	pcmdsend->magic_number=htonl(DEMO_MAGICNUMBER);
	pcmdsend->return_code=htonl(1);	/*pre-set to TRUE*/	
		  
		  switch(cmdid){
			case DLR_QUERY_NETWORK:
			/*report node infomation*/
			{
				DLR_NODE_REPORT * pnr;
				int i;
				strcpy(server_ip,prmtip);
				printf("server_ip=%s \n",server_ip);
				eve.event=(DLR_HSR_EVENT)htonl(DLR_REPORT_NODE_INFO);
				pnr=(DLR_NODE_REPORT *)&eve.event_data[0];
				memcpy(&pnr->nodeinfo,&m_nodeinfo,sizeof(DLR_NODE_INFO));
				rc = get_dlr_super_status(fd, &status);
				pnr->status=(DLR_SUPERVISOR_STATUS)htonl(status);
				for(i=0;i<3;i++){
					result=sendto(sockfd,(char *)&eve,sizeof(EVENT_PKT),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
						/*wait for event ack*/
						result=wait_event_ack(DLR_REPORT_NODE_INFO);
						if(result)
							break;
					}
				}
				
			break;

			case DLR_GET_NET_STATUS:
				{
					DLR_NET_STATUS_INFO * pnet;
					u8 network;
					pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_GET_NET_STATUS);
					//any node can get a network status, 	
					rc = get_dlr_network(fd, &network);	
					if(rc)
						pcmdsend->return_code=htonl(0); 
						
					pnet=(DLR_NET_STATUS_INFO *)&pcmdsend->cmd_data[0];
					pnet->net_status=(DLR_NET_STATUS)htonl((long)(network));
					cmdsize=sizeof(CMD_PKT)-sizeof(char)+sizeof(DLR_NET_STATUS_INFO);
					pcmdsend->pktsize=htonl(cmdsize);
					result=sendto(sockfd,(char *)&m_sendbuf[0],cmdsize,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
				
			  }
				break;
			
			case DLR_GET_SUPERVISOR_STATUS:{
						DLR_SUPERVISOR_STATUS_DATA * pus;
						
						pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_GET_SUPERVISOR_STATUS);
						pus=(DLR_SUPERVISOR_STATUS_DATA *)&pcmdsend->cmd_data[0];
						rc = get_dlr_super_status(fd, &status);
						if(rc)
								pcmdsend->return_code=htonl(0);
						
					  //we cannot update local viable here, we need to let the check_network function to do this	m_nodeType=status; 
			 			pus->dlr_supervisor_status=htonl(status);//m_nodeType);
						cmdsize=sizeof(CMD_PKT)-sizeof(char)+sizeof(DLR_SUPERVISOR_STATUS_DATA);
						pcmdsend->pktsize=htonl(cmdsize);
						result=sendto(sockfd,(char *)&m_sendbuf[0],cmdsize,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
	    		}
					break;

			case DLR_GET_SUPERVISOR:
					{
						DLR_SUPERVISOR * psu;
						pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_GET_SUPERVISOR);				
						/*check to see if I am a supervisor*/
			  		if(m_nodeType==DLR_BACKUP_SUPER || m_nodeType==DLR_ACTIVE_SUPER){
			  				rc=get_dlr_super_cfg(fd, &cfg);
			  			if(rc)
			  					pcmdsend->return_code=htonl(0);
			  			else {
			  				m_supinfo.enable=cfg.enable;
			  				m_supinfo.beacon_interval=cfg.beacon_interval;
			  				m_supinfo.beacon_timeout=cfg.beacon_timeout;
			  				m_supinfo.precedence=cfg.prec;
			  				m_supinfo.vlanid=cfg.vid;
	
			  			}
			  	 }
			  	else
			  		pcmdsend->return_code=htonl(0);	
				
					psu=(DLR_SUPERVISOR * )&pcmdsend->cmd_data[0];
					psu->beacon_interval=htonl(m_supinfo.beacon_interval);
					psu->beacon_timeout=htonl(m_supinfo.beacon_timeout);
					psu->enable=htonl(m_supinfo.enable);
					psu->precedence=htonl(m_supinfo.precedence);
					psu->vlanid=htonl(m_supinfo.vlanid);
					cmdsize=sizeof(CMD_PKT)-sizeof(char)+sizeof(DLR_SUPERVISOR);
					pcmdsend->pktsize=htonl(cmdsize);
					result=sendto(sockfd,(char *)&m_sendbuf[0],cmdsize,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
				}
			break;

			case DLR_SET_SUPERVISOR:
			{
				DLR_SUPERVISOR * psu;
				pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_SET_SUPERVISOR);
			
				psu=(DLR_SUPERVISOR *)&pcmd->cmd_data[0];
				m_supinfo.beacon_interval=ntohl(psu->beacon_interval);
				m_supinfo.beacon_timeout=ntohl(psu->beacon_timeout);
				m_supinfo.enable=ntohl(psu->enable);
				m_supinfo.precedence=ntohl(psu->precedence);
				m_supinfo.vlanid=ntohl(psu->vlanid);
				printf("set precedence=%d \n",(int)m_supinfo.precedence);
				
			  cfg.enable=m_supinfo.enable;
			  cfg.beacon_interval=m_supinfo.beacon_interval;
			  cfg.beacon_timeout=m_supinfo.beacon_timeout;
			  cfg.prec=m_supinfo.precedence;
			  cfg.vid=m_supinfo.vlanid;
			  rc = set_dlr_super_cfg(fd, &cfg, &err);
			  if(rc)
			  	pcmdsend->return_code=htonl(0);
			
				cmdsize=sizeof(CMD_PKT)-sizeof(char)+sizeof(DLR_SUPERVISOR);
				pcmdsend->pktsize=htonl(cmdsize);
				result=sendto(sockfd,(char *)&m_sendbuf[0],cmdsize,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
					
			}
			break;
			
			case  DLR_GET_FAULTS_COUNT:
				{
					DLR_FAULTS_COUNT * pfaults;
					pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_GET_FAULTS_COUNT);
			  	rc=get_dlr_ring_fault_cnt(fd,&cnt);
			  	if(rc)
			    	pcmdsend->return_code=htonl(0);
			  
					pfaults=(DLR_FAULTS_COUNT *  )&pcmdsend->cmd_data[0];
					pfaults->dlr_faults_count=htonl(cnt);
					cmdsize=sizeof(CMD_PKT)-sizeof(char)+sizeof(DLR_FAULTS_COUNT);
					pcmdsend->pktsize=htonl(cmdsize);
					result=sendto(sockfd,(char *)&m_sendbuf[0],cmdsize,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
				}
				break;
			
			case DLR_GET_RING_NODES:{
			   	DLR_NODES_COUNT * pc;
			  	 pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_GET_RING_NODES);
			   	cnt=0; /* initialize the node count to zero*/
				 	if(m_nodeType==DLR_ACTIVE_SUPER) {
			     	rc=get_dlr_ring_part_cnt(fd,&cnt);
				   	if(rc)
				  			pcmdsend->return_code=htonl(0);
				 
			  	}
			  	else
			   		pcmdsend->return_code=htonl(0);
				 	 
			   	pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_GET_RING_NODES);
			   	pc=(DLR_NODES_COUNT *)&pcmdsend->cmd_data[0];
			   	pc->dlr_ring_nodes_count=cnt;//htonl(all_nodes);
			   	cmdsize=sizeof(CMD_PKT)-sizeof(char)+sizeof(DLR_NODES_COUNT);
			   	pcmdsend->pktsize=htonl(cmdsize);
			   	result=sendto(sockfd,(char *)&m_sendbuf[0],cmdsize,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
				}
				break;
			
			case  DLR_GET_RING_NODES_LIST:
			{
				DLR_NODES_LIST_INFO * pls;
				pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_GET_RING_NODES_LIST);
				
				pls=(DLR_NODES_LIST_INFO * )&pcmdsend->cmd_data[0];
				DLR_NODE_INFO * plsnode= &pls->node_info[0];
				if(m_nodeType==DLR_ACTIVE_SUPER) {
			  	 pls->ring_nodes=htonl(0);
			   	if(!gpnode_list)
			   			 build_node_list();
			  
			   if(gpnode_list){
			      struct ksz_dlr_active_node * pn=gpnode_list;
			      pls->ring_nodes=htonl(all_nodes);
			      for(i=0;i<all_nodes;i++){
			      	
					     convertip( &plsnode->ipv4[0],pn);
					      	memcpy(&plsnode->mac[0],&pn->addr[0],6);
					      	pn++;
					      	plsnode++;
					  } 		 	
			    }
			  }
			  else
			  	pcmdsend->return_code=htonl(0);
			  
			  if(all_nodes==0)
			    	cmdsize=sizeof(CMD_PKT)-sizeof(char)+sizeof(DLR_NODES_LIST_INFO);
			  else 	
			  		cmdsize=sizeof(CMD_PKT)-sizeof(char)+sizeof(long)+(all_nodes*sizeof(DLR_NODE_INFO));
			    
			    pcmdsend->pktsize=htonl(cmdsize);
					result=sendto(sockfd,(char *)&m_sendbuf[0],cmdsize,0,(struct sockaddr *)&servaddr,sizeof(servaddr));	 	
			  	
			}
			break;

			case DLR_GET_RING_FAULT_INFO:
				{
					DLR_RING_FAULT_INFO * pnf;
					DLR_NODE_INFO node1,node2;
					rc=get_dlr_active_node(fd, 0, &ksz_node);
					pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_GET_RING_FAULT_INFO);
					
					memset(&node1,0,sizeof(DLR_NODE_INFO));
					memset(&node2,0,sizeof(DLR_NODE_INFO));
					
					if(rc)
						pcmdsend->return_code=htonl(0);
					else{
					
						convertip(&node1.ipv4[0],&ksz_node);
						memcpy(&node1.mac[0],&ksz_node.addr[0],6);
					}

					rc=get_dlr_active_node(fd, 1, &ksz_node);
					if(rc)
						pcmdsend->return_code=htonl(0);
					else{
					
						convertip(&node2.ipv4[0],&ksz_node);
						memcpy(&node2.mac[0],&ksz_node.addr[0],6);
					}
					pcmdsend=(CMD_PKT*)&m_sendbuf[0];
					pnf=(DLR_RING_FAULT_INFO *)&pcmdsend->cmd_data[0];
					pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_GET_RING_FAULT_INFO);
					
					memcpy(&pnf->last_active_node_on_port1,&node1,sizeof(DLR_NODE_INFO));
					memcpy(&pnf->last_active_node_on_port2,&node2,sizeof(DLR_NODE_INFO));

					cmdsize=sizeof(CMD_PKT)-sizeof(char)+sizeof(long)+sizeof(DLR_RING_FAULT_INFO);
					pcmdsend->pktsize=htonl(cmdsize);
					result=sendto(sockfd,(char *)&m_sendbuf[0],cmdsize,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
	
				}
				break;
		
			case DLR_GET_SUPERVISOR_ADDR:{
						DLR_NODE_INFO * pnode;
						pcmdsend->cmd=(DLR_HSR_CMD)htonl(DLR_GET_SUPERVISOR_ADDR);
				
				    rc = get_dlr_active_super_addr(fd, &ksz_node);
			      if(rc)
		 					pcmdsend->return_code=htonl(0);
		 				else{
		 					if(debugmsg){	
		 						print_node(&ksz_node);
		 					}
		 						pnode=(DLR_NODE_INFO *)&pcmdsend->cmd_data[0];
		 						convertip(&pnode->ipv4[0],&ksz_node);
		 						
		 						memcpy(&pnode->mac[0], &ksz_node.addr[0],6);
		 				}
		 			cmdsize=sizeof(CMD_PKT)-sizeof(char)+sizeof(long)+sizeof(DLR_NODE_INFO);
					pcmdsend->pktsize=htonl(cmdsize);
					result=sendto(sockfd,(char *)&m_sendbuf[0],cmdsize,0,(struct sockaddr *)&servaddr,sizeof(servaddr));
		 		}
				break;


			default:

			break;
		}
	  close(sockfd);
	
	}

    
}

static void print_status(u8 status)
{
	printf("status: ");
	switch (status) {
	case DLR_STAT_BACKUP_SUPERVISOR:
		printf("backup supervisor\n");
		break;
	case DLR_STAT_ACTIVE_SUPERVISOR:
		printf("active supervisor\n");
		break;
	case DLR_STAT_RING_NODE:
		printf("ring node\n");
		break;
	case DLR_STAT_NO_SUPERVISOR:
		printf("no supervisor\n");
		break;
	case DLR_STAT_NODE_NOT_SUPPORTED:
		printf("not supported\n");
		break;
	}
}

static int linux_kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
  
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
   
   return ch;
}

static void send_event(DLR_HSR_EVENT event,unsigned char * pdata, int data_size)
{
	int sockfd,result;
	struct sockaddr_in servaddr;
	EVENT_PKT eve;
	const int reuseFlag = 1;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	 if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseFlag, sizeof reuseFlag) < 0){
		 printf("setsockopt SO_REUSEADDR failed\n");
		  		return;
	}
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port= htons(EVENT_PORT);
	servaddr.sin_addr.s_addr=inet_addr(server_ip);
	
	eve.magic_number=htonl(DEMO_MAGICNUMBER);
	eve.event=(DLR_HSR_EVENT)htonl(event);
	if(pdata)
		memcpy(&eve.event_data[0], pdata,data_size);
	
	
  result=sendto(sockfd,(char *)&eve,sizeof(EVENT_PKT),0,(struct sockaddr *)&servaddr,sizeof(servaddr));
  close(sockfd);		
}
 

 
 
static void handle_dlr_msg(u16 cmd, void *data, int len)
{
	u32 *dword = data;
	int rc;
	void *fd = &dlrdev;
	switch (cmd) {
	case DEV_INFO_QUIT:
		printf("quit\n");
		break;
	case DEV_INFO_DLR_LINK:
   {		
				u8 status;
				printf("link status: %x\n", *dword);
				
				/* check to see if I is a suppervisor*/
        rc = get_dlr_super_status(fd, &status);
        if(status==DLR_STAT_ACTIVE_SUPERVISOR){				
        	len -= 4;
		     if (len >= 4 + sizeof(struct ksz_dlr_active_node)) {
						char ipv4[32];	
						struct ksz_dlr_active_node *active =	(struct ksz_dlr_active_node *)(dword + 1);
          	convertip(ipv4,active);
						printf("message from ip=%s localip=%s\n",ipv4,m_nodeinfo.ipv4);
				
					}
				
				}
	}	
	case DEV_INFO_DLR_CFG:
		#if 0
			rc=get_dlr_network(fd, &network);
			if(net_status!= network && network==DLR_NET_NORMAL){
				  printf("ring broken restored \n");
				  net_status=DLR_NET_NORMAL;
				  send_event(DLR_RING_RESTORED,NULL,0);	
				  
			}  
		#endif
		printf("cfg: %x\n", *dword);
		break;
	
		break;
	}
}



static void *NotificationTask(void *param)
{
	int len;
	u8 data[MAX_REQUEST_SIZE];
	//PTTaskParam pTaskParam = param;
  //pTaskParam->fTaskStop = FALSE;
	fTaskExit=MCHP_FALSE;
	printf("Notification task running\n");
	do {
						
		
		len = sw_recv(&dlrdev, data, MAX_REQUEST_SIZE);
		if (len > 0) {
			printf("+-%s --\n",__FUNCTION__);		  
		  check_network();
#if 0		
			struct ksz_resp_msg *msg = (struct ksz_resp_msg *)
				data;
	

			switch (msg->module) {
			case DEV_MOD_DLR:
				handle_dlr_msg(msg->cmd, msg->resp.data, len);
				break;
			default:
				printf("[%d] ", len);
			}
#endif		
		
				fflush(stdout);
			
		}
	} while (!fTaskExit);
	printf("Notification task exit!\n");
	return NULL;
} 

static void print_network(u8 network)
{
	printf("network: ");
	switch (network) {
	case DLR_NET_NORMAL:
		printf("normal\n");
		break; 
	case DLR_NET_RING_FAULT:
		printf("ring fault\n");
		break; 
	case DLR_NET_UNEXPECTED_LOOP_DETECTED:
		printf("unexpected loop\n");
		break; 
	case DLR_NET_PARTIAL_FAULT:
		printf("partial fault\n");
		break; 
	case DLR_NET_RAPID_FAULT:
		printf("rapid fault\n");
		break; 
	}
}

static void convertip(char * buf,struct ksz_dlr_active_node *node)
{
		sprintf(buf,"%u.%u.%u.%u",
		(u8)(node->ip_addr),
		(u8)(node->ip_addr >> 8),
		(u8)(node->ip_addr >> 16),
		(u8)(node->ip_addr >> 24));
}

static void print_node(struct ksz_dlr_active_node *node)
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x  ",
		node->addr[0],
		node->addr[1],
		node->addr[2],
		node->addr[3],
		node->addr[4],
		node->addr[5]);
	printf("%u.%u.%u.%u\n",
		(u8)(node->ip_addr),
		(u8)(node->ip_addr >> 8),
		(u8)(node->ip_addr >> 16),
		(u8)(node->ip_addr >> 24));
}




static void console_cmd(int key)
{
	int rc,size;
	u8 err,topology, network,status;
	u16 cnt;
	struct ksz_dlr_super_cfg cfg;
	void *fd = &dlrdev;

	topology = 0;
	switch (key){
			case 'a':
				m_supinfo.beacon_interval=400;
				m_supinfo.beacon_timeout=1960;
				m_supinfo.enable=1;
				m_supinfo.precedence=0;
				m_supinfo.vlanid=0;
			
			  cfg.enable=m_supinfo.enable;
			  cfg.beacon_interval=m_supinfo.beacon_interval;
			  cfg.beacon_timeout=m_supinfo.beacon_timeout;
			  cfg.prec=m_supinfo.precedence;
			  cfg.vid=m_supinfo.vlanid;
			  rc = set_dlr_super_cfg(fd, &cfg, &err);
			 // m_nodeType=DLR_ACTIVE_SUPER;
			  
			  
			  printf("set suppervisor rc=%d \n",rc);
			break;
		 
		 case 'b':
		 	rc = get_dlr_topology(fd, &topology);
			printf("rc=%d get topology=%s\n", rc,(DLR_TOPOLOGY_RING == topology) ? "ring" : "linear");	
	    break;
	    
	   case 'c':
	   	rc = get_dlr_network(fd, &network);
	   	printf("get network rc=%d \n",rc);
	   	print_network(network);
	   	break;
	   	
	   case 'd':
	   	rc=get_dlr_super_cfg(fd,&cfg);
	   	printf("get sup cfg rc=%d enable=%d intervale=%d timeout=%d prec=%d vid=%d\n",
	   	rc,cfg.enable,cfg.beacon_interval,cfg.beacon_timeout,cfg.prec,cfg.vid);
	   break;
		 
		 case 'e':
		 	rc = get_dlr_super_status(fd, &status);
		 	print_status(status);
		 	break;
		 
		 case 'f':
		 	rc=get_dlr_ring_part_cnt(fd,&cnt);
		 	printf(" ring part cnt rc=%d cnt=%d \n",rc,cnt);
		 	break;	
		 
		 case 'g':{
		 	int i;
			u16 list_size;
		  struct ksz_dlr_active_node * plist;
		  			char ipv4[32];
		  			struct ksz_dlr_active_node * pn;
		  			get_dlr_ring_part_cnt(fd,&cnt);
						/*allocate memory for node list*/
					 list_size=cnt * sizeof(struct ksz_dlr_active_node);
					 plist=(struct ksz_dlr_active_node *)malloc(list_size+32);	 	
					 rc = get_dlr_ring_part_list(fd,plist,&list_size,&err);
					    printf("++get_dlr_ring_part_list rc=%d \n",rc);
					
					 pn=plist;
					 for(i=0;i<cnt;i++){
							    convertip(&ipv4[0],pn);
					      	print_node(pn);
					      	pn++;
					      }
				  free(plist);		
					 	  
			} 	
		 break;	
		 	
		 case 'h':
		 	  rc=get_dlr_ring_fault_cnt(fd,&cnt);
		 	  printf("get ring fault count rc=%d cnt=%d \n",rc, cnt);
		 	break;	
		 	
		 case 'i':
		 	{
		 			struct ksz_dlr_active_node ksz_node;
		 			rc=get_dlr_active_node(fd, 0, &ksz_node);
		 		  printf("get active node 0 rc=%d \n",rc);
		 		  print_node(&ksz_node);
		 		  rc=get_dlr_active_node(fd, 1, &ksz_node);
		 		  printf("get active node 1 rc=%d \n",rc);
		 		  print_node(&ksz_node);
		 		  
		 	}	  
		 		  
		 	break;	
		 
		 case 'j':
				m_supinfo.beacon_interval=400;
				m_supinfo.beacon_timeout=1600;
				m_supinfo.enable=1;
				m_supinfo.precedence=3;
				m_supinfo.vlanid=3;
			
			  cfg.enable=m_supinfo.enable;
			  cfg.beacon_interval=m_supinfo.beacon_interval;
			  cfg.beacon_timeout=m_supinfo.beacon_timeout;
			  cfg.prec=m_supinfo.precedence;
			  cfg.vid=m_supinfo.vlanid;
			  rc = set_dlr_super_cfg(fd, &cfg, &err);
			  m_nodeType=DLR_ACTIVE_SUPER;
			  
			 
			  printf("set suppervisor rc=%d \n",rc);
			break;
		 
		case 'k':
		  system("cat /sys/class/net/eth0/dlrfs/state");
		  break;
		 	
		 case 'q':
		 printf("exit the program\n");
		 rc = dlr_dev_exit(&dlrdev);
		 sw_exit(&dlrdev);
		 exit(0);
		 break;	
	}
	return;
}

int main (int argc, const char * argv[])
{
#define APP_VERSION					68

int		 sockfd, result;
u8 err;
char 	s_mac[32];
struct sockaddr_in name;
int addr_size=sizeof(struct sockaddr_in);
int    i,rc,port=CMD_PORT;
const char s[2] = ":";
unsigned long ll;//,jj;
char *token;
const int reuseFlag = 1;
unsigned long int nonBlockingMode = 1;

struct ksz_dlr_active_node node;
 
	if (argc < 2) {
		printf("usage: %s <local_if> [debugflag]\n",
			argv[0]);
		return 1;
	}
	strncpy(devname, argv[1], sizeof(devname));

  if(argc==3)
  	debugmsg=atoi(argv[2]);
  	
     	 printf("DLR Daemon runing cmdport=%d event_port=%d version=1.%d\n", CMD_PORT,EVENT_PORT, APP_VERSION);   
  		
  		mhp_mutex_init(&g_mutex);
 
       if (sw_init(&dlrdev)) {
						printf("cannot access device\n");
						return -1;
				}
       	
       	rc = sw_dev_init(&dlrdev, 0, &sw_version, &sw_ports);
				if (rc) {
						print_sw_err(rc);
						printf("sw_dev_init error\n");
						sw_exit(&dlrdev);
						return -1;
				}
       
       
				rc = dlr_dev_init(&dlrdev, 0, &dlr_version, &dlr_ports);

			
			
	#ifdef USE_NOTIFY
		   if (!rc) {
						printf("version=%d ports=0x%x\n",	dlr_version, dlr_ports);
							rc = set_dlr_notify(&dlrdev,DLR_INFO_CFG_CHANGE | DLR_INFO_LINK_LOST);
				}
 		 
			 Pthread_create(&taskT, NULL, NotificationTask, NULL);
  #endif
			
			  get_ip(&m_nodeinfo.ipv4[0]);
        get_mac(&s_mac[0]);
        
        node.ip_addr =inet_addr(&m_nodeinfo.ipv4[0]); 
				rc = set_dlr_ip_addr(&dlrdev, &node, &err);
	      printf("!node ip=%s mac=%s rc=%d\n",m_nodeinfo.ipv4,s_mac, rc);
  
      i=0;
  		token = strtok(s_mac, s);
   		if(token){
   				sscanf(token,"%x", (unsigned int *)&ll);
					m_nodeinfo.mac[i++]=(unsigned char)ll;
				
   		}
  		 	/* walk through other tokens */
   			while( token != NULL ) 
   			{
      		token = strtok(NULL, s);
	  			if(token){
							sscanf(token,"%x", (unsigned int *)&ll);
							m_nodeinfo.mac[i++]=(unsigned char)ll;
						}
   			}
      
     
        
        sockfd =socket(PF_INET,SOCK_DGRAM,0);

        if (sockfd < 0) {
                printf("unable to create stream socket: ");
                return sockfd;
        }
        
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuseFlag, sizeof reuseFlag) < 0){
		      printf("setsockopt SO_REUSEADDR failed\n");
		  		return -1;
				}
	

        memset(&name,0,addr_size);

        name.sin_family = AF_INET;
        name.sin_port = htons(port);
        name.sin_addr.s_addr = INADDR_ANY;
        result=bind(sockfd, (struct sockaddr*)&name, sizeof name);
        
         if (result != 0) {
                printf( "bind() error (port number: %d): ",port);
              	close(sockfd);
                return -1;
        }
        
         // Set Non Blocking Mode, specified via last parameter
        // 0 Disabled
        // !0 Enabled

        result=ioctl(sockfd,FIONBIO, &nonBlockingMode );
        if ( result ) {
                printf("ioctlsocket failed\n");
                exit(1);
        }
				while(1) {
        	      //char number[32], nouse[8];
                struct timeval timeout;
                fd_set set;
                int key;
                //time_t cur_time;

                /* don't change the time-out value, because we use this one second idle time to count DIAL_WAIT_TIME
                  and  auto answer wait time  */
              
                timeout.tv_sec=0;//1;//ONE_SECOND;
                timeout.tv_usec=(300*1000);//300 millisecond 0;

                FD_ZERO( &set );
                FD_SET(sockfd, &set );
                result = select( FD_SETSIZE, &set, NULL, NULL, &timeout );

                if(result<0) {
                        printf ("socket_select() failed, close current socket \n");
                        close(sockfd);
                } else if(result ==0) {
                				void * status;
												//idle time
											#ifndef USE_NOTIFY
												check_network();
											#endif
												//printf("i ");
												#ifdef RUN_FOREGROUND
													key = linux_kbhit();
													console_cmd(key);
												#endif
											  fflush(stdout);
												 
								}
								else {
									
									  		//struct timeval tvT;
                        char rbuf[512];
                        char rmtip[32];
                        int n_read,len;                       
                        struct sockaddr_in clientAddr; /*client address*/
                        len=sizeof(struct sockaddr_in);
                        n_read=recvfrom(sockfd,(unsigned char*)rbuf,sizeof(rbuf),0,(struct sockaddr *) &clientAddr, (socklen_t *) &len);
                        strcpy(rmtip,inet_ntoa(clientAddr.sin_addr));
                        //printf("\n <-ip=%s received data size=%d --------->\n",rmtip,n_read);
                        cmdProcess((CMD_PKT *)&rbuf[0],rmtip);
                        fflush(stdout);
                        
								}
				}

printf("dlr daemon exit\n");
return 0;
}


