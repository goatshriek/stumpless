#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_FILTER_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_FILTER_H

#include "private/type.h"

FilterListReverseIterator *
CopyFilterListReverseIterator
( const FilterListReverseIterator * );

void
DestroyFilterListReverseIterator
( FilterListReverseIterator * );

unsigned short
FilterListReverseIteratorHasNext
( const FilterListReverseIterator * );

FilterListReverseIterator *
NewFilterListReverseIterator
( FilterList *, int );

Filter *
NextInFilterListReverseIterator
( FilterListReverseIterator * );

#endif
