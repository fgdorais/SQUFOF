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

uint64_t squfof_u64 (uint64_t n) 
{
  uint64_t p0, q0;
  uint64_t p1, q1;
  uint64_t s;
  uint64_t d;
  int val;

  if (n == UINT64_C(0)) 
    {
      return UINT64_C(0);
    }

  bxval_u64(val, n, n);  
  n = ((n & UINT64_C(3)) == UINT64_C(1)) ? (n <<= 1) : (n);
	
  sqrt_u64(s, n);

  p0 = s;
  q0 = n - s*s;

  if (q0 == 0) 
    {
      return s;
    }

  if (squfof_forth (&p0, &q0, s) != 0) 
    {
      return UINT64_C(1);
    }

  p1 = p0 + q0*((s - p0)/q0);
  q1 = (n - p1*p1)/q0;

  d = squfof_back (p0, q0, p1, q1, s);

  bxval_u64(val, d, d); /* Is this necessary? */
	
  return d;
}
