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
  dimension_t index;
  const char * name;
  Dictionary * options;
  Node * root;
}

struct Node {
  intptr_t * children;
  void * value;
};

struct Tree {
  dimension_t current_dimension;
  Dimension ** dimensions;
  unsigned short dimension_count;
  Dictionary * options;
};

static
void
DestroyDimension
( Dimension * );

static
void
DestroyNode
( Node *, intptr_t );

#endif
