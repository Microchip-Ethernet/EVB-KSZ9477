/**
 * @file sk.h
 * @brief Implements protocol independent socket methods.
 * @note Copyright (C) 2012 Richard Cochran <richardcochran@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef HAVE_SK_H
#define HAVE_SK_H

#include <stdbool.h>
#include "address.h"
#include "transport.h"

/**
 * Defines the available Hardware time-stamp setting modes.
 */

enum hwts_filter_mode {
	HWTS_FILTER_NORMAL,    /* set hardware filters in normal way */
	HWTS_FILTER_CHECK,     /* check filters but do not change them */
	HWTS_FILTER_FULL,      /* Use time-stamp on all received packets */
};

/**
 * Contains timestamping information returned by the GET_TS_INFO ioctl.
 * @valid:            set to non-zero when the info struct contains valid data.
 * @phc_index:        index of the PHC device.
 * @so_timestamping:  supported time stamping modes.
 * @tx_types:         driver level transmit options for the HWTSTAMP ioctl.
 * @rx_filters:       driver level receive options for the HWTSTAMP ioctl.
 */
struct sk_ts_info {
	int valid;
	int phc_index;
	unsigned int so_timestamping;
	unsigned int tx_types;
	unsigned int rx_filters;
};

/**
 * Contains interface information returned by the GLINKSETTINGS ioctl.
 * @valid:            set to non-zero when the info struct contains valid data.
 * @speed:            interface speed.
 * @iface_bit_period  interface bit period in attoseconds per bit.
 */
struct sk_if_info {
	bool valid;
	uint32_t speed;
	uint64_t iface_bit_period;
};

/**
 * Obtains a socket suitable for use with sk_interface_index().
 * @return  An open socket on success, -1 otherwise.
 */
int sk_interface_fd(void);

/**
 * Obtain the numerical index from a network interface by name.
 * @param fd      An open socket.
 * @param device  The name of the network interface of interest.
 * @return        The result from the SIOCGIFINDEX ioctl.
 */
int sk_interface_index(int fd, const char *device);

/**
 * Prepare a given socket for PTP "general" messages.
 * @param fd  An open socket.
 * @return    Zero on success, non-zero otherwise.
 */
int sk_general_init(int fd);

/**
 * Obtain supported timestamping information
 * @param name	    The name of the interface
 * @param info      Struct containing obtained timestamping information.
 * @return          zero on success, negative on failure.
 */
int sk_get_ts_info(const char *name, struct sk_ts_info *sk_info);

/**
 * Obtain supporte interface information
 * @param name     The name of the interface
 * @param info      Struct containing obtained interface information.
 * @return          zero on success, negative on failure.
 */
int sk_get_if_info(const char *name, struct sk_if_info *sk_info);

/**
 * Obtain the MAC address of a network interface.
 * @param name  The name of the interface
 * @param mac   Buffer to hold the result
 * @return      Zero on success, non-zero otherwise.
 */
int sk_interface_macaddr(const char *name, struct address *mac);

/**
 * Obtains the first IP address assigned to a network interface.
 * @param name   The name of the interface
 * @param family The family of the address to get: AF_INET or AF_INET6
 * @param addr   Buffer to hold the result
 * @return       The number of bytes written to addr on success, -1 otherwise.
 */
int sk_interface_addr(const char *name, int family, struct address *addr);

/**
 * Read a message from a socket.
 * @param fd      An open socket.
 * @param buf     Buffer to receive the message.
 * @param buflen  Size of 'buf' in bytes.
 * @param addr    Pointer to a buffer to receive the message's source
 *                address. May be NULL.
 * @param hwts    Pointer to a buffer to receive the message's time stamp.
 * @param flags   Flags to pass to RECV(2).
 * @return
 */
int sk_receive(int fd, void *buf, int buflen,
	       struct address *addr, struct hw_timestamp *hwts, int flags);

/**
 * Get and clear a pending socket error.
 * @param fd      An open socket.
 * @return        The error.
 */
int sk_get_error(int fd);

/**
 * Set DSCP value for socket.
 * @param fd     An open socket.
 * @param family The address family in use: AF_INET or AF_INET6
 * @param dscp   The desired DSCP code.
 * @return Zero on success, negative on failure
 */
int sk_set_priority(int fd, int family, uint8_t dscp);

#ifdef KSZ_1588_PTP
int sk_timestamping_close(int fd, const char *device);
int sk_timestamping_filt(int fd, const char *device, int rx_sync);
#endif

/**
 * Enable time stamping on a given network interface.
 * @param fd          An open socket.
 * @param device      The name of the network interface to configure.
 * @param type        The requested flavor of time stamping.
 * @param transport   The type of transport used.
 * @param vclock      Index of the virtual PHC, or -1 for the physical clock.
 * @return            Zero on success, non-zero otherwise.
 */
int sk_timestamping_init(int fd, const char *device, enum timestamp_type type,
			 enum transport_type transport, int vclock);

/**
 * Limits the time that RECVMSG(2) will poll while waiting for the tx timestamp
 * if MSG_ERRQUEUE is set. Specified in milliseconds.
 */
extern int sk_tx_timeout;

/**
 * Enables the SO_TIMESTAMPNS socket option on the both the event and
 * general sockets in order to test the order of paired sync and
 * follow up messages using their network stack receipt time stamps.
 */
extern int sk_check_fupsync;

/**
 * Hardware time-stamp setting mode
 */
extern enum hwts_filter_mode sk_hwts_filter_mode;

#endif
