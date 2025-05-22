

#ifndef KSZ_WEB_H
#define KSZ_WEB_H


struct web_attributes {
	int dev_info;
	int tgt_info;
	int dynamic_table;
	int static_table;
	int static_cfg;
	int vlan_table;
	int vlan;
	int jumbo_packet;
	int mtu;
	int port_status;
	int pvid;
};

enum {
	WEB_GET_DEV_INFO,
	WEB_GET_TGT_INFO,
	WEB_DYNAMIC,
	WEB_STATIC,
	WEB_STATIC_CFG,
	WEB_VLAN,
	WEB_ENABLE_VLAN,
	WEB_ENABLE_JUMBO_PACKET,
	WEB_SET_MTU,
	WEB_SET_PORT_STATUS,
	WEB_SET_PVID,
};

#endif
