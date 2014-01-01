#ifndef STUMPLESS_PRIVATE_STATIC_LIST_ITERATOR_H
#define STUMPLESS_PRIVATE_STATIC_LIST_ITERATOR_H

#include "private/static/list.h"
#include "private/type.h"

struct ListIterator {
  Node * current;
  List * list;
};

#endif
