#ifndef __STUMPLESS_LIST_ITERATOR_COMPARATOR_H
#define __STUMPLESS_LIST_ITERATOR_COMPARATOR_H

#include <stumpless/type.h>

unsigned short
ComparatorListIteratorHasNext
( const ComparatorListIterator * );

ComparatorListIterator *
CopyComparatorListIterator
( const ComparatorListIterator * );

void
DestroyComparatorListIterator
( ComparatorListIterator * );

ComparatorListIterator *
NewComparatorListIterator
( ComparatorList * );

Comparator *
NextInComparatorListIterator
( ComparatorListIterator * );

#endif
