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

typedef struct {
  int head;
  int tail;
  uint64_t p[Q_LENGTH];
  uint64_t q[Q_LENGTH];
} queue_t;

static inline
int queue_init (queue_t *queue) {

  queue->head = 0;
  queue->tail = 0;
  
  return 0;
}

static inline
int queue_size (queue_t *queue) {
  int size = queue->tail - queue->head;
  
  return (size < 0) ? (size + Q_LENGTH) : (size);
}

static inline
int queue_put (queue_t *queue, uint64_t p, uint64_t q) {
  int next = (queue->tail+1)%Q_LENGTH;
  
  if (next == queue->head) {
    return 1;
  }

  queue->p[queue->tail] = p;
  queue->q[queue->tail] = q;
  
  queue->tail = next;
  
  return 0;
}

static inline
int queue_get (queue_t *queue, uint64_t *p, uint64_t *q) {

  if (queue->head == queue->tail) {
    return 1;
  }
	
  *p = queue->p[queue->head];
  *q = queue->q[queue->head];

  queue->head = (queue->head + 1)%Q_LENGTH;
  
  return 0;
}

int squfof_forth (uint64_t *p, uint64_t *q, uint64_t sqrtn) {
  uint64_t q_limit;
  queue_t queue;

  uint64_t p0;
  uint64_t q0 = 1;
  uint64_t p1 = *p;
  uint64_t q1 = *q;

  uint64_t quot;
  uint64_t test;
  uint64_t root;
  
  queue_init (&queue);

  sqrt_u64(q_limit, sqrtn << 1);
  q_limit++;

  do {
    quot = (sqrtn + p1)/q1;
    p0 = quot*q1 - p1;
    test = ((q1 & 1) == 0) ? (q1 >> 1) : (q1);
    if ((test <= q_limit) && (queue_put (&queue, p1%test, test) != 0)) {
      return -1;
    }
    q0 += quot*(p1 - p0);
    
    sqrt_u64(root, q0);

    if (q0 == root*root) {
      do {
	uint64_t pp;
	uint64_t qq;
	
	if (queue_get (&queue, &pp, &qq) != 0) {
	  *p = p0;
	  *q = root;
	  return 0;
	}
	
	if (qq == root) {
	  if (root == 1) {
	    return 1;
	  } else if (((p0 - pp)%root) == 0) {
	    break;
	  }
	}
	
      } while (1);
    }
    
    quot = (sqrtn + p0)/q0;
    p1 = quot*q0 - p0;
    test = ((q0 & 1) == 0) ? (q0 >> 1) : (q0);
    if ((test <= q_limit) && (queue_put (&queue, p0%test, test) != 0)) {
      return -1;
    }
    q1 += quot*(p0 - p1);
  } while (1);
}
