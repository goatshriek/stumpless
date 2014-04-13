#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_H

#include "private/type.h"

ListReverseIterator *
CopyListReverseIterator
( const ListReverseIterator * );

void
DestroyListReverseIterator
( ListReverseIterator * );

unsigned short
ListReverseIteratorHasNext
( const ListReverseIterator * );

ListReverseIterator *
NewListReverseIterator
( List *, int );

void *
NextInListReverseIterator
( ListReverseIterator * );

#endif
