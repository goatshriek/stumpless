#include <event.h>

#include "private/event.h"

char *
__STUMPLESS_NAME( EventToString)
( __STUMPLESS_NAME( Event ) * event )
{
  return EventToString( event );
}

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( GetDebugEvent )
( void )
{
  return GetDebugEvent();
}

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( GetErrorEvent )
( void )
{
  return GetErrorEvent();
}

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( EventForLevel )
( __STUMPLESS_NAME( Level ) * level )
{
  return EventForLevel( level );
}

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( GetFatalEvent )
( void )
{
  return GetFatalEvent();
}

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( GetInfoEvent )
( void )
{
  return GetInfoEvent();
}

__STUMPLESS_NAME( Event ) *
__STUMPLESS_NAME( GetWarningEvent )
( void )
{
  return GetWarningEvent();
}
