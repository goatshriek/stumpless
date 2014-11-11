#ifndef __STUMPLESS_STATIC_CONTAINER_DICTIONARY_H
#define __STUMPLESS_STATIC_CONTAINER_DICTIONARY_H

#include "private/type.h"

struct Node;

typedef struct Node
        Node;

struct Dictionary {
  Node *root;
};

struct Node {
  const char *key;
  Node *left_child;
  Node *parent;
  Node *right_child;
  void *value;
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
