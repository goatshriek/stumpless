#ifndef STUMPLESS_PRIVATE_HANDLER_LIST_H
#define STUMPLESS_PRIVATE_HANDLER_LIST_H

#include <stdio.h>

#include "private/type.h"

Status *
AppendToHandlerList
( HandlerList *, Handler * );

Handler *
BeginHandlerList
( HandlerList * );

HandlerList *
CopyHandlerList
( HandlerList * );

void
DestroyHandlerList
( HandlerList * );

unsigned short
HandlerListIsEmpty
( HandlerList * );

HandlerList *
NewHandlerList
( void );

Handler *
NextInHandlerList
( HandlerList * );

Status *
OutputThroughHandlerList
( HandlerList *, Output * );

Status *
PrependToHandlerList
( HandlerList *, Handler * );

#endif
