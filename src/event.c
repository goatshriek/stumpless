#include <event.h>
#include <level.h>

char *
StumplessEventToString( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  return NULL;
}

StumplessEvent *
StumplessGetDebugEvent( void )
{
  return StumplessGetEventForLevel( StumplessGetDebugLevel() );
}

StumplessEvent *
StumplessGetErrorEvent( void )
{
  return StumplessGetEventForLevel( StumplessGetErrorLevel() );
}

StumplessEvent *
StumplessGetEventForLevel( StumplessLevel * level )
{
  StumplessEvent * event = malloc( sizeof( StumplessEvent ) );
  
  if( level == NULL || event == NULL )
    return NULL;
  
  event->name = NULL;
  event->level = level;
  event->attribute_count = 0;
  
  return event;
}

StumplessEvent *
StumplessGetFatalEvent( void )
{
  return StumplessGetEventForLevel( StumplessGetFatalLevel() );
}

StumplessEvent *
StumplessGetInfoEvent( void )
{
  return StumplessGetEventForLevel( StumplessGetInfoLevel() );
}

StumplessEvent *
StumplessGetWarningEvent( void )
{
  return StumplessGetEventForLevel( StumplessGetWarningLevel() );
}
