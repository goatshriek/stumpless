#ifndef STUMPLESS_PRIVATE_SORTABLE_LIST_STATIC_H
#define STUMPLESS_PRIVATE_SORTABLE_LIST_STATIC_H

#include "private/type.h"

struct Node;

typedef struct Node
        Node;

struct List {
  unsigned short ( *compare )( const void *, const void *, Dictionary * );
  Node * current;
  Node * first;
  Node * last;
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
