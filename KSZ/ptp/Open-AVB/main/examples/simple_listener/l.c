/*
Copyright (c) 2013 Katja Rohloff <Katja.Rohloff@uni-jena.de>

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#include <arpa/inet.h>
#include <errno.h>
#include <netinet/if_ether.h>
#include <netinet/in.h>
#if 0
#include <pcap/pcap.h>
#endif
#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/if.h>
#include <netpacket/packet.h>
#include <sys/ioctl.h>
#include <pthread.h>
#include <poll.h>
#if 1
#include <sys/time.h>
#endif

#if 0
#include <sndfile.h>

//#define DEBUG
#define PCAP
#define LIBSND
#endif

#define MAX_MRPD_CMDSZ 1500
#define MRPD_PORT_DEFAULT 7500

#define ETHERNET_HEADER_SIZE 18
#define SEVENTEEN22_HEADER_PART1_SIZE 4
#define STREAM_ID_SIZE 8
#define SEVENTEEN22_HEADER_PART2_SIZE 10
#define SIX1883_HEADER_SIZE 10
#define HEADER_SIZE ETHERNET_HEADER_SIZE + SEVENTEEN22_HEADER_PART1_SIZE + STREAM_ID_SIZE + SEVENTEEN22_HEADER_PART2_SIZE + SIX1883_HEADER_SIZE 

#define SAMPLES_PER_SECOND 48000
#define SAMPLES_PER_FRAME 6
#define CHANNELS 2

struct six1883_sample{
	uint8_t label;
	uint8_t value[3];
};

struct ethernet_header{
	u_char dst[6];
	u_char src[6];
	u_char stuff[4];
	u_char type[2];
};

typedef int (*process_msg) (char *buf, int buflen);

// global
unsigned char stream_id[8];
unsigned char dest_addr[6];
volatile int talker = 0;
int control_socket;
#if 0
pcap_t* handle;
u_char ETHER_TYPE[] = { 0x22, 0xf0 };
SNDFILE* snd_file;
#endif
#if 1
static int use_mac;
#endif

static void help()
{
	fprintf(stderr, "\n"
		"Usage: listener [-h] -i interface -f file_name.wav"
		"\n"
		"Options:\n"
		"    -h  show this message\n"
		"    -i  specify interface for AVB connection\n"
		"    -f  set the name of the output wav-file\n" 
#if 1
		"    -m  use MMRP\n"
		"    -v  use MVRP\n"
		"    -l  test first\n"
		"    -n  test number\n"
		"    -t  test case\n"
		"    -x  extra address\n"
		"    -y  listener failed\n"
		"    -z  skip MRP\n"
#endif
#if 0
		"\n" "%s" "\n");
#else
		"\n");
#endif
	exit(1);
}

#if 0
void pcap_callback(u_char* args, const struct pcap_pkthdr* packet_header, const u_char* packet)
{
	unsigned char* test_stream_id;
	struct ethernet_header* eth_header;
	struct six1883_sample* sample; 
	uint32_t buf;
	uint32_t *mybuf;
	uint32_t frame[2] = { 0 , 0 };

#ifdef DEBUG
	fprintf(stdout,"Got packet.\n");
#endif	

	eth_header = (struct ethernet_header*)(packet);

#ifdef DEBUG
	fprintf(stdout,"Ether Type: 0x%02x%02x\n", eth_header->type[0], eth_header->type[1]);
#endif

	if (0 == memcmp(ETHER_TYPE,eth_header->type,sizeof(eth_header->type)))
	{		
		test_stream_id = (unsigned char*)(packet + ETHERNET_HEADER_SIZE + SEVENTEEN22_HEADER_PART1_SIZE);

#ifdef DEBUG
		fprintf(stderr, "Received stream id: %02x%02x%02x%02x%02x%02x%02x%02x\n ",
			     test_stream_id[0], test_stream_id[1],
			     test_stream_id[2], test_stream_id[3],
			     test_stream_id[4], test_stream_id[5],
			     test_stream_id[6], test_stream_id[7]);
#endif

		if (0 == memcmp(test_stream_id, stream_id, sizeof(STREAM_ID_SIZE)))
		{

#ifdef DEBUG
			fprintf(stdout,"Stream ids matched.\n");
#endif

			//sample = (struct six1883_sample*) (packet + HEADER_SIZE);
			mybuf = (uint32_t*) (packet + HEADER_SIZE);
			for(int i = 0; i < SAMPLES_PER_FRAME * CHANNELS; i += 2)
			{	
				memcpy(&frame[0], &mybuf[i], sizeof(frame));

				frame[0] = ntohl(frame[0]);   /* convert to host-byte order */
				frame[1] = ntohl(frame[1]);
				frame[0] &= 0x00ffffff;       /* ignore leading label */
				frame[1] &= 0x00ffffff;
				frame[0] <<= 8;               /* left-align remaining PCM-24 sample */
				frame[1] <<= 8;

				sf_writef_int(snd_file, frame, 1);
			}
		}	
	}
}
#endif

