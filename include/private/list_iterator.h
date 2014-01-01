#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_H

#include "private/type.h"

ListIterator *
CopyListIterator
( ListIterator * );

void
DestroyListIterator
( ListIterator * );

unsigned short
ListIteratorHasNext
( ListIterator * );

void *
NextInListIterator
( ListIterator * );

#endif
