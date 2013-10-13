#include <logger_profile.h>

#include "private/logger_profile.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddLoggerProfile )
( __STUMPLESS_NAME( LoggerProfile ) * profile )
{
  return AddLoggerProfile( profile );
}

__STUMPLESS_NAME( LoggerProfile ) *
__STUMPLESS_NAME( FindLoggerProfileByName )
( const char * name )
{
  return FindLoggerProfileByName( name );
}
