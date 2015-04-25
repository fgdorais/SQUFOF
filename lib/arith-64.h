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
#error "arith-64.h: Do note include this this file directly, include arith.h instead."
#endif

#ifndef __ARITH_64_H__
#define __ARITH_64_H__

#define addd_u64_gen(rlo,rhi,alo,ahi,blo,bhi) \
  do {                                                                  \
    uint64_t __addd_rlo = (alo) + (blo);                                \
    (rhi) = (ahi) + (bhi) + (__addd_rlo < (alo));                       \
    (rlo) = __addd_rlo;                                                 \
  } while (0)

#define subd_u64_gen(rlo,rhi,alo,ahi,blo,bhi) \
  do {                                                                  \
    uint64_t __subd_rlo = (alo) - (blo);                                \
    (rhi) = (ahi) - (bhi) - ((alo) < (blo));                            \
    (rlo) = __subd_rlo;                                                 \
  } while (0)

#define muld_u64_gen(plo,phi,opx,opy) \
  do {                                                                  \
    uint64_t __muld_pp0;                                                \
    uint64_t __muld_pp1;                                                \
    uint64_t __muld_pp2;                                                \
    uint64_t __muld_pp3;                                                \
    uint64_t __muld_xlo = (opx) & UINT64_C(0xFFFFFFFF);                 \
    uint64_t __muld_ylo = (opy) & UINT64_C(0xFFFFFFFF);                 \
    uint64_t __muld_xhi = (opx) >> 32;                                  \
    uint64_t __muld_yhi = (opy) >> 32;                                  \
    __muld_pp0 = __muld_xlo * __muld_ylo;                               \
    __muld_pp1 = __muld_xlo * __muld_yhi;                               \
    __muld_pp2 = __muld_xhi * __muld_ylo;                               \
    __muld_pp3 = __muld_xhi * __muld_yhi;                               \
    __muld_pp1 += __muld_pp0 >> 32; /* no carry */                      \
    __muld_pp1 += __muld_pp2;                                           \
    (phi) = __muld_pp3 + (__muld_pp1 >> 32)                             \
          + ((uint64_t)(__muld_pp1 < __muld_pp2) << 32);                \
    (plo) = (__muld_pp1 << 32) | (__muld_pp0 & UINT64_C(0xFFFFFFFF));   \
  } while (0)

#define divd_u64_gen(quo,rem,nlo,nhi,den) \
  do {                                                                  \
    uint64_t __divd_dhi = (den) >> 32;                                  \
    uint64_t __divd_dlo = (den) & UINT64_C(0xFFFFFFFF);                 \
    uint64_t __divd_qhi;                                                \
    uint64_t __divd_qlo;                                                \
    uint64_t __divd_rhi;                                                \
    uint64_t __divd_rlo;                                                \
    uint64_t __divd_aux;                                                \
    /* ASSERT((nhi) < (den)); */                                        \
    divrem_u64(__divd_qhi,__divd_rhi,(nhi),__divd_dhi);                 \
    __divd_aux = __divd_qhi * __divd_dlo;                               \
    __divd_rhi = (__divd_rhi << 32) | ((nlo) >> 32);                    \
    if (__divd_rhi < __divd_aux) {                                      \
       __divd_qhi--;                                                    \
       __divd_rhi += (den);                                             \
       if ((__divd_rhi >= (den)) && (__divd_rhi < __divd_aux)) {        \
         __divd_qhi--;                                                  \
         __divd_rhi += (den);                                           \
       }                                                                \
    }                                                                   \
    __divd_rhi -= __divd_aux;                                           \
    divrem_u64(__divd_qlo,__divd_rlo,__divd_rhi,__divd_dhi);            \
    __divd_aux = __divd_qlo * __divd_dlo;                               \
    __divd_rlo = (__divd_rlo << 32) | ((nlo) >> 32);                    \
    if (__divd_rlo < __divd_aux) {                                      \
       __divd_qlo--;                                                    \
       __divd_rlo += (den);                                             \
       if ((__divd_rlo >= (den)) && (__divd_rlo < __divd_aux)) {        \
          __divd_qlo--;                                                 \
          __divd_rlo += (den);                                          \
       }                                                                \
    }                                                                   \
    __divd_rlo -= __divd_aux;                                           \
    (quo) = (__divd_qhi << 32) | __divd_qlo;                            \
    (rem) = __divd_rlo;                                                 \
  } while (0)

