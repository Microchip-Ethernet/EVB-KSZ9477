/*
 *  linux/arch/arm/mach-ksz8695/ks895_io.c
 *
 *  Copyright (C) 2002-2009 Micrel Inc.
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#ifndef	__KS8695_IO_H
#define	__KS8695_IO_H

#include <asm/irq.h>
#include <asm/io.h>

#define KS8695_VA_IO_BASE  IO_ADDRESS(KS8695_IO_BASE) 

#define	KS8695_WRITE(offset, v)	__raw_writel((v), KS8695_VA_IO_BASE + (offset))
#define	KS8695_READ(offset)	__raw_readl(KS8695_VA_IO_BASE + (offset))

#endif	/* __KS8695_IO_H */
