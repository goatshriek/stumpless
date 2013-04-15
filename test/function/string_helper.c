#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "string_helper.h"

#include "helper.h"

const char * test_copy_string( void );
const char * test_is_empty( void );
const char * test_replace_char( void );
const char * test_title_case( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( copy_string )
  RUN_TEST( is_empty )
  RUN_TEST( replace_char )
  RUN_TEST( title_case )
  
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

const char *
test_replace_char( void )
{
  char * str = replace_char( "sucka_punch_you", '_', ' ' );
  if( str == NULL )
    return "could not build the new string";
  if( strcmp( str, "sucka punch you" ) != 0 )
    return "the target characters were not replaced";
  
  return NULL;
}

const char *
test_title_case( void )
{
  char * str = title_case( "i'm the original string" );
  if( str == NULL )
    return "could not build the new string";
  if( strcmp( str, "I'm The Original String" ) != 0 )
    return "the new string was not title-cased";
  
  return NULL;
}