#define bxval_u64_gen(val,rop,op) \
  do {                                                                  \
    uint64_t __bxval_rop = (op);                                        \
    int __bxval_val = 0;                                                \
    if ((__bxval_rop & UINT64_C(0xFFFFFFFF)) == UINT64_C(0))            \
      { __bxval_val += 32; __bxval_rop >>= 32; }                        \
    if ((__bxval_rop & UINT64_C(0xFFFF)) == UINT64_C(0))                \
      { __bxval_val += 16; __bxval_rop >>= 16; }                        \
    if ((__bxval_rop & UINT64_C(0xFF)) == UINT64_C(0))                  \
      { __bxval_val +=  8; __bxval_rop >>=  8; }                        \
    if ((__bxval_rop & UINT64_C(0xF)) == UINT64_C(0))                   \
      { __bxval_val +=  4; __bxval_rop >>=  4; }                        \
    if ((__bxval_rop & UINT64_C(0x3)) == UINT64_C(0))                   \
      { __bxval_val +=  2; __bxval_rop >>=  2; }                        \
    if ((__bxval_rop & UINT64_C(0x1)) == UINT64_C(0))                   \
      { __bxval_val +=  1; __bxval_rop >>=  1; }                        \
    (val) = __bxval_val;                                                \
    (rop) = __bxval_rop;                                                \
  } while (0)

#define bxlog_u64_gen(log,rop,op) \
  do {                                                                  \
    uint64_t __bxlog_rop = (op);                                        \
    int __bxlog_log = 64;                                               \
    if (__bxlog_rop < (UINT64_C(1) << 32))                              \
      { __bxlog_log -= 32; __bxlog_rop <<= 32; }                        \
    if (__bxlog_rop < (UINT64_C(1) << 48))                              \
      { __bxlog_log -= 16; __bxlog_rop <<= 16; }                        \
    if (__bxlog_rop < (UINT64_C(1) << 56))                              \
      { __bxlog_log -=  8; __bxlog_rop <<=  8; }                        \
    if (__bxlog_rop < (UINT64_C(1) << 60))                              \
      { __bxlog_log -=  4; __bxlog_rop <<=  4; }                        \
    if (__bxlog_rop < (UINT64_C(1) << 62))                              \
      { __bxlog_log -=  2; __bxlog_rop <<=  2; }                        \
    if (__bxlog_rop < (UINT64_C(1) << 63))                              \
      { __bxlog_log -=  1; __bxlog_rop <<=  1; }                        \
    (log) = __bxlog_log;                                                \
    (rop) = __bxlog_rop;                                                \
  } while (0)

#define gcd_u64_div(gcd,op1,op2) \
  do {                                                                  \
    uint64_t __egcd_op1 = (op1);                                        \
    uint64_t __egcd_op2 = (op2);                                        \
    while (1) {                                                         \
      if (__egcd_op1 == 0) break;                                       \
      __egcd_op2 %= __egcd_op1;                                         \
      if (__egcd_op2 == 0) break;                                       \
      __egcd_op1 %= __egcd_op2;                                         \
    }                                                                   \
    (gcd) = __egcd_op1 | __egcd_op2;                                    \
  } while (0)

