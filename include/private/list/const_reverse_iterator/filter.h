#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_FILTER_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_FILTER_H

#include "private/type.h"

FilterListConstReverseIterator *
CopyFilterListConstReverseIterator
( const FilterListConstReverseIterator * );

void
DestroyFilterListConstReverseIterator
( FilterListConstReverseIterator * );

unsigned short
FilterListConstReverseIteratorHasNext
( const FilterListConstReverseIterator * );

FilterListConstReverseIterator *
NewFilterListConstReverseIterator
( const FilterList *, int );

const Filter *
NextInFilterListConstReverseIterator
( FilterListConstReverseIterator * );

#endif
