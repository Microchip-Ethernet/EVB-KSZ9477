#ifndef __DLR_HSR_DEMO__H__
#define __DLR_HSR_DEMO__H__
#pragma pack(push) 
#pragma pack(1)

#ifndef Boolean
#define Boolean  int
#define MCHP_TRUE	1
#define MCHP_FALSE	0
#endif

#define CMD_PORT	8128
#define EVENT_PORT	8129
#define EVENT_DATA_SIZE	128
#define DEMO_MAGICNUMBER     0xB234838A

typedef enum{
DLR_BACKUP_SUPER=0,
DLR_ACTIVE_SUPER=1,
DLR_RING_NODE=2,
DLR_NOT_IN_DLR=3,
DLR_NOT_SUPPORT_BEACON=4,
}DLR_SUPERVISOR_STATUS;

typedef enum
{
DLR_NET_NORMAL=0,
DLR_RING_FAULT,
DLR_UNEXPECTED_LOOP,
DLR_PARTIAL_NET_FAULT,
DLR_RAPID_FAULT_CYCLE,
}DLR_NET_STATUS;

typedef struct{
unsigned long dlr_supervisor_status;
}DLR_SUPERVISOR_STATUS_DATA;


typedef struct{
Boolean enable;
unsigned long precedence;
unsigned long beacon_interval;
unsigned long beacon_timeout;
unsigned long vlanid;
}DLR_SUPERVISOR;


typedef struct{
unsigned long dlr_faults_count;
}DLR_FAULTS_COUNT;

typedef struct{
char  ipv4[20];
unsigned char mac[6];
}DLR_NODE_INFO;

typedef struct{
unsigned long dlr_ring_nodes_count;
}DLR_NODES_COUNT; 

typedef struct{
unsigned long ring_nodes;	
DLR_NODE_INFO node_info[1]; /*is for all nodes list.*/
}DLR_NODES_LIST_INFO;

typedef struct
{
long /*DLR_NET_STATUS*/ net_status;
}DLR_NET_STATUS_INFO;

typedef enum {
DLR_QUERY_NETWORK=0,
DLR_GET_NET_STATUS,
DLR_GET_SUPERVISOR_STATUS,
DLR_GET_SUPERVISOR,
DLR_SET_SUPERVISOR,
DLR_GET_FAULTS_COUNT,
DLR_GET_RING_NODES,
DLR_GET_RING_NODES_LIST,
DLR_GET_RING_FAULT_INFO,
DLR_GET_SUPERVISOR_ADDR,
}DLR_HSR_CMD;

typedef struct {
	unsigned long	magic_number;
	unsigned long pktsize;
	unsigned long	return_code; /* MCHP_TRUE /MCHP_FALSE*/
	long /*DLR_HSR_CMD*/		cmd;
	unsigned  char  cmd_data[1];
}CMD_PKT;

/*****************  event packet ********************/
#define EVENT_ACK_TIMEOUT		500 /*300 milliseconds*/

typedef struct{
unsigned long	magic_number;
unsigned long	event;
unsigned char	event_data[EVENT_DATA_SIZE];
}EVENT_PKT;

typedef enum{
DLR_REPORT_NODE_INFO=0,
DLR_SUPERVISOR_SELECTED,
DLR_RING_FAULT_DETECTED,
DLR_RING_RESTORED,
EVENT_ACK,
}DLR_HSR_EVENT;

#define PORT1_DOWN			0x01
#define PORT2_DOWN			0x02
#define PORT1_LOST			0x04
#define PORT2_LOST			0x08


typedef struct {
	DLR_NODE_INFO last_active_node_on_port1;
	DLR_NODE_INFO last_active_node_on_port2;
	unsigned long fault_bitmap;
}DLR_RING_FAULT_INFO; 

typedef struct {
DLR_NODE_INFO nodeinfo;
long /*DLR_SUPERVISOR_STATUS*/ status;
}DLR_NODE_REPORT;

typedef struct{
 char	  ipv4[20];
 unsigned char mac[6];
 unsigned long precedence;
 unsigned long beacon_interval;
 unsigned long beacon_timeout;
 unsigned long vlanid;
}DLR_SUPERVISOR_SELECTED_INFO;

#pragma pack(pop) 
#endif //__DLR_HSR_DEMO__H__