int create_socket()
{
	struct sockaddr_in addr;
	control_socket = socket(AF_INET, SOCK_DGRAM, 0);
		
	/** in POSIX fd 0,1,2 are reserved */
	if (2 > control_socket)
	{
		if (-1 > control_socket)
			close(control_socket);
	return -1;
	}
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(0);
	
	if(0 > (bind(control_socket, (struct sockaddr*)&addr, sizeof(addr)))) 
	{
		fprintf(stderr, "Could not bind socket.\n");
		close(control_socket);
		return -1;
	}
	return 0;
}

#define ETH_TYPE 0x22F0

unsigned char DEST_ADDR[] = { 0x91, 0xE0, 0xF0, 0x00, 0x0e, 0x80 };

typedef struct __attribute__ ((packed)) {
	uint64_t subtype:7;
	uint64_t cd_indicator:1;
	uint64_t timestamp_valid:1;
	uint64_t gateway_valid:1;
	uint64_t reserved0:1;
	uint64_t reset:1;
	uint64_t version:3;
	uint64_t sid_valid:1;
	uint64_t seq_number:8;
	uint64_t timestamp_uncertain:1;
	uint64_t reserved1:7;
	uint64_t stream_id;
	uint64_t timestamp:32;
	uint64_t gateway_info:32;
	uint64_t length:16;
} seventeen22_header;

/* 61883 CIP with SYT Field */
typedef struct {
	uint16_t packet_channel:6;
	uint16_t format_tag:2;
	uint16_t app_control:4;
	uint16_t packet_tcode:4;
	uint16_t source_id:6;
	uint16_t reserved0:2;
	uint16_t data_block_size:8;
	uint16_t reserved1:2;
	uint16_t source_packet_header:1;
	uint16_t quadlet_padding_count:3;
	uint16_t fraction_number:2;
	uint16_t data_block_continuity:8;
	uint16_t format_id:6;
	uint16_t eoh:2;
	uint16_t format_dependent_field:8;
	uint16_t syt;
} six1883_header;

typedef struct {
	uint8_t label;
	uint8_t value[3];
} six1883_sample;

static int extra_addr;
static int test_first;
static int test_cnt;

int get_1722_socket(char *interface, int *sock)
{
	struct sockaddr_ll addr;
	struct ifreq if_request;
	int lsock;
	int rc;
	struct packet_mreq multicast_req;

	lsock = socket(PF_PACKET, SOCK_RAW, htons(ETH_TYPE));
	if (lsock < 0)
		return -1;
	memset(&if_request, 0, sizeof(if_request));
	strncpy(if_request.ifr_name, interface, sizeof(if_request.ifr_name));
	rc = ioctl(lsock, SIOCGIFINDEX, &if_request);
	if (rc < 0) {
		close(lsock);
		return -1;
	}

#if 1
	memset(&addr, 0, sizeof(addr));
	addr.sll_ifindex = if_request.ifr_ifindex;
	addr.sll_family = AF_PACKET;
	addr.sll_protocol = htons(ETH_TYPE);

	rc = bind(lsock, (struct sockaddr *)&addr, sizeof(addr));
	if (0 != rc) {
		close(lsock);
		return -1;
	}

	rc = setsockopt(lsock, SOL_SOCKET, SO_BINDTODEVICE, interface,
			strlen(interface));
	if (0 != rc) {
		close(lsock);
		return -1;
	}
#endif

	multicast_req.mr_ifindex = if_request.ifr_ifindex;
	multicast_req.mr_type = PACKET_MR_MULTICAST;
	multicast_req.mr_alen = 6;
	memcpy(multicast_req.mr_address, dest_addr, 6);

	rc = setsockopt(lsock, SOL_PACKET, PACKET_ADD_MEMBERSHIP,
			&multicast_req, sizeof(multicast_req));
	if (0 != rc) {
		close(lsock);
		return -1;
	}

	*sock = lsock;
	return 0;
}

