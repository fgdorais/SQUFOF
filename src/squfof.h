/* 
 * This file is part of the SQUFOF program.
 * Copyright (C) 2009, 2010 F. G. Dorais.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * file COPYING for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. 
 */

#include <config.h>
#include "../lib/arith.h"

#if (HAVE_STDINT_H) && (HAVE_INTTYPES_H)
#include <stdint.h>
#include <inttypes.h>
#endif

#ifndef __SQUFOF__
#define __SQUFOF__

extern uint64_t squfof_u64 (uint64_t);

extern int squfof_forth (uint64_t *, uint64_t *, uint64_t);

extern uint64_t squfof_back (uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);

#define Q_LENGTH (64)

#endif /* SQUFOF */
