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
#error "arith-sqrt.h: Do note include this this file directly, include arith.h instead."
#endif

#ifndef __ARITH_SQRT_H__
#define __ARITH_SQRT_H__

extern const uint8_t __sqrt_u8[256];
extern const uint8_t __sqrt_u16_app[192];
extern const uint8_t __sqrt_u16_bnd[192];

extern uint16_t __sqrt_u16 (uint16_t);
extern uint32_t __sqrt_u32 (uint32_t);
extern uint64_t __sqrt_u64 (uint64_t);

#define sqrt_u32(res,op) \
  do {                                                                  \
    uint32_t __sqrt_adj;                                                \
    uint32_t __sqrt_app;                                                \
    int __sqrt_exp;                                                     \
    bxlog_u32(__sqrt_exp,__sqrt_adj,(op));                              \
    __sqrt_adj = (__sqrt_exp & 1) ? (__sqrt_adj) : (__sqrt_adj >> 1);   \
    __sqrt_exp = (31 - __sqrt_exp) >> 1;                                \
    (res) = __sqrt_u32(__sqrt_adj) >> __sqrt_exp;                       \
  } while (0)

#define sqrt_u64(res,op) \
  do {                                                                  \
    uint64_t __sqrt_adj;                                                \
    uint64_t __sqrt_app;                                                \
    int __sqrt_exp;                                                     \
    bxlog_u64(__sqrt_exp,__sqrt_adj,(op));                              \
    __sqrt_adj = (__sqrt_exp & 1) ? (__sqrt_adj) : (__sqrt_adj >> 1);   \
    __sqrt_exp = (63 - __sqrt_exp) >> 1;                                \
    (res) = __sqrt_u64(__sqrt_adj) >> __sqrt_exp;                       \
  } while (0)

#endif /* ARITH_SQRT_H */
