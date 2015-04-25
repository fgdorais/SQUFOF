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
#define __ARITH_ARCH_H__ PPC64

#define addd_u64(rlo,rhi,alo,ahi,blo,bhi) \
  do {                                                                  \
    if (__builtin_constant_p (bhi) && (bhi) == 0)			\
      __asm__ ("{a%I4|add%I4c} %1,%3,%4\n\t{aze|addze} %0,%2"		\
	     : "=r" (rhi), "=&r" (rlo)                                  \
             : "r" (ahi), "%r" (alo), "rI" (blo));                      \
    else if (__builtin_constant_p (bhi) && (bhi) == ~(uint64_t)(0))	\
      __asm__ ("{a%I4|add%I4c} %1,%3,%4\n\t{ame|addme} %0,%2"		\
	     : "=r" (rhi), "=&r" (rlo)                                  \
             : "r" (ahi), "%r" (alo), "rI" (blo));			\
    else								\
      __asm__ ("{a%I5|add%I5c} %1,%4,%5\n\t{ae|adde} %0,%2,%3"		\
	     : "=r" (rhi), "=&r" (rlo)					\
	     : "r" (ahi), "r" (bhi), "%r" (alo), "rI" (blo));		\
  } while (0)

#define subd_u64(rhi, rlo, ahi, alo, bhi, blo) \
  do {									\
    if (__builtin_constant_p (ahi) && (ahi) == 0)			\
      __asm__ ("{sf%I3|subf%I3c} %1,%4,%3\n\t{sfze|subfze} %0,%2"	\
	       : "=r" (rhi), "=&r" (rlo)                                \
               : "r" (bhi), "rI" (alo), "r" (blo));			\
    else if (__builtin_constant_p (ahi) && (ahi) == ~(uint64_t)(0))	\
      __asm__ ("{sf%I3|subf%I3c} %1,%4,%3\n\t{sfme|subfme} %0,%2"	\
	       : "=r" (rhi), "=&r" (rlo)                                \
               : "r" (bhi), "rI" (alo), "r" (blo));			\
    else if (__builtin_constant_p (bhi) && (bhi) == 0)			\
      __asm__ ("{sf%I3|subf%I3c} %1,%4,%3\n\t{ame|addme} %0,%2"		\
	       : "=r" (rhi), "=&r" (rlo)                                \
               : "r" (ahi), "rI" (alo), "r" (blo));		        \
    else if (__builtin_constant_p (bhi) && (bhi) == ~(uint64_t)(0))	\
      __asm__ ("{sf%I3|subf%I3c} %1,%4,%3\n\t{aze|addze} %0,%2"		\
	       : "=r" (rhi), "=&r" (rlo)                                \
               : "r" (ahi), "rI" (alo), "r" (blo));			\
    else								\
      __asm__ ("{sf%I4|subf%I4c} %1,%5,%4\n\t{sfe|subfe} %0,%3,%2"	\
	       : "=r" (rhi), "=&r" (rlo)				\
	       : "r" (ahi), "r" (bhi), "rI" (alo), "r" (blo));		\
  } while (0)

#define mulh_u64(rhi,op1,op2) \
  do {									\
    __asm__ ("mulhdu %0,%1,%2" : "=r" (rhi) : "%r" (op1), "r" (op2));	\
  } while (0)

#define muld_u64(rlo,rhi,op1,op2) \
  do {									\
    uint64_t __muld_op1 = (op1);                                        \
    uint64_t __muld_op2 = (op2);					\
    mulh_u64(rhi,op1,op2);                                              \
    (rlo) = __muld_op1 * __muld_op2;					\
  } while (0)

#if 0

#define blog_u64(log,op) \
  do {                                                                  \
    int __blog_log;                                                     \
    __asm__ ("{cntlz|cntlzw} %0,%1" : "=r" (__blog_log) : "r" (op));    \
    (log) = 63 - __blog_log;                                            \
  } while (0)

#define bxlog_u64(log,rop,op) \
  do {                                                                  \
    int __blog_log;                                                     \
    __asm__ ("{cntlz|cntlzw} %0,%1" : "=r" (__blog_log) : "r" (op));    \
    (log) = 63 - __blog_log;                                            \
    (rop) = (op) << __blog_log;                                         \
  } while (0)
    
#define bval_u64(val,op) \
  do {                                                                  \
    blog_u64(val, (op) & -(op));                                        \
  } while (0)

#define bxval_u64(val,rop,op) \
  do {                                                                  \
    bval_u64(val,op);                                                   \
    (rop) = (op) >> (val);                                              \
  } while (0)

#endif

#endif /* ARITH_ARCH_H */