#if 1
void process_1722(int sock)
{
	int len;
	int addr_len = sizeof(struct sockaddr_in);
	struct sockaddr_in client_addr;
	unsigned char *buf;
	seventeen22_header *header0;
	six1883_header *header1;
	six1883_sample *sample;
	uint16_t *vlanhdr;
	uint16_t *ethtype;
	int i;

	buf = malloc(2000);
	if (NULL == buf) {
		return;
	}
	len = recvfrom(sock, buf, 2000, 0, (struct sockaddr *) &client_addr,
		&addr_len);
#if 0
	memcpy(tmp_packet, DEST_ADDR, sizeof(DEST_ADDR));
	memcpy(tmp_packet + 6, STATION_ADDR, sizeof(STATION_ADDR));
#endif

	/* Q-tag */
	vlanhdr = (uint16_t *) &buf[12];
	i = 12;
	if (0x8100 == ntohs(*vlanhdr))
		i += 4;
#if 0
	tmp_packet[12] = 0x81;
	tmp_packet[13] = 0x00;
	tmp_packet[14] = ((a_priority << 13 | a_vid)) >> 8;
	tmp_packet[15] = ((a_priority << 13 | a_vid)) & 0xFF;
#endif
	ethtype = (uint16_t *) &buf[i];
	i += 2;
#if 0
	tmp_packet[16] = 0x22;	/* 1722 eth type */
	tmp_packet[17] = 0xF0;
#endif

	/* 1722 header update + payload */
	header0 = (seventeen22_header *)(buf + i);
#if 0
	header0->cd_indicator = 0;
	header0->subtype = 0;
	header0->sid_valid = 1;
	header0->version = 0;
	header0->reset = 0;
	header0->reserved0 = 0;
	header0->gateway_valid = 0;
	header0->reserved1 = 0;
	header0->timestamp_uncertain = 0;
	memset(&(header0->stream_id), 0, sizeof(header0->stream_id));
	memcpy(&(header0->stream_id), STATION_ADDR, sizeof(STATION_ADDR));
	header0->length = htons(32);
#endif

	header1 = (six1883_header *)(header0 + 1);
#if 0
	header1->format_tag = 1;
	header1->packet_channel = 0x1F;
	header1->packet_tcode = 0xA;
	header1->app_control = 0x0;
	header1->reserved0 = 0;
	header1->source_id = 0x3F;
	header1->data_block_size = 1;
	header1->fraction_number = 0;
	header1->quadlet_padding_count = 0;
	header1->source_packet_header = 0;
	header1->reserved1 = 0;
	header1->eoh = 0x2;
	header1->format_id = 0x10;
	header1->format_dependent_field = 0x02;
	header1->syt = 0xFFFF;
#endif
	printf("%d: %02x:%02x:%02x:%02x:%02x:%02x %04x %04x %u\n", len,
		buf[0], buf[1], buf[2], buf[3], buf[4], buf[5],
		ntohs(*vlanhdr), ntohs(*ethtype),
		header0->seq_number);
	free(buf);
}
#endif

