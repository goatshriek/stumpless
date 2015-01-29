#include <stdlib.h>
#include <stdio.h>

#include "private/handler/stream.h"
#include "private/type.h"
#include "test/helper.h"

const char * test_stream_handler( void );
const char * test_raw_string_readability( void );
const char * test_raw_string_write( void );
const char * test_text_readability( void );
const char * test_text_write( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  RUN_TEST( stream_handler )
  RUN_TEST( raw_string_readability )
  RUN_TEST( raw_string_write )
  RUN_TEST( text_readability )
  RUN_TEST( text_write )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_stream_handler
( void )
{
  const Handler *result;
  Output *output = NULL;

  result = HandleStreamOutput( NULL, output );
  if( result )
    return "a NULL Output caused a problem";

  output = BuildTextOutput();
  FAIL_IF_NULL( output, "the test output could not be built" )
  result = HandleStreamOutput( NULL, output );
  if( result )
    return "a normal Output could not by a NULL Handler";

  output->profile->into_stream = NULL;
  result = HandleStreamOutput( NULL, output );
  if( result )
    return "an Output with no stream function caused problems";

  return NULL;
}

const char *
test_raw_string_readability
( void )
{
  char *buffer, *result;
  const char *filename;
  Exception *e;
  FILE *test_file;
  Output *text;

  filename = "raw_string_readability.txt";

  test_file = fopen( filename, "w+" );
  FAIL_IF_NULL( test_file, "the test file could not be created" )

  text = BuildRawStringOutput();
  FAIL_IF_NULL( text, "the test output could not be built" )

  RawStringOutputIntoStream( test_file, text );

  fclose( test_file );

  test_file = fopen( filename, "r" );
  FAIL_IF_NULL( test_file, "the test file could not be reopened" )

  buffer = malloc( sizeof( char ) * 100 );
  FAIL_IF_NULL( buffer, "the test buffer could not be created" )

  result = fgets( buffer, 100, test_file );
  FAIL_IF_NULL( result, "the first file read resulted in an error" )
  ASSERT_STRINGS_EQUAL( "Test String with\n", buffer, "the first string was not correct" )

  result = fgets( buffer, 100, test_file );
  FAIL_IF_NULL( result, "the second file read resulted in an error" )
  ASSERT_STRINGS_EQUAL( "stuff in it.", buffer, "the second string was not correct" )

  FAIL_IF_NOT_NULL( fgets( buffer, 100, test_file ), "there was extra information stored in the file" )

  fclose( test_file );
  remove( filename );

  return NULL;
}

const char *
test_raw_string_write
( void )
{
  Exception *e;
  FILE *test_file;
  Output *str;

  test_file = tmpfile();
  FAIL_IF_NULL( test_file, "the test file could not be created" )

  str = BuildRawStringOutput();
  FAIL_IF_NULL( str, "the test output could not be built" )

  RawStringOutputIntoStream( test_file, str );

  fclose( test_file );

  return NULL;
}

const char *
test_text_readability
( void )
{
  char *buffer, *result;
  const char *filename = "text_readability.txt";
  Exception *e;
  FILE *test_file;
  Output *text;

  test_file = fopen( filename, "w+" );
  FAIL_IF_NULL( test_file, "the test file could not be created" )

  text = BuildTextOutput();
  FAIL_IF_NULL( text, "the test output could not be built" )

  TextOutputIntoStream( test_file, text );

  fclose( test_file );

  test_file = fopen( filename, "r" );
  FAIL_IF_NULL( test_file, "the test file could not be reopened" )

  buffer = malloc( sizeof( char ) * 10 );
  FAIL_IF_NULL( buffer, "the test buffer could not be created" )

  result = fgets( buffer, 10, test_file );
  FAIL_IF_NULL( result, "the first file read resulted in an error" )
  ASSERT_STRINGS_EQUAL( "First\n", buffer, "the first string was not correct" )

  result = fgets( buffer, 10, test_file );
  FAIL_IF_NULL( result, "the second file read resulted in an error" )
  ASSERT_STRINGS_EQUAL( "Second\n", buffer, "the second string was not correct" )

  result = fgets( buffer, 10, test_file );
  FAIL_IF_NULL( result, "the third file read resulted in an error" )
  ASSERT_STRINGS_EQUAL( "Third", buffer, "the third string was not correct" )

  FAIL_IF_NOT_NULL( fgets( buffer, 10, test_file ), "there was extra information stored in the file" )

  fclose( test_file );
  remove( filename );

  return NULL;
}

const char *
test_text_write
( void )
{
  Exception *e;
  FILE *test_file;
  Output *text;

  test_file = tmpfile();
  FAIL_IF_NULL( test_file, "the test file could not be created" )

  text = BuildTextOutput();
  FAIL_IF_NULL( text, "the test output could not be built" )

  TextOutputIntoStream( test_file, text );

  fclose( test_file );

  return NULL;
}
