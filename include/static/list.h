#ifndef __STUMPLESS_STATIC_LIST_H
#define __STUMPLESS_STATIC_LIST_H

#include <stdint.h>

#include "private/type.h"

#define XORNODES( first, second )                                              \
( ( Node * ) ( ( ( intptr_t ) ( first ) ) ^ ( ( intptr_t ) ( second ) ) ) )

struct Node;

typedef struct Node
        Node;

struct List {
  Node * first;
  Node * last;
};

struct Node {
  Node * neighbors;
  void * value;
};

static
void
DestroyNodes
( Node *, Node * );

static
void *
SeparateNodes
( Node *, Node *, void * );

#endif
