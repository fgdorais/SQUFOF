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
#error "arith-arch.h: Do note include this this file directly, include arith.h instead."
#endif

#ifndef __ARITH_ARCH_H__
#define __ARITH_ARCH_H__ x86_32

#define addd_u32(rlo,rhi,alo,ahi,blo,bhi) \
  do {                                                                  \
    asm ("addl\t%3, %0\n\tadcl\t%5, %1"                                 \
         : "=&r" (rlo), "=r" (rhi)                                      \
         : "0" (alo), "g" (blo),                                        \
           "1" (ahi), "g" (bhi));                                       \
  } while (0)

#define subd_u32(rlo,rhi,alo,ahi,blo,bhi) \
  do {                                                                  \
    asm ("subl\t%3, %0\n\tsbbl\t%5, %1"                                 \
         : "=&r" (rlo), "=r" (rhi)                                      \
         : "0" (alo), "g" (blo),                                        \
           "1" (ahi), "g" (bhi));                                       \
  } while (0)

#define muld_u32(rlo,rhi,op1,op2) \
  do {                                                                  \
    asm ("mull\t%3" : "=a" (rlo), "=d" (rhi)                            \
         : "%0" (op1), "rm" (op2));                                     \
  } while (0)

#define divd_u32(quo,rem,nlo,nhi,den) \
  do {                                                                  \
    asm ("divl\t%4" : "=a" (quo), "=d" (rem)                            \
         : "0" (nlo), "1" (nhi), "rm" (den));                           \
  } while (0)

#define bval_u32(val,op) \
  do {                                                                  \
    asm ("bsfl\t%1, %0" : "=r" (val) : "rm" (op));                      \
  } while (0)

#define bxval_u32(val,rop,op) \
  do {                                                                  \
    uint32_t __bxval_val;                                               \
    uint32_t __bxval_op = (op);                                         \
    asm ("bsfl\t%1, %0" : "=r" (__bxval_val) : "rm" (__bxval_op));      \
    (rop) = __bxval_op >> __bxval_val;                                  \
    (val) = __bxval_val;                                                \
  } while (0)

#define blog_u32(log,op) \
  do {                                                                  \
    asm ("bsrl\t%1, %0" : "=r" (log) : "rm" (op));                      \
  } while (0)

#define bxlog_u32(val,rop,op) \
  do {                                                                  \
    asm ("bsrl\t%1, %0\n\trorl\t%1\n\trorl\t%%cl, %1"                   \
         : "=&c" (val), "=r" (rop) : "1" (op));                         \
  } while (0)

#endif /* ARITH_ARCH_H */
