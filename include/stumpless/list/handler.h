#ifndef __STUMPLESS_LIST_HANDLER_LIST_H
#define __STUMPLESS_LIST_HANDLER_LIST_H

#include <stdio.h>

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( AddSeparatorToHandlerList )
( __STUMPLESS_NAME( HandlerList ) *, __STUMPLESS_NAME( Handler ) * );

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( AppendHandlerLists )
( __STUMPLESS_NAME( HandlerList ) *, __STUMPLESS_NAME( HandlerList ) * );

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( AppendToHandlerList )
( __STUMPLESS_NAME( HandlerList ) *, __STUMPLESS_NAME( Handler ) * );

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( CopyHandlerList )
( __STUMPLESS_NAME( HandlerList ) * );

void
__STUMPLESS_NAME( DestroyHandlerList )
( __STUMPLESS_NAME( HandlerList ) * );

unsigned short
__STUMPLESS_NAME( HandlerListContains )
( __STUMPLESS_NAME( HandlerList ) *, __STUMPLESS_NAME( Handler ) * );

unsigned short
__STUMPLESS_NAME( HandlerListIsEmpty )
( __STUMPLESS_NAME( HandlerList ) * );

unsigned
__STUMPLESS_NAME( HandlerListSize )
( const __STUMPLESS_NAME( HandlerList ) * );

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( NewHandlerList )
( void );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( OutputThroughHandlerList )
( __STUMPLESS_NAME( HandlerList ) *, __STUMPLESS_NAME( Output ) * );

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( PrependToHandlerList )
( __STUMPLESS_NAME( HandlerList ) *, __STUMPLESS_NAME( Handler ) * );

#endif
