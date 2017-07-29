#ifndef _NET_MRP_H
#define _NET_MRP_H

#define MRP_END_MARK		0x0

struct mrp_pdu_hdr {
	u8	version;
};

struct mrp_msg_hdr {
	u8	attrtype;
	u8	attrlen;
};

struct mrp_vecattr_hdr {
	__be16	lenflags;
	unsigned char	firstattrvalue[];
#define MRP_VECATTR_HDR_LEN_MASK cpu_to_be16(0x1FFF)
#define MRP_VECATTR_HDR_FLAG_LA cpu_to_be16(0x2000)
};

enum mrp_vecattr_event {
	MRP_VECATTR_EVENT_NEW,
	MRP_VECATTR_EVENT_JOIN_IN,
	MRP_VECATTR_EVENT_IN,
	MRP_VECATTR_EVENT_JOIN_MT,
	MRP_VECATTR_EVENT_MT,
	MRP_VECATTR_EVENT_LV,
	__MRP_VECATTR_EVENT_MAX
};

struct mrp_skb_cb {
	struct mrp_msg_hdr	*mh;
	struct mrp_vecattr_hdr	*vah;
	unsigned char		attrvalue[];
};

static inline struct mrp_skb_cb *mrp_cb(struct sk_buff *skb)
{
	BUILD_BUG_ON(sizeof(struct mrp_skb_cb) >
		     FIELD_SIZEOF(struct sk_buff, cb));
	return (struct mrp_skb_cb *)skb->cb;
}

enum mrp_applicant_state {
	MRP_APPLICANT_INVALID,
	MRP_APPLICANT_VO,
	MRP_APPLICANT_VP,
	MRP_APPLICANT_VN,
	MRP_APPLICANT_AN,
	MRP_APPLICANT_AA,
	MRP_APPLICANT_QA,
	MRP_APPLICANT_LA,
	MRP_APPLICANT_AO,
	MRP_APPLICANT_QO,
	MRP_APPLICANT_AP,
	MRP_APPLICANT_QP,
	MRP_APPLICANT_LO,
	__MRP_APPLICANT_MAX
};
#define MRP_APPLICANT_MAX	(__MRP_APPLICANT_MAX - 1)

enum mrp_registrar_state {
	MRP_REGISTRAR_INVALID,
	MRP_REGISTRAR_MT,
	MRP_REGISTRAR_IN,
	MRP_REGISTRAR_LV,
	__MRP_REGISTRAR_MAX
};
#define MRP_REGISTRAR_MAX	(__MRP_REGISTRAR_MAX - 1)

enum mrp_event {
	MRP_EVENT_NEW,
	MRP_EVENT_JOIN,
	MRP_EVENT_LV,
	MRP_EVENT_TX,
	MRP_EVENT_TX_LA,
	MRP_EVENT_TX_LAF,
	MRP_EVENT_R_NEW,
	MRP_EVENT_R_JOIN_IN,
	MRP_EVENT_R_IN,
	MRP_EVENT_R_JOIN_MT,
	MRP_EVENT_R_MT,
	MRP_EVENT_R_LV,
	MRP_EVENT_R_LA,
	MRP_EVENT_REDECLARE,
	MRP_EVENT_PERIODIC,
	MRP_EVENT_PERIODIC_DISABLE,
	MRP_EVENT_PERIODIC_ENABLE,
	MRP_EVENT_LV_TIMER,
	MRP_EVENT_LVA_TIMER,
	MRP_EVENT_FLUSH,
	__MRP_EVENT_MAX
};
#define MRP_EVENT_MAX		(__MRP_EVENT_MAX - 1)

enum mrp_tx_action {
	MRP_TX_ACTION_NONE,
	MRP_TX_ACTION_S_NEW,
	MRP_TX_ACTION_S_JOIN_IN,
	MRP_TX_ACTION_S_JOIN_IN_OPTIONAL,
	MRP_TX_ACTION_S_IN,
	MRP_TX_ACTION_S_IN_OPTIONAL,
	MRP_TX_ACTION_S_LV,
};

enum mrp_notification {
	MRP_NOTIFY_NONE,
	MRP_NOTIFY_NEW,
	MRP_NOTIFY_JOIN,
	MRP_NOTIFY_LV,
};

enum mrp_timer_state {
	MRP_TIMER_PASSIVE,
	MRP_TIMER_ACTIVE,
};

struct mrp_attr {
	struct rb_node			node;
	enum mrp_applicant_state	state;
	enum mrp_applicant_state	new_state;
	enum mrp_tx_action		action;
	enum mrp_registrar_state	reg_state;
	enum mrp_notification		notify;
	u8				aging;
	u8				type;
	u8				len;
	unsigned char			value[];
};

struct mrp_lva {
	enum mrp_timer_state		state;
	u8				rx;
	u8				tx;
};

struct mrp_periodic {
	enum mrp_timer_state		state;
};

enum mrp_applications {
	MRP_APPLICATION_MVRP,
	MRP_APPLICATION_MMRP,
	MRP_APPLICATION_MSRP,
	__MRP_APPLICATION_MAX
};
#define MRP_APPLICATION_MAX	(__MRP_APPLICATION_MAX - 1)

struct mrp_application {
	enum mrp_applications	type;
	unsigned int		maxattr;
	struct packet_type	pkttype;
	unsigned char		group_address[ETH_ALEN];
	u8			version;
};

struct mrp_applicant {
	struct mrp_application	*app;
	struct net_device	*dev;
	struct mrp_lva		lva;
	struct mrp_periodic	periodic;
	struct work_struct	join_work;
	struct work_struct	periodic_work;
	struct work_struct	leave_work;
	struct work_struct	lva_work;
	struct timer_list	join_timer;
	struct timer_list	periodic_timer;
	struct timer_list	leave_timer;
	struct timer_list	lva_timer;
	struct {
		u8 join:1;
		u8 periodic:1;
		u8 leave:1;
		u8 lva:1;
	} timer_arm;
	u8 p2p_mac:1;
	u8 rx:1;
	struct rb_node		*last_node;
	void *parent;
	u8 lva_type;
	u8 port;
	unsigned long rla_jiffies;
	void (*attrval_inc)(void *value, u8 len);
	int (*attr_chk)(u8 attrtype, u8 attrlen);
	int (*attr_cmp)(const struct mrp_attr *attr, const void *value,
		u8 len, u8 type);
	u8 (*attr_len)(u8 attrtype, u8 attrlen);
	u8 (*attr_type)(struct mrp_attr *attr);
	void (*attr_upd)(const void *value, struct mrp_attr *attr);
	int (*rxpdu)(struct mrp_applicant *app, u8 *data, int len);
	int (*txpdu)(struct mrp_applicant *app);
	void (*acton)(struct mrp_applicant *app, struct mrp_attr *attr);

	spinlock_t		lock;
	struct sk_buff_head	queue;
	struct sk_buff		*pdu;
	struct rb_root		mad;
	struct rcu_head		rcu;
#ifndef NETIF_F_HW_VLAN_CTAG_FILTER
	struct rnd_state	*rnd;
#endif
};

struct mrp_port {
	struct mrp_applicant __rcu	*applicants[MRP_APPLICATION_MAX + 1];
	struct rcu_head			rcu;
};

int mrp_register_application(struct mrp_application *app);
void mrp_unregister_application(struct mrp_application *app);


#endif /* _NET_MRP_H */
