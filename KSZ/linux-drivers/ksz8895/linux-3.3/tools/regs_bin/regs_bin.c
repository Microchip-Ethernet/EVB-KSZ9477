#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>


#define REGS_COUNT	(0x100)

int fd;
int reg_cnt;
int fixed_boundary = 0;
size_t acc_size;
size_t reg_size;
char *reg_fmt;


int get_regs(unsigned int first, size_t count, unsigned int *buf)
{
	int n;

	n = lseek(fd, first, SEEK_SET);
	if (n < 0)
		return n;
	if (count > REGS_COUNT * acc_size)
		count = REGS_COUNT * acc_size;
	n = read(fd, buf, count);
	return n;
}

int put_regs(unsigned int first, size_t size, size_t count, unsigned int *buf)
{
	int n;
	unsigned short *buf_16 = (unsigned short *) buf;
	unsigned char *buf_8 = (unsigned char *) buf;

	if (2 == size) {
		for (n = 0; n < count; n++)
			buf_16[n] = (unsigned short) buf[n];
		if (1 == acc_size)
			for (n = 0; n < count; n++)
				buf_16[n] = htons(buf_16[n]);
	} else if (1 == size) {
		for (n = 0; n < count; n++)
			buf_8[n] = (unsigned char) buf[n];
	} else {
		if (1 == acc_size)
			for (n = 0; n < count; n++)
				buf[n] = htonl(buf[n]);
		else if (2 == acc_size)
			for (n = 0; n < count; n++)
				buf[n] = (buf[n] << 16) | (buf[n] >> 16);
	}
	n = lseek(fd, first, SEEK_SET);
	if (n < 0)
		return n;
	n = write(fd, buf, count * size);
	return n;
}

void display_regs(unsigned int first, size_t size, size_t count, void *buf)
{
	size_t i;
	unsigned int *buf_32 = buf;
	unsigned short *buf_16 = buf;
	unsigned char *buf_8 = buf;

	if (size == acc_size && fixed_boundary) {
		if (first & 1)
			size = 1;
		else if (first & 2)
			size = 2;
	}
	if (size < acc_size) {
		char fmt[8];

		printf("%04x: ", first);
		if (2 == size)
			strcpy(fmt, "%04x\n");
		else if (1 == size)
			strcpy(fmt, "%02x\n");
		if (4 == acc_size)
			printf(fmt, *buf_32);
		else if (2 == acc_size)
			printf(fmt, *buf_16);
		else
			printf(fmt, *buf_8);
		return;
	}
	if (reg_size < acc_size && acc_size > 1) {
		for (i = 0; i < count / acc_size; i++) {
			if (4 == acc_size) {
				if (2 == reg_size)
					*buf_32 = (*buf_32 << 16) |
						(*buf_32 >> 16);
				else
					*buf_32 = ntohl(*buf_32);
				++buf_32;
			} else if (2 == acc_size) {
				*buf_16 = ntohs(*buf_16);
				++buf_16;
			}
		}
		buf_32 = buf;
		buf_16 = buf;
	}
	count /= reg_size;
	for (i = 0; i < count; i++) {
		if (!(i % reg_cnt))
			printf("%04x: ", first + i * reg_size);
		if (4 == reg_size) {
			printf(reg_fmt, *buf_32);
			++buf_32;
		} else if (2 == reg_size) {
			printf(reg_fmt, *buf_16);
			++buf_16;
		} else {
			printf(reg_fmt, *buf_8);
			++buf_8;
		}
		if ((reg_cnt - 1) == (i % reg_cnt))
			printf("\n");
	}
	if ((i % reg_cnt))
		printf("\n");
}

void determine_reg_size(void)
{
	int n;
	unsigned int data[1];

	acc_size = 1;
	n = get_regs(0, 1, data);
	if (n < 0) {
		printf("read error\n");
		exit(1);
	}
	switch (n) {
	case 4:
		acc_size = 4;
		if (!reg_size) {
			reg_size = 4;
			reg_cnt = 8;
			reg_fmt = "%08x ";
		}
		n = get_regs(1, n, data);
		if (n <= 0)
			fixed_boundary = 1;
		break;
	case 1:
		acc_size = 1;
		if (!reg_size) {
			reg_size = 1;
			reg_cnt = 16;
			reg_fmt = "%02x ";
		}
		break;
	case 2:
	default:
		acc_size = 2;
		if (!reg_size) {
			reg_size = 2;
			reg_cnt = 8;
			reg_fmt = "%04x ";
		}
		n = get_regs(1, n, data);
		if (n <= 0)
			fixed_boundary = 1;
		break;
	}
}

