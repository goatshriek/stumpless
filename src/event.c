#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <event.h>
#include <level.h>
#include <text_formatter.h>
#include <value_list.h>

char *
StumplessEventToString( StumplessEvent * event )
{
  StumplessFormattedOutput * output = StumplessEventAsText( event );
  
  if( event == NULL )
    return NULL;
  else
    return StumplessValueListToString( output->payload->values );
}

StumplessEvent *
StumplessGetDebugEvent( void )
{
  return StumplessEventForLevel( StumplessGetDebugLevel() );
}

StumplessEvent *
StumplessGetErrorEvent( void )
{
  return StumplessEventForLevel( StumplessGetErrorLevel() );
}

StumplessEvent *
StumplessEventForLevel( StumplessLevel * level )
{
  if( level == NULL )
    return NULL;
  
  
  StumplessEvent * event = malloc( sizeof( StumplessEvent ) );
  
  if( event == NULL )
    return NULL;
  
  event->name = NULL;
  event->level = level;
  event->attribute_count = 0;
  
  return event;
}

StumplessEvent *
StumplessGetFatalEvent( void )
{
  return StumplessEventForLevel( StumplessGetFatalLevel() );
}

StumplessEvent *
StumplessGetInfoEvent( void )
{
  return StumplessEventForLevel( StumplessGetInfoLevel() );
}

StumplessEvent *
StumplessGetWarningEvent( void )
{
  return StumplessEventForLevel( StumplessGetWarningLevel() );
}