#define xgcd_u64_div(gcd,cof,op1,op2) \
  do {                                                                  \
    uint64_t __exgcd_mod = (op2);                                       \
    uint64_t __exgcd_op1 = (op1);                                       \
    uint64_t __exgcd_op2 = __exgcd_mod;                                 \
    uint64_t __exgcd_cf1 = UINT64_C(1);                                 \
    uint64_t __exgcd_cf2 = UINT64_C(0);                                 \
    uint64_t __exgcd_quo;                                               \
    while (1) {                                                         \
      if (__exgcd_op1 == UINT64_C(0)) {                                 \
	(gcd) = __exgcd_op2;                                            \
        (cof) = __exgcd_mod - __exgcd_cf2;                              \
	break;                                                          \
      }                                                                 \
      divrem_u64(__exgcd_quo,__exgcd_op2,__exgcd_op2,__exgcd_op1);      \
      __exgcd_cf2 += __exgcd_cf1*__exgcd_quo;                           \
      if (__exgcd_op2 == UINT64_C(0)) {                                 \
	(gcd) = __exgcd_op1;                                            \
        (cof) = __exgcd_cf1;                                            \
	break;                                                          \
      }                                                                 \
      divrem_u64(__exgcd_quo,__exgcd_op1,__exgcd_op1,__exgcd_op2);      \
      __exgcd_cf1 += __exgcd_cf2*__exgcd_quo;                           \
    }                                                                   \
  } while (0)

#define gcd_u64_bin(gcd,op1,op2) \
  do {                                                                  \
    uint64_t __bgcd_op1 = (op1);                                        \
    uint64_t __bgcd_op2 = (op2);                                        \
    int __bgcd_val;                                                     \
    int __bgcd_tmp;                                                     \
    bxval_u64(__bgcd_val,__bgcd_op1,__bgcd_op1);                        \
    bxval_u64(__bgcd_tmp,__bgcd_op2,__bgcd_op2);                        \
    __bgcd_val = (__bgcd_tmp<__bgcd_val) ? (__bgcd_tmp) : (__bgcd_val); \
    while (__bgcd_op1 != __bgcd_op2) {                                  \
      if (__bgcd_op1 < __bgcd_op2) {                                    \
        bxval_u64(__bgcd_tmp,__bgcd_op2, __bgcd_op2 - __bgcd_op1);      \
      } else {                                                          \
        bxval_u64(__bgcd_tmp,__bgcd_op1, __bgcd_op1 - __bgcd_op2);      \
      }                                                                 \
    }                                                                   \
    (gcd) = __bgcd_op1 << __bgcd_val;                                   \
  } while (0)

#define xgcd_u64_bin(gcd,cf1,op1,op2) \
  do {                                                                  \
    uint64_t __bxgcd_mod = (op2);                                       \
    uint64_t __bxgcd_hlf = (__bxgcd_mod >> 1) + UINT64_C(1);            \
    uint64_t __bxgcd_op1 = (op1);                                       \
    uint64_t __bxgcd_op2 = __bxgcd_mod;                                 \
    uint64_t __bxgcd_cf1 = UINT64_C(1);                                 \
    uint64_t __bxgcd_cf2 = UINT64_C(0);                                 \
    uint64_t __bxgcd_tmp;                                               \
    if ((__bxgcd_op1 & UINT64_C(1)) == UINT64_C(0)) {                   \
      __bxgcd_op1 = __bxgcd_mod - __bxgcd_op1;                          \
      __bxgcd_cf1 = __bxgcd_mod - UINT64_C(1);                          \
    }                                                                   \
    while (__bxgcd_op1 != __bxgcd_op2) {                                \
      if (__bxgcd_op1 < __bxgcd_op2) {                                  \
        __bxgcd_tmp = __bxgcd_cf2 - __bxgcd_cf1;                        \
        __bxgcd_cf2 = (__bxgcd_cf2 < __bxgcd_cf1) ?                     \
          (__bxgcd_tmp + __bxgcd_mod) : (__bxgcd_tmp);                  \
        __bxgcd_op2 -= __bxgcd_op1;                                     \
        do {                                                            \
          __bxgcd_tmp = __bxgcd_cf2 >> 1;                               \
          __bxgcd_cf2 = ((__bxgcd_cf2 & UINT64_C(1)) != UINT64_C(0)) ?  \
            (__bxgcd_tmp + __bxgcd_hlf) : (__bxgcd_tmp);                \
          __bxgcd_op2 >>= 1;                                            \
        } while ((__bxgcd_op2 & UINT64_C(1)) == UINT64_C(0));           \
      } else {                                                          \
        __bxgcd_tmp = __bxgcd_cf1 - __bxgcd_cf2;                        \
        __bxgcd_cf1 = (__bxgcd_cf1 < __bxgcd_cf2) ?                     \
          (__bxgcd_tmp + __bxgcd_mod) : (__bxgcd_tmp);                  \
        __bxgcd_op1 -= __bxgcd_op2;                                     \
        do {                                                            \
          __bxgcd_tmp = __bxgcd_cf1 >> 1;                               \
          __bxgcd_cf1 = ((__bxgcd_cf1 & UINT64_C(1)) != UINT64_C(0)) ?  \
            (__bxgcd_tmp + __bxgcd_hlf) : (__bxgcd_tmp);                \
          __bxgcd_op1 >>= 1;                                            \
        } while ((__bxgcd_op1 & UINT64_C(1)) == UINT64_C(0));           \
      }                                                                 \
    }                                                                   \
    (cf1) = __bxgcd_cf1;                                                \
    (gcd) = __bxgcd_op1;                                                \
  } while (0)

