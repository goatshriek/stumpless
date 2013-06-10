#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "helper.h"

const char * test_is_empty( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  //RUN_TEST( is_empty )
  RUN_TEST( to_string )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_is_empty( void )
{
  StumplessFormattedOutput * output = BuildTextFormattedOutput();
  FAIL_IF_NULL( output, "could not build test text output" )
  
  if( StumplessFormattedOutputIsEmpty( output ) )
    return "a full output was marked as empty";
  
  output->payload->values = NULL;
  if( !StumplessFormattedOutputIsEmpty( output ) )
    return "an output with a null list was not marked as empty";
  
  output->payload->values = StumplessNewValueList();
  if( output->payload->values == NULL )
    return "could not create a new value list";
  if( !StumplessFormattedOutputIsEmpty( output ) )
    return "an output with an empty list was not marked as empty";
  
  return NULL;
}

const char *
test_to_string( void )
{
  //StumplessFormattedOutput * output = BuildTextFormattedOutput();
  //FAIL_IF_NULL( output, "could not build the test output" )
  
  //char * buffer;
  //StumplessStatusCode status;
  
  //buffer = StumplessFormattedOutputToString( NULL );
  //FAIL_IF_NOT_NULL( buffer, "a NULL output did not generate the appropriate error" )
  
  //buffer = StumplessFormattedOutputToString( output );
  //FAIL_IF_NULL( buffer, "a valid output did not generate a string" )
  
  //if( strcmp( buffer, "First\nSecond\nThird" ) != 0 )
  //  return "the string written was not equivalent to the output's contents";
  
  return NULL;
}
