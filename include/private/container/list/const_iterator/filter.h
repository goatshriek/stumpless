#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_FILTER_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_FILTER_H

#include "private/type.h"

FilterListConstIterator *
CopyFilterListConstIterator
( const FilterListConstIterator * );

void
DestroyFilterListConstIterator
( FilterListConstIterator * );

unsigned short
FilterListConstIteratorHasNext
( const FilterListConstIterator * );

FilterListConstIterator *
NewFilterListConstIterator
( const FilterList *, int );

const Filter *
NextInFilterListConstIterator
( FilterListConstIterator * );

#endif
