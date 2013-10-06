#include <configuration.h>

#include "private/configuration.h"

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( AddLoggingProfile )
( __STUMPLESS_NAME( LoggingProfile ) * profile )
{
  return AddLoggingProfile( profile );
}

__STUMPLESS_NAME( LoggingProfile ) *
__STUMPLESS_NAME( FindLoggingProfileByName )( const char * name )
{
  return FindLoggingProfileByName( name );
}

__STUMPLESS_NAME( Configuration ) *
__STUMPLESS_NAME( GetConfiguration )( void )
{
  return GetConfiguration();
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( InitializeConfiguration )( void )
{
  return InitializeConfiguration();
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( InitializeLoggingProfiles )( void )
{
  return InitializeLoggingProfiles();
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetConfiguration )
( __STUMPLESS_NAME( Configuration ) * configuration )
{
  return SetConfiguration( configuration );
}
