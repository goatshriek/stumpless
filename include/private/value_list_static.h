#ifndef STUMPLESS_PRIVATE_VALUE_LIST_STATIC_H
#define STUMPLESS_PRIVATE_VALUE_LIST_STATIC_H

#include <public_name.h>

struct Node;

typedef struct Node
        Node;

struct __STUMPLESS_NAME( ValueList ) {
  Node * current;
  Node * first;
  Node * last;
};

struct Node {
  Value * value;
  Node * next;
};

static
Status *
AppendNodeToValueList
( ValueList *, Node * );

static
void
DestroyNode
( Node * );

static
Status *
PrependNodeToValueList
( ValueList *, Node * );

#endif
