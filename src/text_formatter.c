#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <text_formatter.h>

char *
StumplessEntryAsText( StumplessEntry * entry )
{
  if( entry == NULL )
    return NULL;
  
  // todo need to make this method encompass more possible cases
  return NULL;
}

char *
StumplessEventAsText( StumplessEvent * event )
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
  
  char * level_string = StumplessLevelAsText( event->level );
  size_t level_length = strlen( level_string );
  
  size_t str_length = name_length + level_length + 4;
  
  str = malloc( sizeof( char ) * str_length );
  if( str == NULL )
    return NULL;
  
  sprintf( str, "%s (%s)", name, level_string );
  
  return str;
}

char *
StumplessLevelAsText( StumplessLevel * level )
{
  if( level == NULL )
    return NULL;
 
  char * str;
   
  // todo may be able to save memory by calculating a
  //      more exact size of this string
  size_t number_length = 10;
  
  // todo need to check for empty strings as well
  
  if( level->name == NULL ){
    size_t str_length = number_length + 7;
    str = malloc( sizeof( char ) * str_length );
    if( str == NULL )
      return NULL;

    sprintf( str, "level %d", level->value);
  } else {
    size_t name_length = strlen( level->name );
    size_t str_length = number_length + name_length + 9;
    str = malloc( sizeof( char ) * str_length );
    if( str == NULL )
      return NULL;

    sprintf( str, "%s: level %d", level->name, level->value );
  }
  
  return str;
}
