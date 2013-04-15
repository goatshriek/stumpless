#include <stdlib.h>
#include <string.h>

#include <string_helper.h>

char *
copy_string( char * str )
{
  if( str == NULL )
    return NULL;
  
  size_t length = strlen( str );
  char * copy = malloc( sizeof( char ) * length + 1 );
  if( copy == NULL )
    return NULL;
  
  strncpy( copy, str, length );
  copy[length] = '\0';
  return copy;
}

unsigned short
is_empty( const char * str )
{
  if( str == NULL )
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
replace_char( const char * str, char target, char replacement )
{
  if( str == NULL )
    return NULL;
  
  size_t str_length = strlen( str );
  char * new_str = malloc( sizeof( char ) * str_length + 1 );
  if( new_str == NULL )
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
title_case( const char * str )
{
  if( str == NULL )
    return NULL;
  
  size_t str_length = strlen( str );
  char * new_str = malloc( sizeof( char ) * str_length + 1 );
  if( new_str == NULL )
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
