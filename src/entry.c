#include <stdlib.h>

#include <entry.h>
#include <event.h>
#include <formatted_output.h>
#include <text_formatter.h>
#include <type.h>
#include <value_list.h>

char *
StumplessEntryToString( StumplessEntry * entry )
{
  StumplessFormattedOutput * output =  StumplessEntryToText( entry );
  return StumplessFormattedOutputToString( output ); 
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
