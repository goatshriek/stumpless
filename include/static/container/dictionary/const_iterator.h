#ifndef __STUMPLESS_STATIC_CONTAINER_DICTIONARY_CONST_ITERATOR_H
#define __STUMPLESS_STATIC_CONTAINER_DICTIONARY_CONST_ITERATOR_H

#include "private/type.h"
#include "static/container/dictionary.h"

struct DictionaryConstIterator {
  const Dictionary *dictionary;
  Node *current;
};

#endif
