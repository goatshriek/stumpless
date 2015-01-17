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

/**
 * Checks to see if a ListIterator has a previous value.
 *
 * @param iterator the iterator to check for a previous value
 *
 * @return a positive value if a previous value exists, and a 0 if not.
 */
unsigned short
ListIteratorHasPrevious
( const ListIterator *iterator );

ListIterator *
NewListIterator
( List *, int );

void *
NextInListIterator
( ListIterator * );

void *
PreviousInListIterator
( ListIterator * );

#endif
