#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_helper.h"

#include "helper.h"

const char * test_copy_string( void );
const char * test_is_empty( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( test_copy_string, "Copy String Test Failed: %s\n" )
  RUN_TEST( test_is_empty, "Is Empty Test Failed: %s\n" )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_copy_string( void )
{
  char * copy = copy_string( NULL );
  if( copy != NULL )
    return "a null string did not have a null copy";
  
  char * original = "unique of course";
  copy = copy_string( original );
  if( copy == NULL )
    return "the copy was null for a non-null string";
  if( copy == original )
    return "the copy was not actually a copy";
  if( strcmp( copy, original ) != 0 )
    return "the copied strings were not equivalent";
  
  return NULL;
}

const char *
test_is_empty( void )
{
  unsigned short result = is_empty( " \f\n\r\t\v" );

  if( !is_empty( NULL ) )
    return "a NULL pointer was not empty";
  
  if( result == 0 )
    return "a string of all whitespace caharcters was not empty";
  
  if( result != 6 )
    return "the result of the call was not the length of the string";
  
  if( is_empty( "this string is definitely not empty" ) )
    return "a non-empty string was designated as empty";
  
  return NULL;
}
