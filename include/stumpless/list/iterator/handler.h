#ifndef __STUMPLESS_LIST_ITERATOR_HANDLER_H
#define __STUMPLESS_LIST_ITERATOR_HANDLER_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

unsigned short
__STUMPLESS_NAME( HandlerListIteratorHasNext )
( const __STUMPLESS_NAME( HandlerListIterator ) * );

__STUMPLESS_NAME( HandlerListIterator ) *
__STUMPLESS_NAME( CopyHandlerListIterator )
( const __STUMPLESS_NAME( HandlerListIterator ) * );

void
__STUMPLESS_NAME( DestroyHandlerListIterator )
( __STUMPLESS_NAME( HandlerListIterator ) * );

__STUMPLESS_NAME( HandlerListIterator ) *
__STUMPLESS_NAME( NewHandlerListIterator )
( __STUMPLESS_NAME( HandlerList ) * );

__STUMPLESS_NAME( Handler ) *
__STUMPLESS_NAME( NextInHandlerListIterator )
( __STUMPLESS_NAME( HandlerListIterator ) * );

#endif
