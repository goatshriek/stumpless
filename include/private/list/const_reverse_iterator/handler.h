#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_HANDLER_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_HANDLER_H

#include "private/type.h"

HandlerListConstReverseIterator *
CopyHandlerListConstReverseIterator
( const HandlerListConstReverseIterator * );

void
DestroyHandlerListConstReverseIterator
( HandlerListConstReverseIterator * );

unsigned short
HandlerListConstReverseIteratorHasNext
( const HandlerListConstReverseIterator * );

HandlerListConstReverseIterator *
NewHandlerListConstReverseIterator
( const HandlerList *, int );

const Handler *
NextInHandlerListConstReverseIterator
( HandlerListConstReverseIterator * );

#endif
