#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_H

#include "private/type.h"

ListConstReverseIterator *
CopyListConstReverseIterator
( const ListConstReverseIterator * );

void
DestroyListConstReverseIterator
( ListConstReverseIterator * );

unsigned short
ListConstReverseIteratorHasNext
( const ListConstReverseIterator * );

ListConstReverseIterator *
NewListConstReverseIterator
( const List *, int );

const void *
NextInListConstReverseIterator
( ListConstReverseIterator * );

#endif
