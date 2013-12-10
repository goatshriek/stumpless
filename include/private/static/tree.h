#ifndef STUMPLESS_PRIVATE_STATIC_TREE_H
#define STUMPLESS_PRIVATE_STATIC_TREE_H

#include <stdint.h>

#include "private/type.h"

struct Dimension;
struct Node;

typedef struct Dimension
        Dimension;
typedef struct Node
        Node;

struct Dimension {
  List * comparisons;
  unsigned short index;
  const char * name;
  Dictionary * options;
  Node * root;
  Tree * tree;
};

struct Node {
  intptr_t * children;
  void * value;
};

struct Tree {
  unsigned short current_dimension;
  List * dimensions;
  Dictionary * options;
};

static
void
DestroyNode
( Node *, intptr_t );

#endif
