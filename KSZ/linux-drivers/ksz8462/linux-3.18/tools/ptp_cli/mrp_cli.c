#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <netinet/in.h>

#define USE_NET_IOCTL

#include "ksz_mrp_api.c"


struct dev_info mrpdev;

#define DATA_BUFFER_SIZE  2000


static void print_addr(u8 *addr)
{
	int i;

	for (i = 0; i < ETH_ALEN - 1; i++)
		printf("%02x:", addr[i]);
	printf("%02x", addr[i]);
}

static void print_id(u8 *id)
{
	int i;

	for (i = 0; i < 8 - 1; i++)
		printf("%02x.", id[i]);
	printf("%02x", id[i]);
}

static void proc_get_attribute(void)
{
	union mrp_data data;
	int action;
	int port;
	int type;
	int rc;
	void *fd = &mrpdev;

	do {
		rc = get_attribute(fd, &port, &type, &action, &data,
			sizeof(data));
		if (type != MRP_TYPE_UNKNOWN) {
			printf("%d: ", port);
			if (MRP_ACTION_TX == action)
				printf("P ");
			else if (MRP_ACTION_LV == action)
				printf("L ");
			switch (type) {
			case MRP_TYPE_MAC:
				printf("M= ");
				print_addr(data.mac.addr);
				break;
			case MRP_TYPE_VLAN:
				printf("V= ");
				printf("%d", data.vlan.id);
				break;
			case MRP_TYPE_DOMAIN:
				break;
			case MRP_TYPE_LISTENER:
				printf("L= ");
				print_id(data.listener.id);
				printf(" %u", data.listener.substate);
				break;
			case MRP_TYPE_TALKER:
				printf("T= ");
				print_id(data.talker.id);
				printf(" ");
				print_addr(data.talker.dest);
				printf(" %u %u:%u %u %u %u",
					data.talker.vlan_id,
					data.talker.priority,
					data.talker.rank,
					data.talker.MaxFrameSize,
					data.talker.MaxIntervalFrames,
					data.talker.AccumulatedLatency);
				if (data.talker.FailureCode) {
					printf("\n");
					print_id(data.talker.bridge_id);
					printf(" %s", get_failure_code(
						data.talker.FailureCode));
				}
				break;
			}
			if (DEV_IOC_MRP_REPORT == rc)
				printf(" ->");
			printf("\n");
		} else
			print_mrp_err(rc);
	} while (DEV_IOC_MRP_REPORT == rc);
}

