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

/**
 * Checks to see if a ListReverseIterator has a previous value.
 *
 * @param iterator the iterator to check for a previous value
 *
 * @return a positive value if a previous value exists, and a 0 if not
 */
unsigned short
ListReverseIteratorHasPrevious
( const ListReverseIterator *iterator );

ListReverseIterator *
NewListReverseIterator
( List *, int );

void *
NextInListReverseIterator
( ListReverseIterator * );

void *
PreviousInListReverseIterator
( ListReverseIterator *);

#endif
