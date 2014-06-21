#ifndef __STUMPLESS_LIST_HANDLER_LIST_H
#define __STUMPLESS_LIST_HANDLER_LIST_H

#include <stdio.h>

#include <stumpless/type.h>

HandlerList *
AddSeparatorToHandlerList
( HandlerList *, Handler * );

HandlerList *
AppendHandlerLists
( HandlerList *, HandlerList * );

HandlerList *
AppendToHandlerList
( HandlerList *, Handler * );

HandlerList *
CopyHandlerList
( HandlerList * );

void
DestroyHandlerList
( HandlerList * );

unsigned short
HandlerListContains
( HandlerList *, Handler * );

unsigned short
HandlerListIsEmpty
( HandlerList * );

unsigned
HandlerListSize
( const HandlerList * );

HandlerList *
NewHandlerList
( void );

Status *
OutputThroughHandlerList
( HandlerList *, Output * );

HandlerList *
PrependToHandlerList
( HandlerList *, Handler * );

#endif
