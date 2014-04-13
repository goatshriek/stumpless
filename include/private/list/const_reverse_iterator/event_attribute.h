#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_EVENT_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_EVENT_ATTRIBUTE_H

#include "private/type.h"

EventAttributeListConstReverseIterator *
CopyEventAttributeListConstReverseIterator
( const EventAttributeListConstReverseIterator * );

void
DestroyEventAttributeListConstReverseIterator
( EventAttributeListConstReverseIterator * );

unsigned short
EventAttributeListConstReverseIteratorHasNext
( const EventAttributeListConstReverseIterator * );

EventAttributeListConstReverseIterator *
NewEventAttributeListConstReverseIterator
( const EventAttributeList *, int );

const EventAttribute *
NextInEventAttributeListConstReverseIterator
( EventAttributeListConstReverseIterator * );

#endif