void get_cmd(FILE *fp)
{
	int count;
	int hcount;
	unsigned int num[10];
	unsigned int hex[10];
	int rc;
	int cont = 1;
	char cmd[80];
	char line[80];
	u32 srp_latency = 0;
	u32 srp_frame = 786;
	u32 srp_interval = 2;
	u8 srp_priority = 2;
	u8 srp_rank = 1;
	u8 srp_code = 0;
	u8 srp_state = SRP_READY;
	u16 vid = 2;
	u8 uid[2];
	u8 bid[8];
	u8 sid[8];
	u8 dest[6];
	struct MRP_mac mac;
	struct MRP_vlan vlan;
	struct SRP_domain_class domain;
	struct SRP_listener listener;
	struct SRP_talker talker;
	void *fd = &mrpdev;

	sid[0] = 0x00;
	sid[1] = 0x10;
	sid[2] = 0xa1;
	sid[3] = 0x98;
	sid[4] = 0x97;
	sid[5] = 0x05;
	sid[6] = 0x00;
	sid[7] = 0x01;
	uid[0] = 0x00;
	uid[1] = 0x01;
	bid[0] = 0x00;
	bid[1] = 0x10;
	bid[2] = 0xa1;
	bid[3] = 0x98;
	sid[4] = 0x97;
	bid[5] = 0x05;
	bid[6] = 0x00;
	bid[7] = 0x01;
	dest[0] = 0x01;
	dest[1] = 0x80;
	dest[2] = 0xce;
	dest[3] = 0x00;
	dest[4] = 0x01;
	dest[5] = 0x01;
	memcpy(talker.id, sid, 8);
	memcpy(talker.dest, dest, ETH_ALEN);
	talker.vlan_id = vid;
	talker.priority = srp_priority;
	talker.rank = srp_rank;
	talker.MaxFrameSize = srp_frame;
	talker.MaxIntervalFrames = srp_interval;
	talker.AccumulatedLatency = srp_latency;
	memcpy(talker.bridge_id, bid, 8);
	talker.FailureCode = srp_code;
	do {
		printf("> ");
		if (fgets(line, 80, fp) == NULL)
			break;
		cmd[0] = '\0';
		count = sscanf(line, "%s %u %u %u %u %u %u %u %u %u %u", cmd,
			(unsigned int *) &num[0],
			(unsigned int *) &num[1],
			(unsigned int *) &num[2],
			(unsigned int *) &num[3],
			(unsigned int *) &num[4],
			(unsigned int *) &num[5],
			(unsigned int *) &num[6],
			(unsigned int *) &num[7],
			(unsigned int *) &num[8],
			(unsigned int *) &num[9]);
		hex[0] = 0;
		hcount = sscanf(line, "%s %x %x %x %x %x %x %x %x %x %x", cmd,
			(unsigned int *) &hex[0],
			(unsigned int *) &hex[1],
			(unsigned int *) &hex[2],
			(unsigned int *) &hex[3],
			(unsigned int *) &hex[4],
			(unsigned int *) &hex[5],
			(unsigned int *) &hex[6],
			(unsigned int *) &hex[7],
			(unsigned int *) &hex[8],
			(unsigned int *) &hex[9]);
		if (count > 1 && !num[0] && hex[0])
			for (rc = 0; rc < count - 1; rc++)
				num[rc] = hex[rc];
		if (!strcmp(cmd, "sid") || !strcmp(cmd, "bid")) {
			u8 *id;

			count = sscanf(line, "%s %x:%x:%x:%x:%x:%x:%x:%x", cmd,
				&num[0], &num[1], &num[2], &num[3],
				&num[4], &num[5], &num[6], &num[7]);
			if (!strcmp(cmd, "sid"))
				id = sid;
			else
				id = bid;
			if (count >= 9) {
				for (count = 0; count < 8; count++)
					id[count] = (u8) num[count];
				if (!strcmp(cmd, "sid")) {
					uid[0] = sid[6];
					uid[1] = sid[7];
				}
			}
			print_id(id);
			printf("\n");
		} else if (!strcmp(cmd, "uid")) {
			count = sscanf(line, "%s %x:%x", cmd,
				&num[0], &num[1]);
			if (count >= 3) {
				for (count = 0; count < 2; count++)
					uid[count] = (u8) num[count];
				sid[6] = uid[0];
				sid[7] = uid[1];
			}
			printf("%02x.%02x\n",
				uid[0],
				uid[1]);
		} else if (!strcmp(cmd, "dest")) {
			count = sscanf(line, "%s %x:%x:%x:%x:%x:%x", cmd,
				&num[0], &num[1], &num[2], &num[3],
				&num[4], &num[5]);
			if (count >= 7) {
				for (count = 0; count < 6; count++)
					dest[count] = (u8) num[count];
				memcpy(mac.addr, dest, 6);
				memcpy(talker.dest, dest, 6);
			}
			print_addr(dest);
			printf("\n");
		} else if (!strcmp(cmd, "vid")) {
			if (count >= 2) {
				if (0 < num[0] && num[0] < 0xfff) {
					vid = num[0];
					vlan.id = num[0];
					talker.vlan_id = num[0];
				}
			} else
				printf("vid = %d\n", vid);
		} else if (!strcmp(cmd, "nd")) {
			if (sid[7] < 255)
				sid[7]++;
			if (dest[5] < 255)
				dest[5]++;
		} else if (!strcmp(cmd, "pd")) {
			if (sid[7])
				sid[7]--;
			if (dest[5])
				dest[5]--;
		} else if ('m' == line[1]) {
			memcpy(mac.addr, dest, ETH_ALEN);
			switch (line[0]) {
			case 'r':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= hex[1] && hex[1] <= 0xff)
						mac.addr[5] = hex[1];
				}
				rc = set_mac_rx(fd, num[0], &mac);
				print_mrp_err(rc);
				break;
			case 'v':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= hex[1] && hex[1] <= 0xff)
						mac.addr[5] = hex[1];
				}
				rc = set_mac_lv(fd, num[0], &mac);
				print_mrp_err(rc);
				break;
			case 'a':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= hex[1] && hex[1] <= 0xff)
						mac.addr[5] = hex[1];
				}
				rc = set_mac_on(fd, num[0], &mac);
				print_mrp_err(rc);
				break;
			case 'z':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= hex[1] && hex[1] <= 0xff)
						mac.addr[5] = hex[1];
				}
				rc = set_mac_off(fd, num[0], &mac);
				print_mrp_err(rc);
				break;
			case 'm':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= hex[1] && hex[1] <= 0xff)
						mac.addr[5] = hex[1];
				}
				rc = set_mac_decl(fd, num[0], &mac);
				print_mrp_err(rc);
				break;
			case 'n':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= hex[1] && hex[1] <= 0xff)
						mac.addr[5] = hex[1];
				}
				rc = set_mac_drop(fd, num[0], &mac);
				print_mrp_err(rc);
				break;
			case 'd':
				break;
			}
		} else if ('v' == line[1]) {
			switch (line[0]) {
			case 'r':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = vid;
				else if (num[1] <= 0 || num[1] >= 0xfff) {
					break;
				}
				vlan.id = num[1];
				rc = set_vlan_rx(fd, num[0], &vlan);
				print_mrp_err(rc);
				break;
			case 'v':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = vid;
				else if (num[1] <= 0 || num[1] >= 0xfff) {
					break;
				}
				vlan.id = num[1];
				rc = set_vlan_lv(fd, num[0], &vlan);
				print_mrp_err(rc);
				break;
			case 'a':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = vid;
				else if (num[1] <= 0 || num[1] >= 0xfff) {
					break;
				}
				vlan.id = num[1];
				rc = set_vlan_on(fd, num[0], &vlan);
				print_mrp_err(rc);
				break;
			case 'z':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = vid;
				else if (num[1] <= 0 || num[1] >= 0xfff) {
					break;
				}
				vlan.id = num[1];
				rc = set_vlan_off(fd, num[0], &vlan);
				print_mrp_err(rc);
				break;
			case 'm':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = vid;
				else if (num[1] <= 0 || num[1] >= 0xfff) {
					break;
				}
				vlan.id = num[1];
				rc = set_vlan_decl(fd, num[0], &vlan);
				print_mrp_err(rc);
				break;
			case 'n':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = vid;
				else if (num[1] <= 0 || num[1] >= 0xfff) {
					break;
				}
				vlan.id = num[1];
				rc = set_vlan_drop(fd, num[0], &vlan);
				print_mrp_err(rc);
				break;
			}
		} else if ('d' == line[1]) {
			switch (line[0]) {
			case 'r':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = SR_CLASS_B_ID;
				if (count < 4)
					num[2] = srp_priority;
				if (count < 5)
					num[3] = vid;
				domain.id = num[1];
				domain.priority = num[2];
				domain.vlan_id = num[3];
				rc = set_domain_rx(fd, num[0], &domain);
				print_mrp_err(rc);
				break;
			case 'v':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = SR_CLASS_B_ID;
				if (count < 4)
					num[2] = srp_priority;
				if (count < 5)
					num[3] = vid;
				domain.id = num[1];
				domain.priority = num[2];
				domain.vlan_id = num[3];
				rc = set_domain_lv(fd, num[0], &domain);
				print_mrp_err(rc);
				break;
			case 'm':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = SR_CLASS_B_ID;
				if (count < 4)
					num[2] = srp_priority;
				if (count < 5)
					num[3] = vid;
				domain.id = num[1];
				domain.priority = num[2];
				domain.vlan_id = num[3];
				rc = set_domain_decl(fd, num[0], &domain);
				print_mrp_err(rc);
				break;
			case 'n':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = SR_CLASS_B_ID;
				if (count < 4)
					num[2] = srp_priority;
				if (count < 5)
					num[3] = vid;
				domain.id = num[1];
				domain.priority = num[2];
				domain.vlan_id = num[3];
				rc = set_domain_drop(fd, num[0], &domain);
				print_mrp_err(rc);
				break;
			}
		} else if ('l' == line[1]) {
			memcpy(listener.id, sid, 8);
			switch (line[0]) {
			case 'r':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = srp_state;
				else if (num[1] < 0 || num[1] > 3) {
					break;
				}
				if (count > 3) {
					if (0 <= num[2] && num[2] <= 0xff)
						listener.id[7] = num[2];
				}
				listener.substate = num[1];
				rc = set_listener_rx(fd, num[0], &listener);
				if (DEV_IOC_MRP_REPORT == rc)
					printf("->\n");
				print_mrp_err(rc);
				break;
			case 'v':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count < 3)
					num[1] = srp_state;
				else if (num[1] < 0 || num[1] > 3) {
					break;
				}
				if (count > 3) {
					if (0 <= num[2] && num[2] <= 0xff)
						listener.id[7] = num[2];
				}
				listener.substate = num[1];
				rc = set_listener_lv(fd, num[0], &listener);
				if (DEV_IOC_MRP_REPORT == rc)
					printf("->\n");
				print_mrp_err(rc);
				break;
			case 'a':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= num[1] && num[1] <= 0xff)
						listener.id[7] = num[1];
				}
				listener.substate = SRP_READY;
				rc = set_listener_on(fd, num[0], &listener);
				print_mrp_err(rc);
				break;
			case 'z':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= num[1] && num[1] <= 0xff)
						listener.id[7] = num[1];
				}
				listener.substate = SRP_ASKING_FAILED;
				rc = set_listener_off(fd, num[0], &listener);
				print_mrp_err(rc);
				break;
			case 'm':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= num[1] && num[1] <= 0xff)
						listener.id[7] = num[1];
				}
				listener.substate = SRP_READY;
				rc = set_listener_decl(fd, num[0], &listener);
				print_mrp_err(rc);
				break;
			case 'n':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= num[1] && num[1] <= 0xff)
						listener.id[7] = num[1];
				}
				listener.substate = SRP_ASKING_FAILED;
				rc = set_listener_drop(fd, num[0], &listener);
				print_mrp_err(rc);
				break;
			case 'd':
				break;
			case 's':
				if (count >= 2) {
					srp_state = num[0];
					listener.substate = num[0];
				} else
					printf("state = %d\n", srp_state);
				break;
			case 'l':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					rc = set_port_speed(fd, num[0],
						num[1]);
					print_mrp_err(rc);
				} else {
					int speed;

					rc = get_port_speed(fd, num[0],
						&speed);
					print_mrp_err(rc);
					printf("speed = %d\n", speed);
				}
				break;
			}
		} else if ('t' == line[1]) {
			memcpy(talker.id, sid, 8);
			memcpy(talker.dest, dest, ETH_ALEN);
			talker.vlan_id = vid;
			talker.priority = srp_priority;
			talker.rank = srp_rank;
			talker.MaxFrameSize = srp_frame;
			talker.MaxIntervalFrames = srp_interval;
			talker.AccumulatedLatency = srp_latency;
			memcpy(talker.bridge_id, bid, 8);
			talker.FailureCode = srp_code;
			switch (line[0]) {
			case 'r':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= num[1] && num[1] <= 0xff) {
						talker.id[7] = num[1];
						talker.dest[5] = num[1];
					}
				}
				rc = set_talker_rx(fd, num[0], &talker);
				if (DEV_IOC_MRP_REPORT == rc)
					printf("->\n");
				print_mrp_err(rc);
				break;
			case 'v':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= num[1] && num[1] <= 0xff) {
						talker.id[7] = num[1];
						talker.dest[5] = num[1];
					}
				}
				rc = set_talker_lv(fd, num[0], &talker);
				if (DEV_IOC_MRP_REPORT == rc)
					printf("->\n");
				print_mrp_err(rc);
				break;
			case 'a':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= num[1] && num[1] <= 0xff) {
						talker.id[7] = num[1];
						talker.dest[5] = num[1];
					}
				}
				rc = set_talker_on(fd, num[0], &talker);
				print_mrp_err(rc);
				break;
			case 'z':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= num[1] && num[1] <= 0xff) {
						talker.id[7] = num[1];
						talker.dest[5] = num[1];
					}
				}
				rc = set_talker_off(fd, num[0], &talker);
				print_mrp_err(rc);
				break;
			case 'm':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= num[1] && num[1] <= 0xff) {
						talker.id[7] = num[1];
						talker.dest[5] = num[1];
					}
				}
				rc = set_talker_decl(fd, num[0], &talker);
				print_mrp_err(rc);
				break;
			case 'n':
				if (count < 2)
					break;
				if (num[0] > mrp_ports)
					break;
				if (count > 2) {
					if (0 <= num[1] && num[1] <= 0xff) {
						talker.id[7] = num[1];
						talker.dest[5] = num[1];
					}
				}
				rc = set_talker_drop(fd, num[0], &talker);
				print_mrp_err(rc);
				break;
			case 'd':
				rc = set_talker_dbg(fd, 0, &talker);
				print_mrp_err(rc);
				break;
			case 'f':
				if (count >= 2) {
					srp_frame = num[0];
					talker.MaxFrameSize = num[0];
				} else
					printf("frame = %d\n", srp_frame);
				break;
			case 'i':
				if (count >= 2) {
					srp_interval = num[0];
					talker.MaxIntervalFrames = num[0];
				} else
					printf("interval = %d\n",
						srp_interval);
				break;
			case 'l':
				if (count >= 2) {
					srp_latency = num[0];
					talker.AccumulatedLatency = num[0];
				} else
					printf("latency = %d\n", srp_latency);
				break;
			case 'p':
				if (count >= 2) {
					if (0 <= num[0] && num[0] <= 7) {
						srp_priority = num[0];
						talker.priority = num[0];
					}
				} else
					printf("priority = %d\n",
						srp_priority);
				break;
			case 'k':
				if (count >= 2) {
					if (0 <= num[0] && num[0] <= 1) {
						srp_rank = num[0];
						talker.rank = num[0];
					}
				} else
					printf("rank = %d\n", srp_rank);
				break;
			case 'c':
				if (count >= 2) {
					srp_code = num[0];
					talker.FailureCode = num[0];
				} else
					printf("code = %d\n", srp_code);
				break;
			}
		} else
		switch (line[0]) {
		case 'g':
			proc_get_attribute();
			break;
		case 'h':
			printf("\tsid [stream id]\n");
			printf("\tuid [stream unique id]\n");
			printf("\tbid [bridge id]\n");
			printf("\tvid [vlan id]\n");
			printf("\tdest [mac address]\n");
			printf("\tg\n");
			printf("\n");
			printf("\trm port [:::::dest]\t\trx mac\n");
			printf("\tvm port [:::::dest]\t\tlv mac\n");
			printf("\tam port\t\t\t\tactivate mac\n");
			printf("\tzm port\t\t\t\tdisable mac\n");
			printf("\tmm port\t\t\t\tdeclare mac\n");
			printf("\tnm port\t\t\t\tdrop mac\n");
			printf("\trv port [vid]\t\t\trx vlan\n");
			printf("\tvv port [vid]\t\t\tlv vlan\n");
			printf("\tav port\t\t\t\tactivate vlan\n");
			printf("\tzv port\t\t\t\tdisable vlan\n");
			printf("\tmv port\t\t\t\tdeclare vlan\n");
			printf("\tnv port\t\t\t\tdrop vlan\n");
			printf("\n");
			printf("\trd port [id] [prio] [vid]\trx domain\n");
			printf("\tvd port [id] [prio] [vid]\tlv domain\n");
			printf("\tmd port [id] [prio] [vid]\tdeclare domain\n");
			printf("\tnd port [id] [prio] [vid]\tdrop domain\n");
			printf("\n");
			printf("\trl port [substate]\t\trx listener\n");
			printf("\tvl port [substate]\t\tlv listener\n");
			printf("\tal port\t\t\t\tactivate listener\n");
			printf("\tzl port\t\t\t\tdisable listener\n");
			printf("\tml port\t\t\t\tdeclare listener\n");
			printf("\tnl port\t\t\t\tdrop listener\n");
			printf("\tsl [substate]\n");
			printf("\tll port [speed]\n");
			printf("\n");
			printf("\trt port\t\t\t\trx talker\n");
			printf("\tvt port\t\t\t\tlv talker\n");
			printf("\tat port\t\t\t\tactivate talker\n");
			printf("\tzt port\t\t\t\tdisable talker\n");
			printf("\tmt port\t\t\t\tdeclare talker\n");
			printf("\tnt port\t\t\t\tdrop talker\n");
			printf("\tpt [priority]\n");
			printf("\tkt [rank]\n");
			printf("\tft [MaxFrameSize]\n");
			printf("\tit [MaxIntervalFrames]\n");
			printf("\tlt [AccumulatedLatency]\n");
			printf("\tct [FailureCode]\n");
			printf("\tdt \t\t\t\tdebug\n");
			printf("\n");
			break;
		case 'q':
			cont = 0;
			break;
		}
	} while (cont);
}

int main(int argc, char *argv[])
{
	int rc;

	if (argc < 2) {
		printf("usage: %s <local_if>\n", argv[0]);
		return 1;
	}
	strncpy(mrpdev.name, argv[1], sizeof(mrpdev.name));
	mrpdev.sock = socket(AF_INET, SOCK_DGRAM, 0);

	rc = mrp_dev_init(&mrpdev, 0, &mrp_version, &mrp_ports);
	if (rc) {
		print_mrp_err(rc);
		return rc;
	}
	printf("version=%d ports=%d\n", mrp_version, mrp_ports);

	/* Include the host port for a switch. */
	if (mrp_ports > 1)
		mrp_ports++;
	get_cmd(stdin);
	rc = mrp_dev_exit(&mrpdev);
	close(mrpdev.sock);

	return 0;
}
