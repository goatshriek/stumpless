#ifndef STUMPLESS_PRIVATE_TREE_STATIC_H
#define STUMPLESS_PRIVATE_TREE_STATIC_H

#include <stdint.h>

#include "private/type.h"

struct Dimension;
struct Node;

typedef struct Dimension
        Dimension;
typedef struct Node
        Node;

struct Dimension {
  comparison_t * comparisons;
  unsigned short comparison_count;
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
  Dimension ** dimensions;
  unsigned short dimension_count;
  Dictionary * options;
};

static
void
DestroyNode
( Node *, intptr_t );

#endif
