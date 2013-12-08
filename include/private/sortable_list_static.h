#ifndef STUMPLESS_PRIVATE_SORTABLE_LIST_STATIC_H
#define STUMPLESS_PRIVATE_SORTABLE_LIST_STATIC_H

#include <stdint.h>

#include "private/type.h"

struct Node;

typedef struct Node
        Node;

struct SortableList {
  short ( *compare )( const void *, const void *, Dictionary * );
  Node * current;
  Node * first;
  Node * last;
  Node * previous;
  Dictionary * options;
};

struct Node {
  intptr_t neighbors;
  void * value;
};

static
void
DestroyNode
( Node *, intptr_t );

static
SortableList *
SortList
( SortableList * );

#endif
