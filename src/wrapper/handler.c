#include <handler.h>

#include "private/handler.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddHandler )
( __STUMPLESS_NAME( Handler ) * handler )
{
  return AddHandler( handler );
}

__STUMPLESS_NAME( Handler ) *
__STUMPLESS_NAME( FindHandlerByName )
( const char * name )
{
  return FindHandlerByName( name );
}
