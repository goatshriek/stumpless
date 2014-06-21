#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_EVENT_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_EVENT_ATTRIBUTE_H

#include "private/type.h"

EventAttributeListConstIterator *
CopyEventAttributeListConstIterator
( const EventAttributeListConstIterator * );

void
DestroyEventAttributeListConstIterator
( EventAttributeListConstIterator * );

unsigned short
EventAttributeListConstIteratorHasNext
( const EventAttributeListConstIterator * );

EventAttributeListConstIterator *
NewEventAttributeListConstIterator
( const EventAttributeList *, int );

const EventAttribute *
NextInEventAttributeListConstIterator
( EventAttributeListConstIterator * );

#endif
