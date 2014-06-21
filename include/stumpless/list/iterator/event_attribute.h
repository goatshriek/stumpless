#ifndef __STUMPLESS_LIST_ITERATOR_EVENT_ATTRIBUTE_H
#define __STUMPLESS_LIST_ITERATOR_EVENT_ATTRIBUTE_H

#include <stumpless/type.h>

unsigned short
EventAttributeListIteratorHasNext
( const EventAttributeListIterator * );

EventAttributeListIterator *
CopyEventAttributeListIterator
( const EventAttributeListIterator * );

void
DestroyEventAttributeListIterator
( EventAttributeListIterator * );

EventAttributeListIterator *
NewEventAttributeListIterator
( EventAttributeList * );

EventAttribute *
NextInEventAttributeListIterator
( EventAttributeListIterator * );

#endif
