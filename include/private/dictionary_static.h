#ifndef STUMPLESS_PRIVATE_DICTIONARY_STATIC_H
#define STUMPLESS_PRIVATE_DICIONTARY_STATIC_H

#include <stumpless/public_name.h>

#include "private/type.h"

struct Node;

typedef struct Node
        Node;

struct __STUMPLESS_NAME( Dictionary ) {
  Node * root;
};

struct Node {
  const char * key;
  Node * left_child;
  Node * parent;
  Node * right_child;
  void * value;
};

static
void
AddNode
( Node *, Node * );

static
void
DestroyNode
( Node * );

static
Node *
GetNode
( const char *, Node * );

static
void
LeftRotate
( Dictionary *, Node * );

static
void
ReplaceNode
( Dictionary *, Node *, Node * );

static
void
RightRotate
( Dictionary *, Node * );

static
void
Splay
( Dictionary *, Node * );

static
Node *
SubtreeMinimum
( Node * );

#endif
