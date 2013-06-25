#include <entry.h>

#include "private/entry.h"

char *
__NAME( EntryToString )( __NAME( Entry ) * entry )
{
  return EntryToString( entry );
}

__NAME( Entry ) *
__NAME( GetDebugEntry )( void )
{
  return GetDebugEntry();
}

__NAME( Entry ) *
__NAME( EntryForEvent )( __NAME( Event ) * event )
{
  return EntryForEvent( event );
}

__NAME( Entry ) *
__NAME( GetErrorEntry )( void )
{
  return GetErrorEntry();
}

__NAME( Entry ) *
__NAME( GetFatalEntry )( void )
{
  return GetFatalEntry();
}

__NAME( Entry ) *
__NAME( GetInfoEntry )( void )
{
  return GetInfoEntry();
}

__NAME( Entry ) *
__NAME( GetWarningEntry )( void )
{
  return GetWarningEntry();
}
