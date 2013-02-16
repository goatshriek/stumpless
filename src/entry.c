#include <stdlib.h>

#include <entry.h>
#include <event.h>
#include <text_formatter.h>
#include <types.h>

char *
StumplessEntryToString( StumplessEntry * entry )
{
  StumplessFormattedOutput * output =  StumplessEntryAsText( entry );
  
  if( output == NULL )
    return NULL;
  
  return output->payload->str;
}

StumplessEntry *
StumplessGetDebugEntry( void )
{
  return StumplessEntryForEvent( StumplessGetDebugEvent() );
}

StumplessEntry *
StumplessEntryForEvent( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  StumplessEntry * entry = malloc( sizeof( StumplessEntry ) );
  
  if( entry == NULL )
    return NULL;
  
  entry->event = event;
  
  return entry;
}

StumplessEntry *
StumplessGetErrorEntry( void )
{
  return StumplessEntryForEvent( StumplessGetErrorEvent() );
}

StumplessEntry *
StumplessGetFatalEntry( void )
{
  return StumplessEntryForEvent( StumplessGetFatalEvent() );
}

StumplessEntry *
StumplessGetInfoEntry( void )
{
  return StumplessEntryForEvent( StumplessGetInfoEvent() );
}

StumplessEntry *
StumplessGetWarningEntry( void )
{
  return StumplessEntryForEvent( StumplessGetWarningEvent() );
}
