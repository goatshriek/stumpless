#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_EVENT_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_EVENT_ATTRIBUTE_H

#include "private/type.h"

EventAttributeListReverseIterator *
CopyEventAttributeListReverseIterator
( const EventAttributeListReverseIterator * );

void
DestroyEventAttributeListReverseIterator
( EventAttributeListReverseIterator * );

unsigned short
EventAttributeListReverseIteratorHasNext
( const EventAttributeListReverseIterator * );

EventAttributeListReverseIterator *
NewEventAttributeListReverseIterator
( EventAttributeList *, int );

EventAttribute *
NextInEventAttributeListReverseIterator
( EventAttributeListReverseIterator * );

#endif
