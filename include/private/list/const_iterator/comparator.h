#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_COMPARATOR_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_COMPARATOR_H

#include "private/type.h"

unsigned short
ComparatorListConstIteratorHasNext
( const ComparatorListConstIterator * );

ComparatorListConstIterator *
CopyComparatorListConstIterator
( const ComparatorListConstIterator * );

void
DestroyComparatorListConstIterator
( ComparatorListConstIterator * );

ComparatorListConstIterator *
NewComparatorListConstIterator
( const ComparatorList *, int );

const Comparator *
NextInComparatorListConstIterator
( ComparatorListConstIterator * );

#endif
