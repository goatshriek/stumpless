#ifndef STUMPLESS_PRIVATE_EVENT_ATTRIBUTE_LIST_H
#define STUMPLESS_PRIVATE_EVENT_ATTRIBUTE_LIST_H

#include "private/type.h"

Status *
AppendToEventAttributeList
( EventAttributeList *, EventAttribute * );

EventAttribute *
BeginEventAttributeList
( EventAttributeList * );

EventAttributeList *
CopyEventAttributeList
( EventAttributeList * );

void
DestroyEventAttributeList
( EventAttributeList * );

unsigned short
EventAttributeListIsEmpty
( EventAttributeList * );

EventAttributeList *
NewEventAttributeList
( void );

EventAttribute *
NextInEventAttributeList
( EventAttributeList * );

Status *
PrependToEventAttributeList
( EventAttributeList *, EventAttribute * );

#endif