int msg_process(char *buf, int buflen)
{
	uint32_t id;
	fprintf(stderr, "Msg: %s\n", buf);
 	int l = 0;
#if 0
	if ('S' == buf[l++] && 'N' == buf[l++] && 'E' == buf[l++] && 'T' == buf[++l])
#else
	if (1 == use_mac &&
	    (('M' == buf[0] && 'N' == buf[1] && 'E' == buf[2]) ||
	    ('M' == buf[0] && 'J' == buf[1] && 'O' == buf[2]))) {
		talker = 1;
		return 0;
	}
	if (2 == use_mac &&
	    (('V' == buf[0] && 'N' == buf[1] && 'E' == buf[2]) ||
	    ('V' == buf[0] && 'J' == buf[1] && 'O' == buf[2]))) {
		talker = 1;
		return 0;
	}
	if (('S' == buf[0] && 'N' == buf[1] && 'E' == buf[2]) ||
	    ('S' == buf[0] && 'J' == buf[1] && 'O' == buf[2]))
		l = 4;
	else
		return 0;
#endif
	if ('T' == buf[l++])
	{
		int code;

		while ('S' != buf[l++]);
		l++;
		for(int j = 0; j < 8 ; l+=2, j++)
		{
			sscanf(&buf[l],"%02x",&id);
			stream_id[j] = (unsigned char)id;
		}
		talker = 1;
		l++;
		while ('A' != buf[l++]);
		l++;
		for (int j = 0; j < 6; l += 2, j++)
		{
			sscanf(&buf[l],"%02x",&id);
			dest_addr[j] = (unsigned char) id;
		}
		if (1 == extra_addr)
			dest_addr[5] += 1;
		while ('C' != buf[l++]);
		l++;
		sscanf(&buf[l], "%d", &code);
		if (code)
			talker++;
	}
	return (0);
}

int recv_msg()
{
	char *databuf;
	int bytes = 0;

	databuf = (char *)malloc(2000);
	if (NULL == databuf)
		return -1;

	memset(databuf, 0, 2000);
	bytes = recv(control_socket, databuf, 2000, 0);
	if (bytes <= -1) 
	{
		free(databuf);
		return (-1);
	}
	return msg_process(databuf, bytes);

}

int await_talker()
{
	while (0 == talker)	
		recv_msg();
	return 0;
}

int send_msg(char *data, int data_len)
{
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(MRPD_PORT_DEFAULT);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_aton("127.0.0.1", &addr.sin_addr);
	if (-1 != control_socket)
		return (sendto(control_socket, data, data_len, 0, (struct sockaddr*)&addr, (socklen_t)sizeof(addr)));
	else 
		return 0;
}

int mrp_disconnect()
{
	int rc;
	char *msgbuf = malloc(1500);
	if (NULL == msgbuf)
		return -1;
	memset(msgbuf, 0, 1500);
	sprintf(msgbuf, "BYE");
	rc = send_msg(msgbuf, 1500);

	free(msgbuf);
	return rc;
}
	
int report_domain_status()
{
	int rc;
	char* msgbuf = malloc(1500);

	if (NULL == msgbuf)
		return -1;
	memset(msgbuf, 0, 1500);
	if (1 == use_mac)
		sprintf(msgbuf, "M++:M=%02x%02x%02x%02x%02x%02x",
			DEST_ADDR[0], DEST_ADDR[1], DEST_ADDR[2] + 0,
			DEST_ADDR[3], DEST_ADDR[4], DEST_ADDR[5]);
	else if (2 == use_mac)
		sprintf(msgbuf, "V+?:I=%04x", 2);
	else
	sprintf(msgbuf, "S+D:C=6,P=3,V=0002");
	
	rc = send_msg(msgbuf, 1500);

	free(msgbuf);
	return rc;
}

int send_ready()
{
	char *databuf;
	int rc;
	int substate = 2;
	unsigned char id[2];

	id[0] = stream_id[6];
	id[1] = stream_id[7];
	if (2 == talker || 2 == extra_addr)
		substate = 1;
	databuf = malloc(1500);
	if (NULL == databuf)
		return -1;
	memset(databuf, 0, 1500);
	if (1 == use_mac)
		sprintf(databuf, "M+?:M=%02x%02x%02x%02x%02x%02x",
			DEST_ADDR[0], DEST_ADDR[1], DEST_ADDR[2] + 0,
			DEST_ADDR[3], DEST_ADDR[4], DEST_ADDR[5]);
	else if (2 == use_mac)
		sprintf(databuf, "V+?:I=%04x", 2);
	else
	sprintf(databuf, "S+L:L=%02x%02x%02x%02x%02x%02x%02x%02x, D=%d",
		     stream_id[0], stream_id[1],
		     stream_id[2], stream_id[3],
		     stream_id[4], stream_id[5],
		     stream_id[6], stream_id[7], substate);
	rc = send_msg(databuf, 1500);
	if (3 <= extra_addr) {
		int test = extra_addr - 2;
		unsigned char num = test_cnt;

		stream_id[6] = 0x80 | test;
		switch (test) {
		case 1:
			if (!num)
				num = 11;
			break;
		case 2:
			if (!num)
				num = 200;
			break;
		case 3:
			if (!num)
				num = 200;
			break;
		default:
			if (!num)
				num = 8;
			else if (num > 0xf)
				num = 0xf;
			num = (test_first << 4) | num;
			break;
		}
		stream_id[7] = num;
		sprintf(databuf, "S+L:L=%02x%02x%02x%02x%02x%02x%02x%02x, D=%d",
			stream_id[0], stream_id[1],
			stream_id[2], stream_id[3],
			stream_id[4], stream_id[5],
			stream_id[6], stream_id[7], substate);
		rc = send_msg(databuf, 1500);
	}
	stream_id[6] = id[0];
	stream_id[7] = id[1];

#ifdef DEBUG
	fprintf(stdout,"Ready-Msg: %s\n", databuf);
#endif 

	free(databuf);
	return rc;
}

