#include "stumpless/list/handler.h"

#include "private/list/handler.h"

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( AppendToHandlerList )
( __STUMPLESS_NAME( HandlerList ) * list, __STUMPLESS_NAME( Handler ) * handler )
{
  return AppendToHandlerList( list, handler );
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

unsigned short
__STUMPLESS_NAME( HandlerListIsEmpty )
( __STUMPLESS_NAME( HandlerList ) * list )
{
  return HandlerListIsEmpty( list );
}

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( NewHandlerList )
( void )
{
  return NewHandlerList();
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( OutputThroughHandlerList )
( __STUMPLESS_NAME( HandlerList ) * list, __STUMPLESS_NAME( Output ) * output )
{
  return OutputThroughHandlerList( list, output );
}

__STUMPLESS_NAME( HandlerList ) *
__STUMPLESS_NAME( PrependToHandlerList )
( __STUMPLESS_NAME( HandlerList ) * list, __STUMPLESS_NAME( Handler ) * handler )
{
  return PrependToHandlerList( list, handler );
}
