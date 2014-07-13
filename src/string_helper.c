#include <stdlib.h>
#include <string.h>

#include "private/string_helper.h"

char *
copy_string
( const char *str )
{
  if( !str )
    return NULL;
  
  size_t length = strlen( str );
  char *copy = malloc( sizeof( char ) * length + 1 );
  if( !copy )
    return NULL;
  
  strncpy( copy, str, length );
  copy[length] = '\0';
  return copy;
}

char *
get_title_case
( const char *str )
{
  if( !str )
    return NULL;
  
  size_t str_length = strlen( str );
  char *new_str = malloc( sizeof( char ) * str_length + 1 );
  if( !new_str )
    return NULL;
  
  unsigned i;
  char current;
  char previous = str[0];
  new_str[0] = toupper( str[0] );
  for( i = 1; i < str_length; i++ ){
    current = str[i];
    
    if( isspace( previous ) )
      new_str[i] = toupper( current );
    else
      new_str[i] = current;
    
    previous = current;
  }
  
  new_str[str_length] = '\0';
  
  return new_str;
}

unsigned short
is_empty
( const char *str )
{
  if( !str )
    return 1;
  
  unsigned index = 0;
  char next = str[0];
  
  while( str[index] != '\0' ){
    if( !isspace( str[index] ) )
      return 0;
    
    index++;
  }
  
  return index;
}

char *
replace_char
( const char *str, const char target, char replacement )
{
  if( !str )
    return NULL;
  
  size_t str_length = strlen( str );
  char *new_str = malloc( sizeof( char ) * str_length + 1 );
  if( !new_str )
    return NULL;
  
  unsigned i;
  char current;
  for( i = 0; i < str_length; i++ ){
    current = str[i];
    if( current == target )
      new_str[i] = replacement;
    else
      new_str[i] = current;
  }
  
  new_str[str_length] = '\0';
  
  return new_str;
}

char *
replace_first_string
( char *string, const char *target, const char *replacement )
{
  if( !string )
    return NULL;
  
  size_t target_length = strlen( target );
  size_t replacement_length = strlen( replacement );
  
  char *buffer = malloc( sizeof( char ) * ( strlen( string ) + 1 ) );
  if( !buffer )
    return NULL;
  strcpy( buffer, string );

  char *location = strstr( buffer, target );
  if( !location ){
    free( buffer );
    return string;
  }

  size_t span_length = location - buffer;
  strncpy( string, buffer, span_length );
  char *string_placeholder = string + span_length;
  strncpy( string_placeholder, replacement, replacement_length );
  strcpy( string_placeholder + replacement_length, location + target_length );
  
  free( buffer );

  return string;
}

char *
replace_string
( char *string, const char *target, const char *replacement )
{
  if( !string )
    return NULL;
  
  size_t target_length = strlen( target );
  size_t replacement_length = strlen( replacement );
  
  char *buffer = malloc( sizeof( char ) * ( strlen( string ) + 1 ) );
  if( !buffer )
    return NULL;
  strcpy( buffer, string );
  
  char *string_placeholder = string;
  char *buffer_placeholder = buffer;
  char *location;
  size_t span_length;
  while( location = strstr( buffer_placeholder, target ) ){
    span_length = location - buffer_placeholder;
    strncpy( string_placeholder, buffer_placeholder, span_length );
    string_placeholder += span_length;
    strncpy( string_placeholder, replacement, replacement_length );
    string_placeholder += replacement_length;
    buffer_placeholder = location + target_length;
  }
  
  strcpy( string_placeholder, buffer_placeholder );
  free( buffer );

  return string;
}
