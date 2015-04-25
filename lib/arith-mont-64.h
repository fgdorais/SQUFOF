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
#error "arith-mont-64.h: Do note include this this file directly, include arith.h instead."
#endif

#ifndef __ARITH_MONT_64_H__
#define __ARITH_MONT_64_H__

#include "arith.h"

#define madd_u64(r,a,b,mod) \
  do {                                                                  \
    uint64_t __madd_c = (mod) - (b);                                    \
    msub_u64((r),(a),__madd_c,(mod));                                   \
  } while (0)

#define msub_u64(r,a,b,mod) \
  do {                                                                  \
    uint64_t __msub_d = (a) - (b);                                      \
    (r) = ((a) < (b)) ? (__msub_d + (mod)) : (__msub_d);                \
  } while (0)

#define mmul_u64(r,a,b,mod) \
  do {                                                                  \
    uint64_t __mmul_plo;                                                \
    uint64_t __mmul_phi;                                                \
    muld_u64(__mmul_plo,__mmul_phi,(a),(b));                            \
    remd_u64((res),__mmul_plo,__mmul_phi,(mod));                        \
  } while (0)

#define mmulc_u64(res,a,b,mod,aux) \
  do {                                                                  \
    uint64_t __mmulc_plo;                                               \
    uint64_t __mmulc_phi;                                               \
    muld_u64(__mmulc_plo,__mmulc_phi,(a),(b));                          \
    mredc_u64((res),__mmulc_plo,__mmulc_phi,(mod),(aux));               \
  } while (0)

#define mredc_u64(res,alo,ahi,mod,aux) \
  do {                                                                  \
    uint64_t __mredc_u;                                                 \
    uint64_t __mredc_v = (alo)*(aux);                                   \
    mulh_u64(__mredc_u,__mredc_v,(mod));                                \
    msub_u64((res),(ahi),__mredc_u,(mod));                              \
  } while (0)

#define maddd_u64(rlo,rhi,alo,ahi,blo,bhi,mod) \
  do {                                                                  \
    uint64_t __maddd_rlo = (alo) + (blo);                               \
    uint64_t __maddd_rhi = (ahi) + (bhi);                               \
    if (__maddd_rlo >= (mod)) {                                         \
      __maddd_rlo -= (mod);                                             \
      __maddd_rhi += UINT64_C(1);                                       \
    }                                                                   \
    (rlo) = __maddd_rlo;                                                \
    (rhi) = (__maddd_rhi >= (mod)) ?                                    \
            (__maddd_rhi - (mod)) : (__maddd_rhi);                      \
  } while (0)

#define msubd_u64(rlo,rhi,alo,ahi,blo,bhi,mod) \
  do {                                                                  \
    uint64_t __msubd_rlo = (alo) - (blo);                               \
    uint64_t __msubd_rhi = (ahi) - (bhi);                               \
    if ((int64_t)(__msubd_rlo) < INT64_C(0)) {                          \
      __msubd_rlo += (mod);                                             \
      __msubd_rhi -= UINT64_C(1);                                       \
    }                                                                   \
    (rlo) = __msubd_rlo;                                                \
    (rhi) = ((int64_t)(__msubd_rhi) < INT64_C(0)) ?                     \
            (__msubd_rhi + (mod)) : (__msubd_rhi);                      \
  } while (0)

#define mdbld_u64(rlo,rhi,alo,ahi,mod) \
  do {                                                                  \
    uint64_t __mdbld_rlo = (alo) << 1;                                  \
    uint64_t __mdbld_rhi = (ahi) << 1;                                  \
    if (__mdbld_rlo >= (mod)) {                                         \
      __mdbld_rlo -= (mod);                                             \
      __mdbld_rhi += UINT64_C(1);                                       \
    }                                                                   \
    (rlo) = __mdbld_rlo;                                                \
    (rhi) = (__mdbld_rhi >= (mod)) ?                                    \
            (__mdbld_rhi - (mod)) : (__mdbld_rhi);                      \
  } while (0)

