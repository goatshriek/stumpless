#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_VALUE_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_VALUE_H

#include "private/type.h"

ValueListIterator *
CopyValueListIterator
( const ValueListIterator * );

void
DestroyValueListIterator
( ValueListIterator * );

unsigned short
ValueListIteratorHasNext
( const ValueListIterator * );

ValueListIterator *
NewValueListIterator
( ValueList *, int );

Value *
NextInValueListIterator
( ValueListIterator * );

#endif
