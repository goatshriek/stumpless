#include <configuration.h>

#include "private/configuration.h"

__NAME( StatusCode )
__NAME( AddLoggingProfile )( __NAME( LoggingProfile ) * profile )
{
  return AddLoggingProfile( profile );
}

__NAME( StatusCode )
__NAME( AddOutputProfile )( __NAME( OutputProfile ) * profile )
{
  return AddOutputProfile( profile );
}

__NAME( StatusCode )
__NAME( AddValueProfile )( __NAME( ValueProfile ) * profile )
{
  return AddValueProfile( profile );
}

__NAME( LoggingProfile ) *
__NAME( FindLoggingProfileByName )( const char * name )
{
  return FindLoggingProfileByName( name );
}

__NAME( OutputProfile ) *
__NAME( FindOutputProfileByName )( const char * name )
{
  return FindOutputProfileByName( name );
}

__NAME( ValueProfile ) *
__NAME( FindValueProfileByName )( const char * name )
{
  return FindValueProfileByName( name );
}

__NAME( Configuration ) *
__NAME( GetConfiguration )( void )
{
  return GetConfiguration();
}

__NAME( StatusCode )
__NAME( InitializeConfiguration )( void )
{
  return InitializeConfiguration();
}

__NAME( StatusCode )
__NAME( InitializeLoggingProfiles )( void )
{
  return InitializeLoggingProfiles();
}

__NAME( StatusCode )
__NAME( InitializeOutputProfiles )( void )
{
  return InitializeOutputProfiles();
}

__NAME( StatusCode )
__NAME( InitializeValueProfiles )( void )
{
  return InitializeValueProfiles();
}

__NAME( StatusCode )
__NAME( SetConfiguration )( __NAME( Configuration ) * configuration )
{
  return SetConfiguration( configuration );
}
