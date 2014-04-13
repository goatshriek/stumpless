#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_HANDLER_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_HANDLER_H

#include "private/type.h"

HandlerListConstIterator *
CopyHandlerListConstIterator
( const HandlerListConstIterator * );

void
DestroyHandlerListConstIterator
( HandlerListConstIterator * );

unsigned short
HandlerListConstIteratorHasNext
( const HandlerListConstIterator * );

HandlerListConstIterator *
NewHandlerListConstIterator
( const HandlerList *, int );

const Handler *
NextInHandlerListConstIterator
( HandlerListConstIterator * );

#endif
