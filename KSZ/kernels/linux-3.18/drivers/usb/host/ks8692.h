/*
 *
 * BRIEF MODULE DESCRIPTION
 *	Include file for Micrel's KS8692 CPU.
 *
 * Copyright 2007 Micrel Semiconductor Inc.
 * Author: Micrel Semiconductor, Inc.
 *		david.choi@micrel.com
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 *  THIS  SOFTWARE  IS PROVIDED   ``AS  IS'' AND   ANY  EXPRESS OR IMPLIED
 *  WARRANTIES,   INCLUDING, BUT NOT  LIMITED  TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 *  NO  EVENT  SHALL   THE AUTHOR  BE    LIABLE FOR ANY   DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED   TO, PROCUREMENT OF  SUBSTITUTE GOODS  OR SERVICES; LOSS OF
 *  USE, DATA,  OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN  CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *  You should have received a copy of the  GNU General Public License along
 *  with this program; if not, write  to the Free Software Foundation, Inc.,
 *  675 Mass Ave, Cambridge, MA 02139, USA.
 */

 /*
  * some definitions add by takuzo@sm.sony.co.jp and sato@sm.sony.co.jp
  */

#ifndef _KS8692_USB_H_
#define _KS8692_USB_H_

#ifndef _LANGUAGE_ASSEMBLY

#include <linux/version.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <mach/ks8692_utils.h>

#define KS8692_SOC_OHCI_NAME    "Pegasus-OHCI"
#define KS8692_SOC_EHCI_NAME    "Pegasus-EHCI"
#define KS8692_SOC_USBDEV_NAME  "Pegasus-USBDEV"

static inline u32 au_readl(unsigned long reg)
{
	return KS8692_UTIL_READ_REG(reg);
}

static inline void au_writel(u32 val, unsigned long reg)
{
	KS8692_UTIL_WRITE_REG(val, reg);
}

#endif /* !defined (_LANGUAGE_ASSEMBLY) */

#endif

