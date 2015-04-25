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

#include <stdlib.h>
#include <stdio.h>

#include "squfof.h"

int main (int argc, char **argv) {
  int errc;
  int argi;

  for (argi = 1, errc = 0; argi < argc; argi++) {
    uint64_t n;
    uint64_t f;
    uint64_t g;

    sscanf(argv[argi], "%"SCNu64, &n);

    f = squfof_u64(n);
    g = n / f;
    
    if (n != f*g) {
      errc++;
      printf("ERROR: n = %"PRIu64", f = %"PRIu64"\n", n, f);
    } else {
      printf("%"PRIu64" = %"PRIu64" * %"PRIu64"\n", n, f, g);
    }
    
  }

  if (errc != 0) {
    exit(EXIT_FAILURE);
  } else {
    exit(EXIT_SUCCESS);
  }

}
