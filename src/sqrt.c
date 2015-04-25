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

#include <stdint.h>

static inline uint64_t sqrt_newton (uint64_t x, uint64_t y) {
  uint64_t r;

  do {
    r = y;
    y = (y + x/y)>>1;
  } while (y < r);

  return r;
}

uint64_t xsqrt_u64 (uint64_t x) {
  uint64_t u;
  uint64_t v;
  uint64_t y;

  if (x == 0) {
    return 0;
  }

  u = x;
  y = 1;

  if ((v = (u >> 32)) != 0) {
    u = v;
    y <<= 16;
  }
  if ((v = (u >> 16)) != 0) {
    u = v;
    y <<= 8;
  }
  if ((v = (u >> 8)) != 0) {
    u = v;
    y <<= 4;
  }
  if ((v = (u >> 4)) != 0) {
    u = v;
    y <<= 2;
  }
  if ((v = (u >> 2)) != 0) {
    u = v;
    y <<= 1;
  }

  if (u <= 1) {
    y += y >> 1;
  } else {
    y <<= 1;
  }

  return sqrt_newton (x, y);
}
