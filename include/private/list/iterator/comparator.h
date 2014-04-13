#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_COMPARATOR_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_COMPARATOR_H

#include "private/type.h"

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
( ComparatorList *, int );

Comparator *
NextInComparatorListIterator
( ComparatorListIterator * );

#endif
