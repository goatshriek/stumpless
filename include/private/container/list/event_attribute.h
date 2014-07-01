#ifndef __STUMPLESS_PRIVATE_LIST_EVENT_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_EVENT_ATTRIBUTE_H

#include "private/type.h"

EventAttributeList *
AddSeparatorToEventAttributeList
( EventAttributeList *, EventAttribute * );

EventAttributeList *
AppendEventAttributeLists
( EventAttributeList *, EventAttributeList * );

EventAttributeList *
AppendToEventAttributeList
( EventAttributeList *, EventAttribute * );

EventAttributeListIterator *
BeginEventAttributeList
( EventAttributeList * );

EventAttributeListConstIterator *
CBeginEventAttributeList
( const EventAttributeList * );

EventAttributeListConstIterator *
CEndEventAttributeList
( const EventAttributeList * );

EventAttributeList *
CopyEventAttributeList
( const EventAttributeList * );

EventAttributeListConstReverseIterator *
CRBeginEventAttributeList
( const EventAttributeList * );

EventAttributeListConstReverseIterator *
CREndEventAttributeList
( const EventAttributeList * );

void
DestroyEventAttributeList
( EventAttributeList * );

EventAttributeListIterator *
EndEventAttributeList
( EventAttributeList * );

EventAttribute *
EventAttributeListBack
( const EventAttributeList * );

unsigned short
EventAttributeListContains
( const EventAttributeList *, const EventAttribute * );

EventAttribute *
EventAttributeListFront
( const EventAttributeList * );

unsigned short
EventAttributeListIsEmpty
( const EventAttributeList * );

unsigned
EventAttributeListSize
( const EventAttributeList * );

EventAttributeList *
NewEventAttributeList
();

EventAttributeList *
PrependToEventAttributeList
( EventAttributeList *, EventAttribute * );

EventAttributeListReverseIterator *
RBeginEventAttributeList
( EventAttributeList * );

EventAttributeListReverseIterator *
REndEventAttributeList
( EventAttributeList * );

#endif
