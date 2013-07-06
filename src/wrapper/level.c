#include <level.h>

#include "private/level.h"

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetAlertLevel )( void )
{
  return GetAlertLevel();
}

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetCriticalLevel )( void )
{
  return GetCriticalLevel();
}

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetDebugLevel )
( void )
{
  return GetDebugLevel();
}

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetEmergencyLevel )( void )
{
  return GetEmergencyLevel();
}

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetErrorLevel )( void )
{
  return GetErrorLevel();
}

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetFatalLevel )( void )
{
  return GetFatalLevel();
}

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetInfoLevel )( void )
{
  return GetInfoLevel();
}

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetNoticeLevel )( void )
{
  return GetNoticeLevel();
}

__STUMPLESS_NAME( Level ) *
__STUMPLESS_NAME( GetWarningLevel )( void )
{
  return GetWarningLevel();
}

char *
__STUMPLESS_NAME( LevelToString )
( __STUMPLESS_NAME( Level ) * level )
{
  return LevelToString( level) ;
}
