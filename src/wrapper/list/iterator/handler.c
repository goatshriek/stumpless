#include "stumpless/list/iterator/handler.h"

#include "private/list/iterator/handler.h"

unsigned short
__STUMPLESS_NAME( HandlerListIteratorHasNext )
( const __STUMPLESS_NAME( HandlerListIterator ) * iterator )
{
  return HandlerListIteratorHasNext( iterator );
}

__STUMPLESS_NAME( HandlerListIterator ) *
__STUMPLESS_NAME( CopyHandlerListIterator )
( const __STUMPLESS_NAME( HandlerListIterator ) * iterator )
{
  return CopyHandlerListIterator( iterator );
}

void
__STUMPLESS_NAME( DestroyHandlerListIterator )
( __STUMPLESS_NAME( HandlerListIterator ) * iterator )
{
  DestroyHandlerListIterator( iterator );
  return;
}

__STUMPLESS_NAME( HandlerListIterator ) *
__STUMPLESS_NAME( NewHandlerListIterator )
( __STUMPLESS_NAME( HandlerList ) * list )
{
  return NewHandlerListIterator( list );
}

__STUMPLESS_NAME( Handler ) *
__STUMPLESS_NAME( NextInHandlerListIterator )
( __STUMPLESS_NAME( HandlerListIterator ) * iterator )
{
  return NextInHandlerListIterator( iterator );
}
