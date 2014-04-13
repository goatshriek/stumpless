#ifndef __STUMPLESS_STATIC_LIST_ITERATOR_ADAPTER_H
#define __STUMPLESS_STATIC_LIST_ITERATOR_ADAPTER_H

#include <stumpless/public_name.h>

#include "private/type.h"

struct __STUMPLESS_NAME( AdapterListIterator ) {
  ListIterator * iterator;
};

#endif
