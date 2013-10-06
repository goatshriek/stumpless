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
  return FindStatusByName( name );
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

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( GetLastWarning )
( void )
{
  return GetLastWarning();
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( RaiseAbnormalStatus )
( const char * name )
{
  return RaiseAbnormalStatus( name );
}

const char *
__STUMPLESS_NAME( StatusToString )
( __STUMPLESS_NAME( Status ) * status )
{
  return StatusToString( status );
}
