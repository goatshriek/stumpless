#ifndef STUMPLESS_PRIVATE_DICTIONARY_STATIC_H
#define STUMPLESS_PRIVATE_DICIONTARY_STATIC_H

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

#endif
