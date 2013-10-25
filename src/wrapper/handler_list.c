#include <handler_list.h>

#include "private/handler_list.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToHandlerList )
( __STUMPLESS_NAME( HandlerList ) * list, __STUMPLESS_NAME( Handler ) * handler )
{
  return AppendToHandlerList( list, handler );
}

__STUMPLESS_NAME( Handler ) *
__STUMPLESS_NAME( BeginHandlerList )
( __STUMPLESS_NAME( HandlerList ) * list )
{
  return BeginHandlerList( list );
}

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( CopyHandlerList )
( __STUMPLESS_NAME( HandlerList ) * list )
{
  return CopyHandlerList( list );
}

void
__STUMPLESS_NAME( DestroyHandlerList )
( __STUMPLESS_NAME( HandlerList ) * list )
{
  DestroyHandlerList( list );
}

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( NewHandlerList )
( void )
{
  return NewHandlerList();
}

__STUMPLESS_NAME( Handler ) *
__STUMPLESS_NAME( NextInHandlerList )
( __STUMPLESS_NAME( HandlerList ) * list )
{
  return NextInHandlerList( list );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToHandlerList )
( __STUMPLESS_NAME( HandlerList ) * list, __STUMPLESS_NAME( Handler ) * handler )
{
  return PrependToHandlerList( list, handler );
}

unsigned short
__STUMPLESS_NAME( HandlerListIsEmpty )
( __STUMPLESS_NAME( HandlerList ) * list )
{
  return HandlerListIsEmpty( list );
}
