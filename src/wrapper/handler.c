#include "stumpless/handler.h"

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

void *
__STUMPLESS_NAME( GetHandlerOption )
( const __STUMPLESS_NAME( Handler ) * handler, const char * option )
{
  return GetHandlerOption( handler, option );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetHandlerOption )
( __STUMPLESS_NAME( Handler ) * handler, const char * option, void * value )
{
  return SetHandlerOption( handler, option, value );
}
