#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/formatted_output.h"
#include "private/type.h"

#include "helper.h"

const char * test_is_empty( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( is_empty )
  RUN_TEST( to_string )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_is_empty( void )
{
  FormattedOutput * output = BuildTextFormattedOutput();
  FAIL_IF_NULL( output, "could not build test text output" )
  
  if( FormattedOutputIsEmpty( output ) )
    return "a full output was marked as empty";
  
  output->data = NULL;
  if( !FormattedOutputIsEmpty( output ) )
    return "an output with a null list was not marked as empty";
  
  output->data = ( void * ) NewValueList();
  if( output->data == NULL )
    return "could not create a new value list";
  if( !FormattedOutputIsEmpty( output ) )
    return "an output with an empty list was not marked as empty";
  
  return NULL;
}

const char *
test_to_string( void )
{
  //FormattedOutput * output = BuildTextFormattedOutput();
  //FAIL_IF_NULL( output, "could not build the test output" )
  
  //char * buffer;
  //StatusCode status;
  
  //buffer = FormattedOutputToString( NULL );
  //FAIL_IF_NOT_NULL( buffer, "a NULL output did not generate the appropriate error" )
  
  //buffer = FormattedOutputToString( output );
  //FAIL_IF_NULL( buffer, "a valid output did not generate a string" )
  
  //if( strcmp( buffer, "First\nSecond\nThird" ) != 0 )
  //  return "the string written was not equivalent to the output's contents";
  
  return NULL;
}
