#ifndef __STUMPLESS_LIST_ITERATOR_HANDLER_H
#define __STUMPLESS_LIST_ITERATOR_HANDLER_H

#include <stumpless/type.h>

unsigned short
HandlerListIteratorHasNext
( const HandlerListIterator * );

HandlerListIterator *
CopyHandlerListIterator
( const HandlerListIterator * );

void
DestroyHandlerListIterator
( HandlerListIterator * );

HandlerListIterator *
NewHandlerListIterator
( HandlerList * );

Handler *
NextInHandlerListIterator
( HandlerListIterator * );

#endif
