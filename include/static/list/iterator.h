#ifndef __STUMPLESS_STATIC_LIST_ITERATOR_H
#define __STUMPLESS_STATIC_LIST_ITERATOR_H

#include "private/type.h"

#include "static/list.h"

struct ListIterator {
  Node * current;
  List * list;
  Node * previous;
};

#endif
