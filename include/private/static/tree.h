#ifndef STUMPLESS_PRIVATE_STATIC_TREE_H
#define STUMPLESS_PRIVATE_STATIC_TREE_H

#include <stdint.h>

#include "private/type.h"

struct Dimension;
struct Iterator;
struct Node;

typedef struct Dimension
        Dimension;
typedef struct Iterator
        Iterator;
typedef struct Node
        Node;

struct Dimension {
  List * comparisons;
  unsigned index;
  Iterator * iterator;
  const char * name;
  Dictionary * options;
  Node * root;
  Tree * tree;
};

struct Iterator {
  unsigned index;
  Stack * path;
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
AddAsLeftChild
( Dimension *, Node *, Node *, Stack * );

static
Dimension *
AddAsRightChild
( Dimension *, Node *, Node *, Stack * );

static
Dimension *
AddToDimension
( Dimension *, Node * );

static
void
DestroyNode
( Node * );

static
unsigned short
IteratorIsDone
( Iterator * );

static
unsigned
MaxNodeHeight
( Node *, Node *, unsigned );

static
Iterator *
NewIterator
( Dimension * );

static
Node *
NewNode
( unsigned );

static
void *
NextInIterator
( Iterator * );

static
Dimension *
RestructureDimension
( Dimension *, Stack * );

static
short
RunComparisonList
( List *, void *, void *, Dictionary * );

#endif
