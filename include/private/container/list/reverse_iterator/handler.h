#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_HANDLER_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_HANDLER_H

#include "private/type.h"

HandlerListReverseIterator *
CopyHandlerListReverseIterator
( const HandlerListReverseIterator * );

void
DestroyHandlerListReverseIterator
( HandlerListReverseIterator * );

unsigned short
HandlerListReverseIteratorHasNext
( const HandlerListReverseIterator * );

HandlerListReverseIterator *
NewHandlerListReverseIterator
( HandlerList *, int );

Handler *
NextInHandlerListReverseIterator
( HandlerListReverseIterator * );

#endif