#define mmuld_u64(rlo,rhi,alo,ahi,blo,bhi,mod,aux) \
  do {                                                                  \
    uint64_t __mmuld_s0;                                                \
    uint64_t __mmuld_s1;                                                \
    uint64_t __mmuld_t0;                                                \
    uint64_t __mmuld_t1;                                                \
    uint64_t __mmuld_u0;                                                \
    uint64_t __mmuld_u1;                                                \
    uint64_t __mmuld_v0;                                                \
    uint64_t __mmuld_v1;                                                \
    muld_u64(__mmuld_t0,__mmuld_t1,(alo),(blo));                        \
    __mmuld_v0 = __mmuld_t0 * (aux);                                    \
    mulh_u64(__mmuld_u0,__mmuld_v0,(mod));                              \
    __mmuld_u0 = __mmuld_t1 - __mmuld_u0 + (mod);                       \
    muld_u64(__mmuld_s0,__mmuld_s1,(alo),(bhi));                        \
    addd_u64(__mmuld_t0,__mmuld_t1,__mmuld_s0,__mmuld_s1,               \
	     __mmuld_v0,UINT64_C(0));                                   \
    muld_u64(__mmuld_s0,__mmuld_s1,(blo),(ahi));                        \
    addd_u64(__mmuld_t0,__mmuld_t1,__mmuld_t0,__mmuld_t1,               \
	     __mmuld_s0,__mmuld_s1);                                    \
    __mmuld_v1 = __mmuld_t0 * (aux);                                    \
    mulh_u64(__mmuld_u1,__mmuld_v1,(mod));                              \
    __mmuld_u1 = __mmuld_t1 - __mmuld_u1 + (mod) - UINT64_C(1);         \
    if (__mmuld_u0 >= (mod)) {                                          \
      __mmuld_u0 -= (mod);                                              \
      __mmuld_u1 += UINT64_C(1);                                        \
    }                                                                   \
    (rlo) = __mmuld_u0;                                                 \
    (rhi) = (__mmuld_u1 >= (mod)) ? (__mmuld_u1-(mod)) : (__mmuld_u1);  \
  } while (0)

#define msqrd_u64(rlo,rhi,alo,ahi,mod,aux) \
  do {                                                                  \
    uint64_t __msqrd_t0;                                                \
    uint64_t __msqrd_t1;                                                \
    uint64_t __msqrd_u0;                                                \
    uint64_t __msqrd_u1;                                                \
    uint64_t __msqrd_v0;                                                \
    uint64_t __msqrd_v1;                                                \
    muld_u64(__msqrd_t0,__msqrd_t1,(alo),(alo));                        \
    __msqrd_v0 = __msqrd_t0 * (aux);                                    \
    mulh_u64(__msqrd_u0,__msqrd_v0,(mod));                              \
    __msqrd_u0 = __msqrd_t1 - __msqrd_u0 + (mod);                       \
    muld_u64(__msqrd_t0,__msqrd_t1,(alo),(ahi)<<1);                     \
    addd_u64(__msqrd_t0,__msqrd_t1,__msqrd_t0,__msqrd_t1,               \
	     __msqrd_v0,UINT64_C(0));                                   \
    __msqrd_v1 = __msqrd_t0 * (aux);                                    \
    mulh_u64(__msqrd_u1,__msqrd_v1,(mod));                              \
    __msqrd_u1 = __msqrd_t1 - __msqrd_u1 + (mod) - UINT64_C(1);         \
    if (__msqrd_u0 >= (mod)) {                                          \
      __msqrd_u0 -= (mod);                                              \
      __msqrd_u1 += UINT64_C(1);                                        \
    }                                                                   \
    (rlo) = __msqrd_u0;                                                 \
    (rhi) = (__msqrd_u1 >= (mod)) ? (__msqrd_u1-(mod)) : (__msqrd_u1);  \
  } while (0)

#endif /* ARITH_MONT_64_H */
