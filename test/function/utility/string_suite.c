#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private/utility/string.h"

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
  char *copy;
  const char *original = "unique of course";

  copy = copy_string( NULL );
  if( copy != NULL )
    return "a null string did not have a null copy";

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
  unsigned short result;

  result = is_empty( " \f\n\r\t\v" );

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
  char *str;

  str = replace_char( "sucka_punch_you", '_', ' ' );
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
  size_t buffer_size = 100;

  safe_strncpy( str, "How could this happen to me?", buffer_size );
  replace_first_string( str, "this", "this actually" );
  ASSERT_STRINGS_EQUAL( "How could this actually happen to me?", str, "a single replacement was not handled properly" );

  safe_strncpy( str, "How could this happen to me?", buffer_size );
  replace_first_string( str, "me?", "me!" );
  ASSERT_STRINGS_EQUAL( "How could this happen to me!", str, "a replacement at the end was not handled properly" );

  safe_strncpy( str, "How could this happen to me?", buffer_size );
  replace_first_string( str, "How could", "Did" );
  ASSERT_STRINGS_EQUAL( "Did this happen to me?", str, "a replacement at the beginning was not handled properly" );

  safe_strncpy( str, "How could this happen to me? I think this is unacceptable.", buffer_size );
  replace_first_string( str, "this", "that" );
  ASSERT_STRINGS_EQUAL( "How could that happen to me? I think this is unacceptable.", str, "two replacements were not handled properly" )

  return NULL;
}

const char *
test_replace_string
( void )
{
  char str[1000];
  size_t buffer_size = 1000;

  safe_strncpy( str, "How could this happen to me?", buffer_size );
  replace_string( str, "this", "this actually" );
  ASSERT_STRINGS_EQUAL( "How could this actually happen to me?", str, "a single replacement was not handled properly" );

  safe_strncpy( str, "How could this happen to me?", buffer_size );
  replace_string( str, "me?", "me!" );
  ASSERT_STRINGS_EQUAL( "How could this happen to me!", str, "a replacement at the end was not handled properly" );

  safe_strncpy( str, "How could this happen to me?", buffer_size );
  replace_string( str, "How could", "Did" );
  ASSERT_STRINGS_EQUAL( "Did this happen to me?", str, "a replacement at the beginning was not handled properly" );

  safe_strncpy( str, "How could this happen to me? I think this is unacceptable.", buffer_size );
  replace_string( str, "this", "that" );
  ASSERT_STRINGS_EQUAL( "How could that happen to me? I think that is unacceptable.", str, "two replacements were not handled properly" )

  return NULL;
}

const char *
test_title_case( void )
{
  char *str;

  str = get_title_case( "i'm the original string" );
  if( !str )
    return "could not build the new string";
  if( strcmp( str, "I'm The Original String" ) != 0 )
    return "the new string was not title-cased";

  return NULL;
}
