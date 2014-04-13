#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_COMPARATOR_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_COMPARATOR_H

#include "private/type.h"

unsigned short
ComparatorListReverseIteratorHasNext
( const ComparatorListReverseIterator * );

ComparatorListReverseIterator *
CopyComparatorListReverseIterator
( const ComparatorListReverseIterator * );

void
DestroyComparatorListReverseIterator
( ComparatorListReverseIterator * );

ComparatorListReverseIterator *
NewComparatorListReverseIterator
( ComparatorList *, int );

Comparator *
NextInComparatorListReverseIterator
( ComparatorListReverseIterator * );

#endif
