#ifndef __STUMPLESS_PRIVATE_CONTAINER_LIST_CONST_ITERATOR_H
#define __STUMPLESS_PRIVATE_CONTAINER_LIST_CONST_ITERATOR_H

#include "private/type.h"

ListConstIterator *
CopyListConstIterator
( const ListConstIterator * );

void
DestroyListConstIterator
( ListConstIterator * );

unsigned short
ListConstIteratorHasNext
( const ListConstIterator * );

ListConstIterator *
NewListConstIterator
( const List *, int );

const void *
NextInListConstIterator
( ListConstIterator * );

#endif
