/**
 * @file dm.h
 * @brief Enumerates the delay mechanisms.
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
#ifndef HAVE_DM_H
#define HAVE_DM_H

/**
 * Defines the possible delay mechanisms.
 */
enum delay_mechanism {

	/** Start as E2E, but switch to P2P if a peer is detected. */
	DM_AUTO,

	/** Delay request-response mechanism. */
	DM_E2E,

	/** Peer delay mechanism. */
	DM_P2P,
};

#endif
