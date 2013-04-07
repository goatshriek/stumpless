#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_into_string( void );
const char * test_output_appender( void );
const char * test_string_appender( void );
const char * test_to_string( void );
const char * test_unsigned_int_appender( void );
const char * test_value_appender( void );

StumplessFormattedOutput * GetTestByteOutput( void );
StumplessFormattedOutput * GetTestTextOutput( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_into_string();
  if( result != NULL ){
    printf( "Into String Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_output_appender();
  if( result != NULL ){
    printf( "Output Appender Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_string_appender();
  if( result != NULL ){
    printf( "String Appender Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_to_string();
  if( result != NULL ){
    printf( "To String Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_unsigned_int_appender();
  if( result != NULL ){
    printf( "Unsigned Int Appender Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_value_appender();
  if( result != NULL ){
    printf( "Value Appender Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_into_string( void )
{
  StumplessFormattedOutput * output = GetTestTextOutput();
  if( output == NULL )
    return "the test output cold not be created";
  
  char buffer[21];
  StumplessStatusCode status;
  
  status = StumplessFormattedOutputIntoString( NULL, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "empty arguments did not generate the appropriate error";
  
  status = StumplessFormattedOutputIntoString( NULL, output );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a NULL output did not generate the appropriate error";
  
  status = StumplessFormattedOutputIntoString( buffer, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a NULL string did not generate the appropriate error";
  
  status = StumplessFormattedOutputIntoString( buffer, output );
  if( status != STUMPLESS_SUCCESS )
    return "the string was not properly written to";
  
  if( strcmp( buffer, "test 1\ntest 2\ntest 3" ) != 0 )
    return "the string written was not equivalent to the output's contents";
  
  return NULL;
}

const char *
test_output_appender( void )
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

const char *
test_string_appender( void )
{
  StumplessStatusCode status;
  StumplessFormattedOutput * output = GetTestTextOutput();
  if( output == NULL )
    return "the test output could not be created";
  
  status = StumplessAppendStringToFormattedOutput( NULL, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "two empty arguments did not generate the appropriate error";
  
  status = StumplessAppendStringToFormattedOutput( output, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a null string did not generate the appropriate error";
  
  status = StumplessAppendStringToFormattedOutput( NULL, "empty output" );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a null output did not generate the appropriate error";
  
  status = StumplessAppendStringToFormattedOutput( output, "sucka" );
  if( status != STUMPLESS_SUCCESS )
    return "the string was not properly appended";
  if( strcmp( output->payload->values->last->value->data->c_p , "sucka" ) != 0 )
    return "the string was not actually appended to the output list";
  
  return NULL;
}

const char *
test_to_string( void )
{
  StumplessFormattedOutput * output = GetTestTextOutput();
  if( output == NULL )
    return "the test output cold not be created";
  
  char * buffer;
  StumplessStatusCode status;
  
  buffer = StumplessFormattedOutputToString( NULL );
  if( buffer != NULL )
    return "a NULL output did not generate the appropriate error";
  
  buffer = StumplessFormattedOutputToString( output );
  if( buffer == NULL )
    return "a valid output did not generate a string";
  
  if( strcmp( buffer, "test 1\ntest 2\ntest 3" ) != 0 )
    return "the string written was not equivalent to the output's contents";
  
  return NULL;
}

const char *
test_unsigned_int_appender( void )
{
  StumplessStatusCode status;
  StumplessFormattedOutput * output = GetTestTextOutput();
  if( output == NULL )
    return "the test output could not be created";
  
  status = StumplessAppendUnsignedIntToFormattedOutput( NULL, 3 );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a null output did not generate the appropriate error";
  
  status = StumplessAppendUnsignedIntToFormattedOutput( output, 27 );
  if( status != STUMPLESS_SUCCESS )
    return "the number was not properly appended";
  if( output->payload->values->last->value->data->u_i != 27 )
    return "the number was not actually appended to the output list";
  
  return NULL; 
}

const char *
test_value_appender( void )
{
  StumplessStatusCode status;
  StumplessFormattedOutput * output = GetTestTextOutput();
  if( output == NULL )
    return "the test output could not be created";
  
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return "the test value could not be created";
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return "the test value data could not be created";
  value->type = STUMPLESS_STRING;
  value->data->c_p = "Test Value";
  
  status = StumplessAppendValueToFormattedOutput( NULL, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "two empty arguments did not generate the appropriate error";
  
  status = StumplessAppendValueToFormattedOutput( output, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty value did not generate the appropriate error";
  
  status = StumplessAppendValueToFormattedOutput( NULL, value );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty output did not generate the appropriate error";
  
  status = StumplessAppendValueToFormattedOutput( output, value );
  if( status != STUMPLESS_SUCCESS )
    return "the value was not successfully appended";
  const char * last_value = output->payload->values->last->value->data->c_p;
  if( strcmp( last_value, "Test Value" ) != 0 )
    return "the value was not actually appended to the list";
  
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
