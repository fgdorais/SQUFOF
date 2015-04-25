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

#include <config.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "squfof.h"

double timing ()
{
  struct rusage ru;
  if (getrusage (RUSAGE_SELF, &ru) == -1)
    {
      return 0.0;
    }
  return (double)(ru.ru_utime.tv_sec) + 0.000001*(double)(ru.ru_utime.tv_usec);
}

#define A (565461)
#define B (554113)
#define LIMIT (500)

int time_test () {
  uint64_t x = 12345;
  double t_start = timing ();
  int rv = 0;
  int i;
  
  for (i=0; i<LIMIT; i++)
    {
      uint64_t f;
      uint64_t g;
      
      f = squfof_u64 (x);
      g = (f == UINT64_C(0)) ? x : x / f;

      if (x != f * g) {
	rv++;
	printf("ERROR %"PRIu64", %"PRIu64"\n", x, f);
      }

      x = A*x + B;
    }

  printf ("TIME %f\nERRS %d\n", (timing() - t_start), rv);

  return rv;
}

int eval_test (char *arg) {
  uint64_t x;
  uint64_t f;
  uint64_t g;

  if (sscanf (arg, "%"SCNu64, &x) < 1) {
    return 1;
  }

  f = squfof_u64 (x);
  g = (f == UINT64_C(0)) ? x : x / f;
  printf ("%"PRIu64" = %"PRIu64" * %"PRIu64"\n", x, f, g);

  return (x != f * g);
} 

int main (int argc, char **argv) {
  int argi;
  int retv;

  if (argc == 1) {
    retv = time_test ();
  } else {
    for (argi = 1, retv = 0; argi < argc; argi++) {
      retv += eval_test (argv[argi]);
    }
  }

  return retv;
}
