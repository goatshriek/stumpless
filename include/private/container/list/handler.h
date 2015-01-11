#ifndef __STUMPLESS_PRIVATE_LIST_HANDLER_H
#define __STUMPLESS_PRIVATE_LIST_HANDLER_H

#include <stdio.h>

#include "private/type.h"

HandlerList *
AddSeparatorToHandlerList
( HandlerList *, Handler * );

HandlerList *
AppendHandlerLists
( HandlerList *, HandlerList * );

HandlerList *
AppendToHandlerList
( HandlerList *, Handler * );

HandlerListIterator *
BeginHandlerList
( HandlerList * );

HandlerListConstIterator *
CBeginHandlerList
( const HandlerList * );

HandlerListConstIterator *
CEndHandlerList
( const HandlerList * );

HandlerList *
CopyHandlerList
( const HandlerList * );

HandlerListConstReverseIterator *
CRBeginHandlerList
( const HandlerList * );

HandlerListConstReverseIterator *
CREndHandlerList
( const HandlerList * );

void
DestroyHandlerList
( HandlerList * );

HandlerListIterator *
EndHandlerList
( HandlerList * );

Handler *
HandlerListBack
( const HandlerList * );

unsigned short
HandlerListContains
( const HandlerList *, const Handler * );

Handler *
HandlerListFront
( const HandlerList * );

unsigned short
HandlerListIsEmpty
( const HandlerList * );

unsigned
HandlerListSize
( const HandlerList * );

HandlerList *
NewHandlerList
();

Exception *
OutputThroughHandlerList
( const HandlerList *, const Output * );

HandlerList *
PrependToHandlerList
( HandlerList *, Handler * );

HandlerListReverseIterator *
RBeginHandlerList
( HandlerList * );

HandlerListReverseIterator *
REndHandlerList
( HandlerList * );

#endif
