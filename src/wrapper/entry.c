#include "stumpless/entry.h"

#include "private/entry.h"

char *
__STUMPLESS_NAME( EntryToString )( __STUMPLESS_NAME( Entry ) * entry )
{
  return EntryToString( entry );
}

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( GetDebugEntry )( void )
{
  return GetDebugEntry();
}

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( EntryForEvent )( __STUMPLESS_NAME( Event ) * event )
{
  return EntryForEvent( event );
}

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( GetErrorEntry )( void )
{
  return GetErrorEntry();
}

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( GetFatalEntry )( void )
{
  return GetFatalEntry();
}

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( GetInfoEntry )( void )
{
  return GetInfoEntry();
}

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( GetWarningEntry )( void )
{
  return GetWarningEntry();
}
