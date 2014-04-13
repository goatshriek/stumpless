#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_COMPARATOR_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_COMPARATOR_H

#include "private/type.h"

unsigned short
ComparatorListConstReverseIteratorHasNext
( const ComparatorListConstReverseIterator * );

ComparatorListConstReverseIterator *
CopyComparatorListConstReverseIterator
( const ComparatorListConstReverseIterator * );

void
DestroyComparatorListConstReverseIterator
( ComparatorListConstReverseIterator * );

ComparatorListConstReverseIterator *
NewComparatorListConstReverseIterator
( const ComparatorList *, int );

const Comparator *
NextInComparatorListConstReverseIterator
( ComparatorListConstReverseIterator * );

#endif
