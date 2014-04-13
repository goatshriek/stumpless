#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_FILTER_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_FILTER_H

#include "private/type.h"

FilterListIterator *
CopyFilterListIterator
( const FilterListIterator * );

void
DestroyFilterListIterator
( FilterListIterator * );

unsigned short
FilterListIteratorHasNext
( const FilterListIterator * );

FilterListIterator *
NewFilterListIterator
( FilterList *, int );

Filter *
NextInFilterListIterator
( FilterListIterator * );

#endif