void get_cmd(FILE *fp)
{
	int count;
	unsigned int num[14];
	int rc;
	unsigned int data[REGS_COUNT];
	char cmd[80];
	char line[80];
	int cont = 1;

	do {
		printf("> ");
		if (fgets(line, 80, fp) == NULL)
			break;
		cmd[0] = '\0';
		count = sscanf(line,
			"%s %x %x %x %x %x %x %x %x %x %x %x %x %x", cmd,
			(unsigned int *) &num[0],
			(unsigned int *) &num[1],
			(unsigned int *) &num[2],
			(unsigned int *) &num[3],
			(unsigned int *) &num[4],
			(unsigned int *) &num[5],
			(unsigned int *) &num[6],
			(unsigned int *) &num[7],
			(unsigned int *) &num[8],
			(unsigned int *) &num[9],
			(unsigned int *) &num[10],
			(unsigned int *) &num[11],
			(unsigned int *) &num[12]);
		switch (cmd[0]) {
		case 'r':
			if (count >= 2) {
				size_t size = acc_size;

				if (count >= 3)
					count = num[1];
				else
					count = 1;
				if (1 == count) {
					if ('b' == cmd[1])
						size = 1;
					else if ('w' == cmd[1])
						size = 2;
					else if ('d' == cmd[1])
						size = 4;
					if (fixed_boundary) {
						if (num[0] & 1)
							size = 1;
						else if (num[0] & 2)
							size = 2;
					}
				}
				count *= size;
				do {
					rc = get_regs(num[0], count, data);
					if (rc > 0) {
						display_regs(num[0], count, rc,
							data);
						count -= rc;
						num[0] += rc;
					} else
						break;
				} while (count > 0);
			}
			break;
		case 'w':
			if (count >= 3) {
				int i;
				size_t size = acc_size;

				count -= 2;
				for (i = 0; i < count; i++)
					data[i] = num[1 + i];
				if (1 == count) {
					if ('b' == cmd[1])
						size = 1;
					else if ('w' == cmd[1])
						size = 2;
					else if ('d' == cmd[1])
						size = 4;
					if (fixed_boundary) {
						if (num[0] & 1)
							size = 1;
						else if (num[0] & 2)
							size = 2;
					}
				}
				put_regs(num[0], size, count, data);
			}
			break;
		case 'q':
			cont = 0;
			break;
		}
	} while (cont);
}

int main(int argc, char *argv[])
{
	char device[80];

	acc_size = 0;
	reg_size = 0;
	device[0] = '\0';
	if (argc > 1) {
		int i = 1;

		if ('/' == argv[i][0])
			strncpy(device, argv[i], sizeof(device));
		else {
			if (!strncmp(argv[i], "eth", 3))
				snprintf(device, sizeof(device),
					"/sys/class/net/%s", argv[i]);
			else if (!strncmp(argv[i], "spi", 3))
				snprintf(device, sizeof(device),
					"/sys/bus/spi/devices/%s", argv[i]);
			else
				snprintf(device, sizeof(device),
					"/sys/bus/i2c/devices/%s", argv[i]);
		}
		strcat(device, "/registers");
		++i;
		if (i < argc) {
			if ('4' == argv[i][0]) {
				reg_size = 4;
				reg_cnt = 8;
				reg_fmt = "%08x ";
			} else if ('2' == argv[i][0]) {
				reg_size = 2;
				reg_cnt = 8;
				reg_fmt = "%04x ";
			} else if ('1' == argv[i][0]) {
				reg_size = 1;
				reg_cnt = 16;
				reg_fmt = "%02x ";
			}
		}
	} else {
		printf("%s <dev>\n", argv[0]);
		return 0;
	}
	fd = open(device, O_RDWR);
	if (fd < 0)
		return -1;
	if (!acc_size)
		determine_reg_size();
	get_cmd(stdin);
	close(fd);
	return 0;
}
