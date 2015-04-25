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

#include "squfof.h"

uint64_t squfof_back (uint64_t p0, uint64_t q0, uint64_t p1, uint64_t q1, uint64_t sqrtn) {
  uint64_t quot;

  do {

    quot = (sqrtn + p1)/q1;
    p0 = quot*q1 - p1;
    if (p0 == p1) {
      return ((q1 & UINT64_C(1)) == UINT64_C(0)) ? (q1 >> 1) : (q1);
    }
    q0 += quot*(p1 - p0);
    
    quot = (sqrtn + p0)/q0;
    p1 = quot*q0 - p0;
    if (p0 == p1) {
      return ((q0 & UINT64_C(1)) == UINT64_C(0)) ? (q0 >> 1) : (q0);
    }
    q1 += quot*(p0 - p1);

  } while (1);

}
