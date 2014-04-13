#ifndef __STUMPLESS_STATIC_LIST_REVERSE_ITERATOR_H
#define __STUMPLESS_STATIC_LIST_REVERSE_ITERATOR_H

#include "private/type.h"

#include "static/list.h"

struct ListReverseIterator {
  Node * current;
  List * list;
  Node * previous;
};

#endif
