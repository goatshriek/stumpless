#ifndef __STUMPLESS_LIST_ITERATOR_VALUE_H
#define __STUMPLESS_LIST_ITERATOR_VALUE_H

#include <stumpless/type.h>

unsigned short
ValueListIteratorHasNext
( const ValueListIterator * );

ValueListIterator *
CopyValueListIterator
( const ValueListIterator * );

void
DestroyValueListIterator
( ValueListIterator * );

ValueListIterator *
NewValueListIterator
( ValueList * );

Value *
NextInValueListIterator
( ValueListIterator * );

#endif
