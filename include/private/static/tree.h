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
  Node * current_node;
  unsigned index;
  const char * name;
  Dictionary * options;
  Node * root;
  Tree * tree;
};

struct Node {
  unsigned * heights;
  Node ** left_children;
  Node ** right_children;
  void * value;
};

struct Tree {
  Dimension * current_dimension;
  unsigned dimension_capacity;
  List * dimensions;
  Dictionary * options;
};

static
Dimension *
AddToDimension
( Dimension *, Node * );

static
Node *
BeginDimensionNodes
( Dimension * );

static
void
DestroyNode
( Node * );

static
unsigned
MaxNodeHeight
( Node *, Node *, unsigned );

static
Node *
NewNode
( unsigned );

static
Node *
NextNodeInDimension
( Dimension * );

static
Dimension *
RestructureDimension
( Dimension *, Stack * );

static
short
RunComparisonList
( List *, void *, void *, Dictionary * );

#endif
