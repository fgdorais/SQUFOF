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

#include "arith.h"

inline uint16_t __sqrt_u16(uint16_t x) 
{
  uint8_t xl = (uint8_t)(x & 255);
  int xi = (int)(x >> 8) - 64;

  return (xl > __sqrt_u16_bnd[xi]) 
    ? ((uint16_t)(__sqrt_u16_app[xi]) + 1) 
    : (uint16_t)(__sqrt_u16_app[xi]);
}    

inline uint32_t __sqrt_u32 (uint32_t x) {
  uint32_t root;
  uint32_t rem;
  uint32_t quot;
  uint32_t temp;

  root = (uint32_t)(__sqrt_u16((uint16_t)(x >> 16)));

  temp = (x >> 8) - ((root*root) << 8);

  quot = temp / (2*root);
  temp = temp % (2*root);

  root = (root << 8) + quot;
  temp = ((temp << 8) | (x & 255));

  return (temp < quot*quot) ? (root - 1) : (root);
}

inline uint64_t __sqrt_u64 (uint64_t x) {
  uint64_t root;
  uint64_t rem;
  uint64_t quot;
  uint64_t temp;

  root = (uint64_t)(__sqrt_u32((uint32_t)(x >> 32)));

  temp = (x >> 16) - ((root*root) << 16);

  quot = temp / (2*root);
  temp = temp % (2*root);

  root = (root << 16) + quot;
  temp = ((temp << 16) | (x & 65535));

  return (temp < quot*quot) ? (root - 1) : (root);
}


