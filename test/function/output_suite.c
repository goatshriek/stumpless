#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/container/list/value.h"
#include "private/output.h"
#include "private/type.h"
#include "test/function/output_suite.h"
#include "test/helper.h"

const char * test_is_empty( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  TEST( Destroy )

  RUN_TEST( is_empty )
  RUN_TEST( to_string )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestDestroy
( void )
{
  DestroyOutput( NULL );

  Output *output = BuildOutput();
  if( !output )
    return "could not build a test Output";

  DestroyOutput( output );

  return NULL;
}

const char *
test_is_empty
( void )
{
  Output *output = BuildTextOutput();
  FAIL_IF_NULL( output, "could not build test text output" )

  if( OutputIsEmpty( output ) )
    return "a full output was marked as empty";

  output->data = NULL;
  if( !OutputIsEmpty( output ) )
    return "an output with a null list was not marked as empty";

  output->data = NewValueList();
  if( !OutputIsEmpty( output ) )
    return "an output with an empty list was not marked as empty";

  return NULL;
}

const char *
test_to_string( void )
{
  //Output * output = BuildTextOutput();
  //FAIL_IF_NULL( output, "could not build the test output" )

  //char * buffer;
  //StatusCode status;

  //buffer = OutputToString( NULL );
  //FAIL_IF_NOT_NULL( buffer, "a NULL output did not generate the appropriate error" )

  //buffer = OutputToString( output );
  //FAIL_IF_NULL( buffer, "a valid output did not generate a string" )

  //if( strcmp( buffer, "First\nSecond\nThird" ) != 0 )
  //  return "the string written was not equivalent to the output's contents";

  return NULL;
}
