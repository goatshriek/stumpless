#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include <stumpless/config/check.h>

#include "private/string_helper.h"

char *
copy_string
( const char *str )
{
  char *copy;
  size_t length;

  if( !str )
    return NULL;

  length = strlen( str );
  copy = malloc( sizeof( char ) * length + 1 );
  if( !copy )
    return NULL;

#ifdef __STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS
  strncpy_s( copy, length, str, length );
#else
  strncpy( copy, str, length );
#endif

  copy[length] = '\0';
  return copy;
}

char *
get_title_case
( const char *str )
{
  char current, *new_str, previous;
  size_t str_length;
  unsigned i;

  if( !str )
    return NULL;

  str_length = strlen( str );
  new_str = malloc( sizeof( char ) * str_length + 1 );
  if( !new_str )
    return NULL;

  previous = str[0];
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
  char next;
  unsigned index = 0;

  if( !str )
    return 1;

  next = str[0];

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
  char current, *new_str;
  size_t str_length;
  unsigned i;

  if( !str )
    return NULL;

  str_length = strlen( str );
  new_str = malloc( sizeof( char ) * str_length + 1 );
  if( !new_str )
    return NULL;

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
  char *buffer, *location, *string_placeholder;
  size_t span_length, string_length, replacement_length, target_length;

  if( !string )
    return NULL;

  target_length = strlen( target );
  replacement_length = strlen( replacement );
  string_length = strlen( string );

  buffer = malloc( sizeof( char ) * ( string_length + 1 ) );
  if( !buffer )
    return NULL;

#ifdef __STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS
  strncpy_s( buffer, string_length, string, string_length );
#else
  strncpy( buffer, string, string_length );
#endif

  location = strstr( buffer, target );
  if( !location ){
    free( buffer );
    return string;
  }

  span_length = location - buffer;
#ifdef __STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS
  strncpy_s( string, span_length, buffer, span_length );
#else
  strncpy( string, buffer, span_length );
#endif
  string_placeholder = string + span_length;
#ifdef __STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS
  strncpy_s( string_placeholder, replacement_length, replacement, replacement_length );
  strncpy_s( string_placeholder + replacement_length, string_length - span_length, location + target_length, string_length - span_length );
#else
  strncpy( string_placeholder, replacement, replacement_length );
  strncpy( string_placeholder + replacement_length, location + target_length, string_length - span_length );
#endif

  free( buffer );

  return string;
}

char *
replace_string
( char *string, const char *target, const char *replacement )
{
  char *buffer, *buffer_placeholder, *location, *string_placeholder;
  size_t replacement_length, string_length, span_length, target_length;

  if( !string )
    return NULL;

  target_length = strlen( target );
  replacement_length = strlen( replacement );
  string_length = strlen( string );

  buffer = malloc( sizeof( char ) * ( string_length + 1 ) );
  if( !buffer )
    return NULL;

#ifdef __STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS
  strncpy_s( buffer, string_length, string, string_length );
#else
  strncpy( buffer, string, string_length );
#endif

  string_placeholder = string;
  buffer_placeholder = buffer;
  while( location = strstr( buffer_placeholder, target ) ){
    span_length = location - buffer_placeholder;
#ifdef __STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS
    strncpy_s( string_placeholder, span_length, buffer_placeholder, span_length );
#else
    strncpy( string_placeholder, buffer_placeholder, span_length );
#endif
    string_placeholder += span_length;
#ifdef __STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS
    strncpy_s( string_placeholder, replacement_length, replacement, replacement_length );
#else
    strncpy( string_placeholder, replacement, replacement_length );
#endif
    string_placeholder += replacement_length;
    buffer_placeholder = location + target_length;
  }

#ifdef __STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS
  strncpy_s( string_placeholder, string + string_length - string_placeholder, buffer_placeholder, string + string_length - string_placeholder );
#else
  strncpy( string_placeholder, buffer_placeholder, string + string_length - string_placeholder );
#endif
  free( buffer );

  return string;
}
