#ifndef __STUMPLESS_STATIC_LIST_CONST_REVERSE_ITERATOR_H
#define __STUMPLESS_STATIC_LIST_CONST_REVERSE_ITERATOR_H

#include "private/type.h"

#include "static/list.h"

struct ListConstReverseIterator {
  Node * current;
  const List * list;
  Node * previous;
};

#endif
