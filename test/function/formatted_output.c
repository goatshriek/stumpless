#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_appender( void );

StumplessFormattedOutput * GetTestByteOutput( void );
StumplessFormattedOutput * GetTestTextOutput( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_appender();
  if( result != NULL ){
    printf( "Appender Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_appender( void )
{
  StumplessFormattedOutput * output_1 = GetTestByteOutput();
  StumplessFormattedOutput * output_2 = GetTestTextOutput();
  StumplessFormattedOutput * output_3 = GetTestTextOutput();
  
  StumplessStatusCode status;
  
  status = StumplessAppendFormattedOutputs( NULL, output_1 );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty argument did not generate the appropriate error";
  
  status = StumplessAppendFormattedOutputs( output_1, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty argument did not generate the appropriate error";
  
  status = StumplessAppendFormattedOutputs( NULL, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty argument did not generate the appropriate error";
  
  status = StumplessAppendFormattedOutputs( output_1, output_2 );
  if( status != STUMPLESS_INCOMPATIBLE_ARGUMENTS )
    return "two different format types did not generate the appropriate error";
  
  status = StumplessAppendFormattedOutputs( output_2, output_3 );
  if( status != STUMPLESS_SUCCESS )
    return "the appending of one valid output to another was unsuccessful";
  if( output_2->payload->values->first->next->next->next == NULL )
    return "the outputs were not appended";
  
  return NULL;
}

StumplessFormattedOutput *
GetTestByteOutput( void )
{
  StumplessFormattedOutput * output;
  output = malloc( sizeof( StumplessFormattedOutput ) );
  if( output == NULL )
    return NULL;
  
  output->format = STUMPLESS_BINARY;
  
  return output;
}

StumplessFormattedOutput *
GetTestTextOutput( void )
{
  StumplessFormattedOutput * output;
  output = malloc( sizeof( StumplessFormattedOutput ) );
  if( output == NULL )
    return NULL;
  
  output->format = STUMPLESS_TEXT;
  output->payload = malloc( sizeof( StumplessFormattedPayload ) );
  if( output->payload == NULL )
    return NULL;
  
  output->payload->values = StumplessNewValueList();
  if( output->payload->values == NULL )
    return NULL;
  
  StumplessAppendStringToValueList( output->payload->values, "test 1\n" );
  StumplessAppendStringToValueList( output->payload->values, "test 2\n" );
  StumplessAppendStringToValueList( output->payload->values, "test 3" );
  
  return output;
}
