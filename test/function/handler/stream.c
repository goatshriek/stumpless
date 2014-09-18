#include <stdlib.h>
#include <stdio.h>

#include "private/type.h"

#include "private/handler/stream.h"

#include "helper.h"

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
  Output *output = NULL;
  Status *status;
  
  status = HandleStreamOutput( NULL, output );
  FAIL_IF_NULL( status, "a null output did not generate an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a null output did not raise an empty argument error" )
  
  output = BuildTextOutput();
  FAIL_IF_NULL( output, "the test output could not be built" )
  status = HandleStreamOutput( NULL, output );
  FAIL_IF_NOT_NULL( status, "a normal output could not be handled by a stream with no options" )
  
  output->profile->into_stream = NULL;
  status = HandleStreamOutput( NULL, output );
  FAIL_IF_NULL( status, "an output with no to stream function was properly handled" )
  ASSERT_STRINGS_EQUAL( "incompatible profile", status->name, "an output with a profile incompatible with stream output did not return the appropriate error" )
  
  return NULL;
}

const char *
test_raw_string_readability
( void )
{
  const char * filename = "raw_string_readability.txt";
  
  FILE * test_file = fopen( filename, "w+" );
  FAIL_IF_NULL( test_file, "the test file could not be created" )
  
  Output * text = BuildRawStringOutput();
  FAIL_IF_NULL( text, "the test output could not be built" )
  
  Status * status = RawStringOutputIntoStream( text, test_file );
  FAIL_IF_NOT_NULL( status, "the string could not be written to the file" )
  
  fclose( test_file );
  
  test_file = fopen( filename, "r" );
  FAIL_IF_NULL( test_file, "the test file could not be reopened" )
  
  char * buffer = malloc( sizeof( char ) * 100 );
  FAIL_IF_NULL( buffer, "the test buffer could not be created" )
  
  char * result = fgets( buffer, 100, test_file );
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
  FILE * test_file = tmpfile();
  FAIL_IF_NULL( test_file, "the test file could not be created" )
  
  Output * str = BuildRawStringOutput();
  FAIL_IF_NULL( str, "the test output could not be built" )
  
  Status * status = RawStringOutputIntoStream( str, test_file );
  FAIL_IF_NOT_NULL( status, "the string could not be written to the file" )
  
  fclose( test_file );
  
  return NULL;
}

const char *
test_text_readability
( void )
{
  const char * filename = "text_readability.txt";
  
  FILE * test_file = fopen( filename, "w+" );
  FAIL_IF_NULL( test_file, "the test file could not be created" )
  
  Output * text = BuildTextOutput();
  FAIL_IF_NULL( text, "the test output could not be built" )
  
  Status * status = TextOutputIntoStream( text, test_file );
  FAIL_IF_NOT_NULL( status, "the text could not be written to the file" )
  
  fclose( test_file );
  
  test_file = fopen( filename, "r" );
  FAIL_IF_NULL( test_file, "the test file could not be reopened" )
  
  char * buffer = malloc( sizeof( char ) * 10 );
  FAIL_IF_NULL( buffer, "the test buffer could not be created" )
  
  char * result = fgets( buffer, 10, test_file );
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
  FILE * test_file = tmpfile();
  FAIL_IF_NULL( test_file, "the test file could not be created" )
  
  Output * text = BuildTextOutput();
  FAIL_IF_NULL( text, "the test output could not be built" )
  
  Status * status = TextOutputIntoStream( text, test_file );
  FAIL_IF_NOT_NULL( status, "the text could not be written to the file" )
  
  fclose( test_file );
  
  return NULL;
}
