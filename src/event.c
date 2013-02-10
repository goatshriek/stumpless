#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <event.h>
#include <level.h>

char *
StumplessEventToString( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  // todo need to add more customization to this method
  char * str;
  
  const char * name;
  if( event->name == NULL )
    name = "Event";
  else
    name = event->name;

  size_t name_length = strlen( name );
  
  char * level_string = StumplessLevelToString( event->level );
  size_t level_length = strlen( level_string );
  
  size_t str_length = name_length + level_length + 4;
  
  str = malloc( sizeof( char ) * str_length );
  if( str == NULL )
    return NULL;
  
  sprintf( str, "%s (%s)", name, level_string );
  
  return str;
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
