#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_HANDLER_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_HANDLER_H

#include "private/type.h"

HandlerListIterator *
CopyHandlerListIterator
( const HandlerListIterator * );

void
DestroyHandlerListIterator
( HandlerListIterator * );

unsigned short
HandlerListIteratorHasNext
( const HandlerListIterator * );

HandlerListIterator *
NewHandlerListIterator
( HandlerList *, int );

Handler *
NextInHandlerListIterator
( HandlerListIterator * );

#endif
