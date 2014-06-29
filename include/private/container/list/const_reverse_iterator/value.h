#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_VALUE_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_VALUE_H

#include "private/type.h"

ValueListConstReverseIterator *
CopyValueListConstReverseIterator
( const ValueListConstReverseIterator * );

void
DestroyValueListConstReverseIterator
( ValueListConstReverseIterator * );

unsigned short
ValueListConstReverseIteratorHasNext
( const ValueListConstReverseIterator * );

ValueListConstReverseIterator *
NewValueListConstReverseIterator
( const ValueList *, int );

const Value *
NextInValueListConstReverseIterator
( ValueListConstReverseIterator * );

#endif