int send_leave()
{
	char *databuf;
	int rc;
	databuf = malloc(1500);
	if (NULL == databuf)
		return -1;
	memset(databuf, 0, 1500);
	if (1 == use_mac)
		sprintf(databuf, "M--:M=%02x%02x%02x%02x%02x%02x",
			DEST_ADDR[0], DEST_ADDR[1], DEST_ADDR[2] + 0,
			DEST_ADDR[3], DEST_ADDR[4], DEST_ADDR[5]);
	else if (2 == use_mac)
		sprintf(databuf, "V--:I=%04x", 2);
	else
	sprintf(databuf, "S-L:L=%02x%02x%02x%02x%02x%02x%02x%02x, D=3",
		     stream_id[0], stream_id[1],
		     stream_id[2], stream_id[3],
		     stream_id[4], stream_id[5],
		     stream_id[6], stream_id[7]);
	rc = send_msg(databuf, 1500);
	if (3 <= extra_addr) {
		unsigned char id[2];
		int test = extra_addr - 2;
		unsigned char num = test_cnt;

		id[0] = stream_id[6];
		id[1] = stream_id[7];
		stream_id[6] = 0x80 | test;
		switch (test) {
		case 1:
			if (!num)
				num = 11;
			break;
		case 2:
			if (!num)
				num = 200;
			break;
		case 3:
			if (!num)
				num = 200;
			break;
		default:
			if (!num)
				num = 8;
			else if (num > 0xf)
				num = 0xf;
			num = (test_first << 4) | num;
			break;
		}
		stream_id[7] = num;
		sprintf(databuf, "S-L:L=%02x%02x%02x%02x%02x%02x%02x%02x, D=3",
			     stream_id[0], stream_id[1],
			     stream_id[2], stream_id[3],
			     stream_id[4], stream_id[5],
			     stream_id[6], stream_id[7]);
		rc = send_msg(databuf, 1500);
		stream_id[6] = id[0];
		stream_id[7] = id[1];
	}
	if (!use_mac) {
		sprintf(databuf, "S-D:C=6,P=3,V=0002");
		rc = send_msg(databuf, 1500);
	}
	free(databuf);
	return rc;
}

static int halt_rx;
static int mrp_okay;
static int mrp_error;

void sigint_handler(int signum)
{
	fprintf(stdout,"Leaving...\n");
	
	if (0 != talker || use_mac)
		send_leave();

	if (2 < control_socket)
	{
		mrp_disconnect();
		close(control_socket);
	}

#ifdef PCAP
	if (NULL != handle) 
	{
		pcap_breakloop(handle);
		pcap_close(handle);
	}
#endif
	
#ifdef LIBSND
	sf_write_sync(snd_file);
	sf_close(snd_file);
#endif
	halt_rx = 1;
	exit(0);
}

