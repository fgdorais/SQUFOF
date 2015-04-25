/* 
 * This file is part of the ARITH project.
 * Copyright (C) 2005, 2006, 2007, 2008, 2009, 2010 F. G. Dorais.
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

#ifndef __ARITH_H__
#define __ARITH_H__

#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

extern const uint8_t __binv_table[128];

#include "arith-arch.h"

#include "arith-32.h"
#include "arith-64.h"

#include "arith-mont-32.h"
#include "arith-mont-64.h"

#include "arith-sqrt.h"

#endif /* ARITH_H */
