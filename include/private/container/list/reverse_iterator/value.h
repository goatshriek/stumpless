#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_VALUE_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_VALUE_H

#include "private/type.h"

ValueListReverseIterator *
CopyValueListReverseIterator
( const ValueListReverseIterator * );

void
DestroyValueListReverseIterator
( ValueListReverseIterator * );

unsigned short
ValueListReverseIteratorHasNext
( const ValueListReverseIterator * );

ValueListReverseIterator *
NewValueListReverseIterator
( ValueList *, int );

Value *
NextInValueListReverseIterator
( ValueListReverseIterator * );

#endif