int process_mrp_msg(char *buf, int buflen)
{

	/*
	 * 1st character indicates application
	 * [MVS] - MAC, VLAN or STREAM
	 */
	unsigned int id;
	unsigned int priority;
	unsigned int vid;
	int i, j, k;
	unsigned int substate;
	unsigned char recovered_streamid[8];
	k = 0;
printf(" %s\n", buf);
 next_line:if (k >= buflen)
		return (0);
	switch (buf[k]) {
	case 'E':
		printf("%s from mrpd\n", buf);
		fflush(stdout);
		mrp_error = 1;
		break;
	case 'O':
		mrp_okay = 1;
		break;
#if 0
	case 'M':
		if (1 == use_mac) {
			if (('N' == buf[k + 1] && 'E' == buf[k + 2]) ||
			    ('J' == buf[k + 1] && 'O' == buf[k + 2]))
				listeners = 1;
			else if ('L' == buf[k + 1] && 'E' == buf[k + 2])
				listeners = 0;
			break;
		}
	case 'V':
		if (2 == use_mac) {
			if (('N' == buf[k + 1] && 'E' == buf[k + 2]) ||
			    ('J' == buf[k + 1] && 'O' == buf[k + 2]))
				listeners = 1;
			else if ('L' == buf[k + 1] && 'E' == buf[k + 2])
				listeners = 0;
			break;
		}
		printf("%s unhandled from mrpd\n", buf);
		fflush(stdout);

		/* unhandled for now */
		break;
	case 'L':

		/* parse a listener attribute - see if it matches our monitor_stream_id */
		i = k;
		while (buf[i] != 'D')
			i++;
		i += 2;		/* skip the ':' */
		sscanf(&(buf[i]), "%d", &substate);
		while (buf[i] != 'S')
			i++;
		i += 2;		/* skip the ':' */
		for (j = 0; j < 8; j++) {
			sscanf(&(buf[i + 2 * j]), "%02x", &id);
			recovered_streamid[j] = (unsigned char)id;
		} printf
		    ("FOUND STREAM ID=%02x%02x%02x%02x%02x%02x%02x%02x ",
		     recovered_streamid[0], recovered_streamid[1],
		     recovered_streamid[2], recovered_streamid[3],
		     recovered_streamid[4], recovered_streamid[5],
		     recovered_streamid[6], recovered_streamid[7]);
		switch (substate) {
		case 0:
			printf("with state ignore\n");
			break;
		case 1:
			printf("with state askfailed\n");
			break;
		case 2:
			printf("with state ready\n");
			break;
		case 3:
			printf("with state readyfail\n");
			break;
		default:
			printf("with state UNKNOWN (%d)\n", substate);
			break;
		}
		if (substate > MSRP_LISTENER_ASKFAILED) {
			if (memcmp
			    (recovered_streamid, monitor_stream_id,
			     sizeof(recovered_streamid)) == 0) {
				listeners = 1;
				printf("added listener\n");
			}
		}
		fflush(stdout);

		/* try to find a newline ... */
		while ((i < buflen) && (buf[i] != '\n') && (buf[i] != '\0'))
			i++;
		if (i == buflen)
			return (0);
		if (buf[i] == '\0')
			return (0);
		i++;
		k = i;
		goto next_line;
		break;
	case 'D':
		i = k + 4;

		/* save the domain attribute */
		sscanf(&(buf[i]), "%d", &id);
		while (buf[i] != 'P')
			i++;
		i += 2;		/* skip the ':' */
		sscanf(&(buf[i]), "%d", &priority);
		while (buf[i] != 'V')
			i++;
		i += 2;		/* skip the ':' */
		sscanf(&(buf[i]), "%x", &vid);
		if (id == 6) {
			domain_class_a_id = id;
			domain_class_a_priority = priority;
			domain_class_a_vid = vid;
			domain_a_valid = 1;
		} else {
			domain_class_b_id = id;
			domain_class_b_priority = priority;
			domain_class_b_vid = vid;
			domain_b_valid = 1;
		}
		while ((i < buflen) && (buf[i] != '\n') && (buf[i] != '\0'))
			i++;
		if ((i == buflen) || (buf[i] == '\0'))
			return (0);
		i++;
		k = i;
		goto next_line;
		break;
	case 'T':

		/* as simple_talker we don't care about other talkers */
		i = k;
		while ((i < buflen) && (buf[i] != '\n') && (buf[i] != '\0'))
			i++;
		if (i == buflen)
			return (0);
		if (buf[i] == '\0')
			return (0);
		i++;
		k = i;
		goto next_line;
		break;
#endif
	case 'S':

		/* handle the leave/join events */
		switch (buf[k + 4]) {
		case 'T':
			switch (buf[k + 1]) {
			case 'L':
				printf("got a leave indication\n");
				sigint_handler(1);
			}
			break;
#if 0
		case 'L':
			i = k + 5;
			while (buf[i] != 'D')
				i++;
			i += 2;	/* skip the ':' */
			sscanf(&(buf[i]), "%d", &substate);
			while (buf[i] != 'S')
				i++;
			i += 2;	/* skip the ':' */
			for (j = 0; j < 8; j++) {
				sscanf(&(buf[i + 2 * j]), "%02x", &id);
				recovered_streamid[j] = (unsigned char)id;
			} printf
			    ("EVENT on STREAM ID=%02x%02x%02x%02x%02x%02x%02x%02x ",
			     recovered_streamid[0], recovered_streamid[1],
			     recovered_streamid[2], recovered_streamid[3],
			     recovered_streamid[4], recovered_streamid[5],
			     recovered_streamid[6], recovered_streamid[7]);
			switch (substate) {
			case 0:
				printf("with state ignore\n");
				break;
			case 1:
				printf("with state askfailed\n");
				break;
			case 2:
				printf("with state ready\n");
				break;
			case 3:
				printf("with state readyfail\n");
				break;
			default:
				printf("with state UNKNOWN (%d)\n", substate);
				break;
			}
			switch (buf[k + 1]) {
			case 'L':
				printf("got a leave indication\n");
				if (memcmp
				    (recovered_streamid, monitor_stream_id,
				     sizeof(recovered_streamid)) == 0) {
					listeners = 0;
					printf("listener left\n");
				}
				break;
			case 'J':
			case 'N':
				printf("got a new/join indication\n");
				if (substate > MSRP_LISTENER_ASKFAILED) {
					if (memcmp
					    (recovered_streamid,
					     monitor_stream_id,
					     sizeof(recovered_streamid)) == 0)
						listeners = 1;
				}
				break;
			}
#endif

			/* only care about listeners ... */
		default:
			return (0);
			break;
		}
		break;
	case '\0':
		break;
	}
	return (0);
}

