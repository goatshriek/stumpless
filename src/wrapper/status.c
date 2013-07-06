#include <status.h>

#include "private/status.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddStatus )
( __STUMPLESS_NAME( Status ) * status )
{
  return AddStatus( status );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( FindStatusByName )
( const char * name )
{
  return FindStatusbyName( name );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( InitializeStatus )
( void )
{
  return InitializeStatus();
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( GetLastError )
( void )
{
  return GetLastError();
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( GetLastFailure )
( void )
{
  return GetLastFailure();
}

// todo remove
const char *
__STUMPLESS_NAME( StatusToString )
( __STUMPLESS_NAME( StatusCode ) status_code )
{
  return StatusToString( status_code );
}
