#ifndef __STUMPLESS_LIST_ITERATOR_FILTER_H
#define __STUMPLESS_LIST_ITERATOR_FILTER_H

#include <stumpless/type.h>

unsigned short
FilterListIteratorHasNext
( const FilterListIterator * );

FilterListIterator *
CopyFilterListIterator
( const FilterListIterator * );

void
DestroyFilterListIterator
( FilterListIterator * );

FilterListIterator *
NewFilterListIterator
( FilterList * );

Filter *
NextInFilterListIterator
( FilterListIterator * );

#endif
