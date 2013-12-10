#ifndef STUMPLESS_PRIVATE_STATIC_LIST_H
#define STUMPLESS_PRIVATE_STATIC_LIST_H

#include "private/type.h"

struct Node;

typedef struct Node
        Node;

struct List {
  Node * current;
  Node * first;
  Node * last;
};

struct Node {
  Node * next;
  void * value;
};

static
void
DestroyNode
( Node * );

static
void *
SeparateNodes
( Node *, void * );

#endif
