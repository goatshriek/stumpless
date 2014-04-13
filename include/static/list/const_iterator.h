#ifndef __STUMPLESS_STATIC_LIST_CONST_ITERATOR_H
#define __STUMPLESS_STATIC_LIST_CONST_ITERATOR_H

#include "private/type.h"

#include "static/list.h"

struct ListConstIterator {
  Node * current;
  const List * list;
  Node * previous;
};

#endif
