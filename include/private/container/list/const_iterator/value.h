#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_VALUE_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_VALUE_H

#include "private/type.h"

ValueListConstIterator *
CopyValueListConstIterator
( const ValueListConstIterator * );

void
DestroyValueListConstIterator
( ValueListConstIterator * );

unsigned short
ValueListConstIteratorHasNext
( const ValueListConstIterator * );

ValueListConstIterator *
NewValueListConstIterator
( const ValueList *, int );

const Value *
NextInValueListConstIterator
( ValueListConstIterator * );

#endif
