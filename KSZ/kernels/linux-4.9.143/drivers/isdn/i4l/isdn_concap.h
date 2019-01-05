/* $Id: //depot/swdev/LAN/Switch/KSZ/kernels/linux-4.9.143/drivers/isdn/i4l/isdn_concap.h#1 $
 *
 * Linux ISDN subsystem, protocol encapsulation
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

extern struct concap_device_ops isdn_concap_reliable_dl_dops;
extern struct concap_proto *isdn_concap_new(int);
