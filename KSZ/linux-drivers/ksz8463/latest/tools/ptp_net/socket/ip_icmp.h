#ifndef _IP_ICMP_H
#define _IP_ICMP_H


struct ip {
    uint8_t        ip_hl:4;
    uint8_t        ip_v:4;
    uint8_t        ip_tos;
    u_short        ip_len;
    u_short        ip_id;
    u_short        ip_off;
    uint8_t        ip_ttl;
    uint8_t        ip_p;
    u_short        ip_sum;
    struct in_addr ip_src;
    struct in_addr ip_dst;
};


struct icmp {
    uint8_t  icmp_type;
    uint8_t  icmp_code;
    uint16_t icmp_cksum;

    union {
        uint8_t ih_pptr;
        struct {
            uint16_t icd_id;
            uint16_t icd_seq;
        } ih_idseq;
        uint32_t ih_void;
    } icmp_hun;

#define icmp_pptr   icmp_hun.ih_pptr
#define icmp_id     icmp_hun.ih_idseq.icd_id
#define icmp_seq    icmp_hun.ih_idseq.icd_seq
#define icmp_void   icmp_hun.ih_void

    union {
        struct {
            uint32_t its_otime;
            uint32_t its_rtime;
            uint32_t its_ttime;
        } id_ts;
        uint32_t id_mask;
        uint8_t id_data[ 1 ];
    } icmp_dun;

#define icmp_otime  icmp_dun.id_ts.its_otime
#define icmp_rtime  icmp_dun.id_ts.its_rtime
#define icmp_ttime  icmp_dun.id_ts.its_ttime
#define icmp_mask   icmp_dun.id_mask
#define icmp_data   icmp_dun.id_data
};


#define ICMP_ECHOREPLY      0
#define ICMP_ECHO           8
#define ICMP_TSTAMP         13
#define ICMP_TSTAMPREPLY    14
#define ICMP_INFO_REQUEST   15
#define ICMP_INFO_REPLY     16


u_short in_cksum ( u_short* addr, int len );

#endif
