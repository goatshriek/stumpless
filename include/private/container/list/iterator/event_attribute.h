#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_EVENT_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_EVENT_ATTRIBUTE_H

#include "private/type.h"

EventAttributeListIterator *
CopyEventAttributeListIterator
( const EventAttributeListIterator * );

void
DestroyEventAttributeListIterator
( EventAttributeListIterator * );

unsigned short
EventAttributeListIteratorHasNext
( const EventAttributeListIterator * );

EventAttributeListIterator *
NewEventAttributeListIterator
( EventAttributeList *, int );

EventAttribute *
NextInEventAttributeListIterator
( EventAttributeListIterator * );

#endif
