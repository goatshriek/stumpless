#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private/string_helper.h"

#include "test/helper.h"

const char * test_copy_string( void );
const char * test_is_empty( void );
const char * test_replace_char( void );
const char * test_replace_first( void );
const char * test_replace_string( void );
const char * test_title_case( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( copy_string )
  RUN_TEST( is_empty )
  RUN_TEST( replace_char )
  RUN_TEST( replace_first )
  RUN_TEST( replace_string )
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
test_replace_char
( void )
{
  char *str = replace_char( "sucka_punch_you", '_', ' ' );
  if( !str )
    return "could not build the new string";
  if( strcmp( str, "sucka punch you" ) != 0 )
    return "the target characters were not replaced";
  
  return NULL;
}

const char *
test_replace_first
( void )
{
  char str[100];
  strcpy( str, "How could this happen to me?" );
  replace_first_string( str, "this", "this actually" );
  ASSERT_STRINGS_EQUAL( str, "How could this actually happen to me?", "a single replacement was not handled properly" );

  strcpy( str, "How could this happen to me?" );
  replace_first_string( str, "me?", "me!" );
  ASSERT_STRINGS_EQUAL( str, "How could this happen to me!", "a replacement at the end was not handled properly" );

  strcpy( str, "How could this happen to me?" );
  replace_first_string( str, "How could", "Did" );
  ASSERT_STRINGS_EQUAL( str, "Did this happen to me?", "a replacement at the beginning was not handled properly" );
  
  strcpy( str, "How could this happen to me? I think this is unacceptable." );
  replace_first_string( str, "this", "that" );
  ASSERT_STRINGS_EQUAL( str, "How could that happen to me? I think this is unacceptable.", "two replacements were not handled properly" )

  return NULL;
}

const char *
test_replace_string
( void )
{
  char str[100];
  strcpy( str, "How could this happen to me?" );
  replace_string( str, "this", "this actually" );
  ASSERT_STRINGS_EQUAL( str, "How could this actually happen to me?", "a single replacement was not handled properly" );

  strcpy( str, "How could this happen to me?" );
  replace_string( str, "me?", "me!" );
  ASSERT_STRINGS_EQUAL( str, "How could this happen to me!", "a replacement at the end was not handled properly" );

  strcpy( str, "How could this happen to me?" );
  replace_string( str, "How could", "Did" );
  ASSERT_STRINGS_EQUAL( str, "Did this happen to me?", "a replacement at the beginning was not handled properly" );
  
  strcpy( str, "How could this happen to me? I think this is unacceptable." );
  replace_string( str, "this", "that" );
  ASSERT_STRINGS_EQUAL( str, "How could that happen to me? I think that is unacceptable.", "two replacements were not handled properly" )

  return NULL;
}

const char *
test_title_case( void )
{
  char * str = get_title_case( "i'm the original string" );
  if( !str )
    return "could not build the new string";
  if( strcmp( str, "I'm The Original String" ) != 0 )
    return "the new string was not title-cased";
  
  return NULL;
}
