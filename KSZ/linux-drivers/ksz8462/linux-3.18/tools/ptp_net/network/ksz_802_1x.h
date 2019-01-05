

#ifndef KSZ_802_1X_H
#define KSZ_802_1X_H


struct eapol_frame {
	u8 version;
	u8 type;
	u16 len;
} __packed;

#define EAP_PACKET			0
#define EAPOL_START			1
#define EAPOL_LOGOFF			2
#define EAPOL_KEY			3
#define EAPOL_ENCAPSULATED_ASF_ALER	4

struct eap_frame {
	u8 code;
	u8 id;
	u16 len;
} __packed;

struct eap_body {
	u8 type;
};

#define EAP_CODE_REQUEST		1
#define EAP_CODE_RESPONSE		2
#define EAP_CODE_SUCCESS		3
#define EAP_CODE_FAILURE		4


#define EAP_TYPE_IDENTITY		1
#define EAP_TYPE_NAK			3
#define EAP_TYPE_MD5_CHALLENGE		4
#define EAP_TYPE_PEAP			25

struct radius_frame {
	u8 code;
	u8 id;
	u16 len;
	u8 vector[16];
} __packed;

#define RADIUS_CODE_ACCESS_REQUEST	1
#define RADIUS_CODE_ACCESS_ACCEPT	2
#define RADIUS_CODE_ACCESS_REJECT	3
#define RADIUS_CODE_ACCNT_REQUEST	4
#define RADIUS_CODE_ACCNT_RESPONSE	5
#define RADIUS_CODE_ACCNT_STATUS	6
#define RADIUS_CODE_PASSWORD_REQUEST	7
#define RADIUS_CODE_PASSWORD_ACCEPT	8
#define RADIUS_CODE_PASSWORD_REJECT	9
#define RADIUS_CODE_ACCNT_MESSAGE	10
#define RADIUS_CODE_ACCESS_CHALLENGE	11
#define RADIUS_CODE_STATUS_SERVER	12
#define RADIUS_CODE_STATUS_CLIENT	13

struct radius_attrib {
	u8 val;
	u8 len;
} __packed;

#define RADIUS_USER_NAME		1
#define RADIUS_USER_PASSWORD		2
#define RADIUS_CHAP_PASSWORD		3
#define RADIUS_NAS_IP_ADDRESS		4
#define RADIUS_NAS_PORT			5
#define RADIUS_SERVICE_TYPE		6
#define SERVICE_TYPE_FRAMED		2
#define RADIUS_FRAMED_PROTOCOL		7
#define RADIUS_FRAMED_IP_ADDRESS	8
#define FRAMED_IP_ADDRESS_ASSIGNED	0xfffffffe
#define RADIUS_FRAMED_MTU		12
#define RADIUS_REPLY_MESSAGE		18
#define RADIUS_STATE			24
#define RADIUS_CALLED_STATION_ID	30
#define RADIUS_CALLING_STATION_ID	31
#define RADIUS_CHAP_CHALLENGE		60
#define RADIUS_NAS_PORT_TYPE		61
#define NAS_PORT_TYPE_ETHERNET		15
#define RADIUS_EAP_MESSAGE		79
#define RADIUS_MESSAGE_AUTHENTICATOR	80

struct radius_packet {
	u8 *data;
	u8 code;
	u16 data_len;
	int offset;
	u8 state[16];
	u8 vector[16];
};

typedef struct radius_packet RADIUS_PACKET;

struct radius_info {
	u8 code;
	u8 id;
	u8 eap_id;
	u8 eap_code;
	u8 eap_type;
	u8 *eap_data;
	u8 dst[ETH_ALEN];
	u8 src[ETH_ALEN];
	u8 ip_addr[4];
	u16 port;
	u16 mtu;
	u32 framed;
	u8 state[16];
	u16 state_len;
	u8 eap[1500];
	u16 eap_len;
	u8 msg[80];
	u16 msg_len;
	u8 name[80];
	u16 name_len;
	u8 password[129];
	u8 encrypted[128];
	size_t password_len;
	u8 authen[16];

	int len;
	int sent;
	u8 radius_data[1600];
	struct radius_frame *frame;
	struct radius_packet packet;
	struct radius_packet original;
};


#endif
