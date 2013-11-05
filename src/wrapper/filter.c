#include <filter.h>

#include "private/filter.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddFilter )
( __STUMPLESS_NAME( Filter ) * filter )
{
  return AddFilter( filter );
}

__STUMPLESS_NAME( Filter ) *
__STUMPLESS_NAME( FindFilterByName )
( const char * name )
{
  return FindFilterByName( name );
}

void *
__STUMPLESS_NAME( GetFilterOption )
( const __STUMPLESS_NAME( Filter ) * filter, const char * option )
{
  return GetFilterOption( filter, option );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetFilterOption )
( __STUMPLESS_NAME( Filter ) * filter, const char * option, void * value )
{
  return SetFilterOption( filter, option, value );
}
