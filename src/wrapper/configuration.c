#include <configuration.h>

#include "private/configuration.h"

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( AddLoggingProfile )
( __STUMPLESS_NAME( LoggingProfile ) * profile )
{
  return AddLoggingProfile( profile );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( AddOutputProfile )
( __STUMPLESS_NAME( OutputProfile ) * profile )
{
  return AddOutputProfile( profile );
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( AddValueProfile )
( __STUMPLESS_NAME( ValueProfile ) * profile )
{
  return AddValueProfile( profile );
}

__STUMPLESS_NAME( LoggingProfile ) *
__STUMPLESS_NAME( FindLoggingProfileByName )( const char * name )
{
  return FindLoggingProfileByName( name );
}

__STUMPLESS_NAME( OutputProfile ) *
__STUMPLESS_NAME( FindOutputProfileByName )( const char * name )
{
  return FindOutputProfileByName( name );
}

__STUMPLESS_NAME( ValueProfile ) *
__STUMPLESS_NAME( FindValueProfileByName )( const char * name )
{
  return FindValueProfileByName( name );
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

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( InitializeOutputProfiles )( void )
{
  return InitializeOutputProfiles();
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( InitializeValueProfiles )( void )
{
  return InitializeValueProfiles();
}

__STUMPLESS_NAME( StatusCode )
__STUMPLESS_NAME( SetConfiguration )
( __STUMPLESS_NAME( Configuration ) * configuration )
{
  return SetConfiguration( configuration );
}