#ifndef divrem_u64
#if 0
#define divrem_u64(quo,rem,num,den) \
  do {                                                                  \
    uint64_t __div_den = (den);                                         \
    uint64_t __div_num = (num);                                         \
    (quo) = __div_num / __div_den;                                      \
    (rem) = __div_num % __div_den;                                      \
  } while (0)
#else
#define divrem_u64(quo,rem,num,den) \
  do {                                                                  \
    uint64_t __div_den = (den);                                         \
    uint64_t __div_num = (num);                                         \
    (quo) = __div_num / __div_den;                                      \
    (rem) = __div_num - (quo) * __div_den;                              \
  } while (0)
#endif
#endif

#ifndef addd_u64
#define addd_u64 addd_u64_gen
#endif

#ifndef subd_u64
#define subd_u64 muld_u64_gen
#endif

#ifndef muld_u64
#define muld_u64 muld_u64_gen
#endif

#ifndef mulh_u64
#define mulh_u64(rhi,op1,op2) \
  do {                                                                  \
    uint64_t __mulh_rlo;                                                \
    muld_u64(__mulh_rlo,(rhi),(op1),(op2));                             \
  } while (0)
#endif

#ifndef divd_u64
#define divd_u64 divd_u64_gen
#endif

#ifndef remd_u64
#define remd_u64(res,nlo,nhi,den) \
  do {                                                                  \
    uint64_t __remd_quo;                                                \
    divd_u64(__remd_quo,(res),(nlo),(nhi),(den));                       \
  } while (0)
#endif

#ifndef binv_u64
#define binv_u64(inv,arg) \
  do {                                                                  \
    uint64_t __binv_arg = (arg);                                        \
    uint64_t __binv_inv;                                                \
    __binv_inv = (uint64_t)(__binv_table[(__binv_arg/2) & 0x7f]);       \
    __binv_inv = 2*__binv_inv - __binv_inv*__binv_inv*__binv_arg;       \
    __binv_inv = 2*__binv_inv - __binv_inv*__binv_inv*__binv_arg;       \
    __binv_inv = 2*__binv_inv - __binv_inv*__binv_inv*__binv_arg;       \
    (inv) = __binv_inv;                                                 \
  } while (0)
#endif

#ifndef bxlog_u64
#define bxlog_u64 bxlog_u64_gen
#endif

#ifndef blog_u64
#define blog_u64(log,op) \
  do {                                                                  \
    uint64_t __blog_xop;                                                \
    bxlog_u64((log),__blog_xop,(op));                                   \
  } while (0)
#endif

#ifndef bxval_u64
#define bxval_u64 bxval_u64_gen
#endif

#ifndef bval_u64
#define bval_u64(val,op) \
  do {                                                                  \
    uint64_t __bval_xop;                                                \
    bxval_u64((val),__bval_xop,(op));                                   \
  } while (0)
#endif

#ifndef xgcd_u64
#define xgcd_u64 xgcd_u64_bin
#endif

#ifndef gcd_u64
#define gcd_u64 gcd_u64_bin
#endif

#endif /* ARITH_64_H */
