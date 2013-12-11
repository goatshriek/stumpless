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
  Node ** left_children;
  Node ** right_children;
  void * value;
};

struct Tree {
  Dimension * current_dimension;
  List * dimensions;
  Dictionary * options;
};

static
void
DestroyNode
( Node * );

#endif
