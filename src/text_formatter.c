#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <text_formatter.h>

static
StumplessFormattedOutput *
GetTextFormattedOutput( void ){
  StumplessFormattedOutput * output;
  StumplessFormattedPayload * payload;

  output = malloc( sizeof( StumplessFormattedOutput ) );
  if( output == NULL )
    return NULL;
  
  payload = malloc( sizeof( StumplessFormattedPayload ) );
  if( payload == NULL )
    return NULL;
  
  output->format = STUMPLESS_TEXT;
  output->payload = payload;
  
  return output;
}

StumplessFormattedOutput *
StumplessEntryAsText( StumplessEntry * entry )
{
  if( entry == NULL )
    return NULL;
  
  // todo need to make this method encompass more possible cases
  return NULL;
}

StumplessFormattedOutput *
StumplessEventAsText( StumplessEvent * event )
{
  if( event == NULL )
    return NULL;
  
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
   
  char * str;
  
  if( event->name == NULL ){
    if( event->level == NULL ){
      if( event->attribute_count == 0 ){
        str = "";
      } else {
        // todo
      }
    } else {

    }
  } else {
    if( event->level == NULL ){
      if( event->attribute_count == 0 ){

      } else {

      }
    } else {

    }
    
  }
  
  output->payload->str = str;
  
  return output;
}

StumplessFormattedOutput *
StumplessLevelAsText( StumplessLevel * level )
{
  if( level == NULL )
    return NULL;
 
  StumplessFormattedOutput * output = GetTextFormattedOutput();
  if( output == NULL )
    return NULL;
  
  char * str;
   
  // todo may be able to save memory by calculating a
  //      more exact size of this string
  size_t number_length = 10;
  
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
  
  output->payload->str = str;
  
  return output;
}