void *mrp_monitor_thread(void *arg)
{
	char *msgbuf;
	struct sockaddr_in client_addr;
	struct msghdr msg;
	struct iovec iov;
	int bytes = 0;
	struct pollfd fds;
	int rc;
	if (NULL == arg)
		rc = 0;

	else
		rc = 1;
	msgbuf = (char *)malloc(MAX_MRPD_CMDSZ);
	if (NULL == msgbuf)
		return NULL;
	while (!halt_rx) {
		fds.fd = control_socket;
		fds.events = POLLIN;
		fds.revents = 0;
		rc = poll(&fds, 1, 100);
		if (rc < 0) {
			free(msgbuf);
			pthread_exit(NULL);
		}
		if (rc == 0)
			continue;
		if ((fds.revents & POLLIN) == 0) {
			free(msgbuf);
			pthread_exit(NULL);
		}
		memset(&msg, 0, sizeof(msg));
		memset(&client_addr, 0, sizeof(client_addr));
		memset(msgbuf, 0, MAX_MRPD_CMDSZ);
		iov.iov_len = MAX_MRPD_CMDSZ;
		iov.iov_base = msgbuf;
		msg.msg_name = &client_addr;
		msg.msg_namelen = sizeof(client_addr);
		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;
		bytes = recvmsg(control_socket, &msg, 0);
		if (bytes < 0)
			continue;
		process_mrp_msg(msgbuf, bytes);
	}
	free(msgbuf);
	pthread_exit(NULL);
}

pthread_t monitor_thread;
pthread_attr_t monitor_attr;
int mrp_monitor()
{
	pthread_attr_init(&monitor_attr);
	pthread_create(&monitor_thread, NULL, mrp_monitor_thread, NULL);
	return (0);
}

