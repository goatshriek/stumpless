#include <logger.h>

#include "private/logger.h"

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LogDebug )
( const char * message )
{
  return LogDebug( message );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LogError )
( const char * message )
{
  return LogError( message );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LogFatal )
( const char * message )
{
  return LogFatal( message );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LogInfo )
( const char * message )
{
  return LogInfo( message );
}

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( LogWarning )
( const char * message )
{
  return LogWarning( message );
}
