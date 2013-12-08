#ifndef STUMPLESS_PRIVATE_SORTABLE_LIST_STATIC_H
#define STUMPLESS_PRIVATE_SORTABLE_LIST_STATIC_H

#include "private/type.h"

struct Node;

typedef struct Node
        Node;

struct SortableList {
  short ( *compare )( const void *, const void *, Dictionary * );
  Node * current;
  Node * first;
  Node * last;
  Dictionary * options;
};

struct Node {
  Node * neighbors;
  void * value;
};

static
void
DestroyNode
( Node * );

#endif
