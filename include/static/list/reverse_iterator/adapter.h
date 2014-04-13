#ifndef __STUMPLESS_STATIC_LIST_REVERSE_ITERATOR_ADAPTER_H
#define __STUMPLESS_STATIC_LIST_REVERSE_ITERATOR_ADAPTER_H

#include <stumpless/public_name.h>

#include "private/type.h"

struct __STUMPLESS_NAME( AdapterListReverseIterator ) {
  ListReverseIterator * iterator;
};

#endif
