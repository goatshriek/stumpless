#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_H

#include "private/type.h"

ListIterator *
CopyListIterator
( const ListIterator * );

void
DestroyListIterator
( ListIterator * );

unsigned short
ListIteratorHasNext
( const ListIterator * );

ListIterator *
NewListIterator
( List *, int );

void *
NextInListIterator
( ListIterator * );

#endif