int main(int argc, char *argv[])
{
	int ret;
	char* file_name = NULL;
	char* dev = NULL;
#if 0
	char errbuf[PCAP_ERRBUF_SIZE];
	struct bpf_program comp_filter_exp;		/* The compiled filter expression */
	char filter_exp[] = "ether dst 91:E0:F0:00:0e:80";	/* The filter expression */
	struct pcap_pkthdr header;	/* header pcap gives us */
#endif
	const u_char* packet;		/* actual packet */
	int avb_socket;
	fd_set fds;
	fd_set sel_fds;
	struct timeval timer;
	int skip_mrp = 0;
	int num;

	signal(SIGINT, sigint_handler);

	int c;
	file_name = "test.wav";
	while((c = getopt(argc, argv, "hi:f:ml:n:t:vxyz")) > 0) 
	{
		switch (c) 
		{
		case 'm':
			use_mac = 1;
			break;
		case 'v':
			use_mac = 2;
			break;
		case 'x':
			extra_addr = 1;
			break;
		case 'y':
			extra_addr = 2;
			break;
		case 'l':
			num = atoi(optarg);
			test_first = num;
			break;
		case 'n':
			num = atoi(optarg);
			test_cnt = num;
			break;
		case 't':
			num = atoi(optarg);
			extra_addr = 2 + num;
			break;
		case 'z':
			skip_mrp = 1;
			break;
		case 'h': 
			help();
			break;
		case 'i':
			dev = strdup(optarg);
			break;
		case 'f':
			file_name = strdup(optarg);
			break;
		default:
          		fprintf(stderr, "Unrecognized option!\n");
		}
	}

	if ((NULL == dev) || (NULL == file_name))
		help();

	if (!skip_mrp)
	if (create_socket())
	{
		fprintf(stderr, "Socket creation failed.\n");
		return (errno);
	}
	memcpy(dest_addr, DEST_ADDR, 6);
	if (1 == extra_addr)
		dest_addr[5] += 1;
	if (skip_mrp) {
		ret = get_1722_socket(dev, &avb_socket);
		goto recv_1722;
	}

	report_domain_status();

	fprintf(stdout,"Waiting for talker...\n");
	await_talker();	
	if (!skip_mrp)
		mrp_monitor();

	ret = get_1722_socket(dev, &avb_socket);

#ifdef DEBUG
	fprintf(stdout,"Send ready-msg...\n");
#endif
	send_ready();
		
#ifdef LIBSND
	SF_INFO* sf_info = (SF_INFO*)malloc(sizeof(SF_INFO));

	memset(sf_info, 0, sizeof(SF_INFO));
	
	sf_info->samplerate = SAMPLES_PER_SECOND;
	sf_info->channels = CHANNELS;
	sf_info->format = SF_FORMAT_WAV | SF_FORMAT_PCM_24;

	if (0 == sf_format_check(sf_info))
	{
		fprintf(stderr, "Wrong format.");
		return -1;
	}
			
	if (NULL == (snd_file = sf_open(file_name, SFM_WRITE, sf_info)))
	{
		fprintf(stderr, "Could not create file.");
		return -1;
	}
	fprintf(stdout,"Created file called %s\n", file_name);	
#endif

#ifdef PCAP		
	/** session, get session handler */
	/* take promiscuous vs. non-promiscuous sniffing? (0 or 1) */
	handle = pcap_open_live(dev, BUFSIZ, 1, -1, errbuf);
	if (NULL == handle) 
	{
		fprintf(stderr, "Could not open device %s: %s\n", dev, errbuf);
		return -1;
	}

#ifdef DEBUG
	fprintf(stdout,"Got session handler.\n");
#endif
	/* compile and apply filter */
	if (-1 == pcap_compile(handle, &comp_filter_exp, filter_exp, 0, PCAP_NETMASK_UNKNOWN))
	{
		fprintf(stderr, "Could not parse filter %s: %s\n", filter_exp, pcap_geterr(handle));
		return -1;
	}

	if (-1 == pcap_setfilter(handle, &comp_filter_exp)) 
	{
		fprintf(stderr, "Could not install filter %s: %s\n", filter_exp, pcap_geterr(handle));
		return -1;
	}

#ifdef DEBUG
	fprintf(stdout,"Compiled and applied filter.\n");
#endif

	/** loop forever and call callback-function for every received packet */
	pcap_loop(handle, -1, pcap_callback, NULL);
#endif

recv_1722:
	FD_ZERO(&fds);
	FD_SET(avb_socket, &fds);
#if 1
	do {
		timerclear(&timer);
		timer.tv_sec = 1;
		sel_fds = fds;
		ret = select(avb_socket + 1, &sel_fds, NULL, NULL, &timer);
		if (ret > 0 && FD_ISSET(avb_socket, &sel_fds))
			process_1722(avb_socket);
	} while (!halt_rx);
	if (avb_socket != -1)
		close(avb_socket);
#endif

	return 0;
}
