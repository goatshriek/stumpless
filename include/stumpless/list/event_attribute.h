#ifndef __STUMPLESS_LIST_EVENT_ATTRIBUTE_LIST_H
#define __STUMPLESS_LIST_EVENT_ATTRIBUTE_LIST_H

#include <stumpless/type.h>

EventAttributeList *
AddSeparatorToEventAttributeList
( EventAttributeList *, EventAttribute * );

EventAttributeList *
AppendEventAttributeLists
( EventAttributeList *, EventAttributeList * );

EventAttributeList *
AppendToEventAttributeList
( EventAttributeList *, EventAttribute * );

EventAttributeList *
CopyEventAttributeList
( EventAttributeList * );

void
DestroyEventAttributeList
( EventAttributeList * );

unsigned short
EventAttributeListContains
( EventAttributeList *, EventAttribute * );

unsigned short
EventAttributeListIsEmpty
( EventAttributeList * );

unsigned
EventAttributeListSize
( const EventAttributeList * );

EventAttributeList *
NewEventAttributeList
( void );

EventAttributeList *
PrependToEventAttributeList
( EventAttributeList *, EventAttribute * );

#endif
