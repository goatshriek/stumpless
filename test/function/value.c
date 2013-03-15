#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_destructor( void );
const char * test_into_string( void );
const char * test_stream_write( void );
const char * test_to_string( void );
const char * test_value_from_string( void );

StumplessValue * GetTestArrayValue( void );
StumplessValue * GetTestVoidValue( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_destructor();
  if( result != NULL ){
    printf( "Destructor Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_into_string();
  if( result != NULL ){
    printf( "Write Into String Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_stream_write();
  if( result != NULL ){
    printf( "Stream Write Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_to_string();
  if( result != NULL ){
    printf( "To String Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_value_from_string();
  if( result != NULL ){
    printf( "Value From String Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_destructor( void )
{
  StumplessDestroyValue( NULL );
  
  StumplessValue * value = StumplessValueFromString( "testing value" );
  if( value == NULL )
    return "the value could not be created";
  
  StumplessDestroyValue( value );
  
  return NULL;
}

const char *
test_into_string( void )
{
  StumplessValue * value = GetTestVoidValue();
  if( value == NULL )
    return "the test value could not be created";
  
  char str[11];
  
  StumplessStatusCode status = StumplessValueIntoString( NULL, value );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty string did not generate the correct error";
  
  status = StumplessValueIntoString( str, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty list did not generate the correct error";
  
  status = StumplessValueIntoString( str, value );
  if( status != STUMPLESS_SUCCESS )
    return "a correct value and string generated an error";
 
  if( strstr( str, "cdefghij" ) == NULL )
    return "the string did not have the correct contents in it";
  
  return NULL;
}

const char *
test_stream_write( void )
{
  StumplessValue * value = StumplessValueFromString( "sucka" );
  
  StumplessStatusCode status = StumplessWriteValueToStream( NULL, value );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty file pointer did not generate the correct error";
  
  status = StumplessWriteValueToStream( stdout, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty value did not generate the correct error";
  
  status = StumplessWriteValueToStream( stdout, value );
  if( status != STUMPLESS_SUCCESS )
    return "the value was not written to the stream successfully";
  
  value->format = NULL;
  if( status != STUMPLESS_SUCCESS )
    return "a value without a format specifier generated an error";
  
  value = GetTestArrayValue();
  status = StumplessWriteValueToStream( stdout, value );
  if( status != STUMPLESS_SUCCESS )
    return "a value with an array were not written to the stream successfully";
  
  value->format = NULL;
  status = StumplessWriteValueToStream( stdout, value );
  if( status != STUMPLESS_SUCCESS )
    return "a value array without a format specifier generated an error";
  
  value = GetTestVoidValue();
  status = StumplessWriteValueToStream( stdout, value );
  if( status != STUMPLESS_SUCCESS )
    return "the void pointer was not handled properly";
  
  return NULL;
}

const char *
test_to_string( void )
{
  StumplessValue * value = GetTestArrayValue();
  if( value == NULL )
    return "the test value could not be created";
  char * str;
  
  str = StumplessValueToString( NULL );
  if( str != NULL )
    return "a null value did not create a null string";
  
  str = StumplessValueToString( value );
  if( str == NULL )
    return "a valid value returned a null string";
  
  if( strstr( str, "123456" ) == NULL )
    return "the string did not contain the value's contents";
  
  return NULL;
}

const char *
test_value_from_string( void )
{
  StumplessValue * value = NULL;
  
  value = StumplessValueFromString( NULL );
  if( value != NULL )
    return "a null value was not returned for a null string";
  
  value = StumplessValueFromString( "test string 'n such" );
  if( value == NULL )
    return "a null value was returned for a non-null string";
  if( value->type != STUMPLESS_STRING )
    return "the value did not have a string type";
  if( value->data == NULL )
    return "the value did not have any data";
  if( strcmp( value->data->c_p, "test string 'n such" ) != 0 )
    return "the value string did not match the initial string";
  
  return NULL;
}

StumplessValue *
GetTestArrayValue( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  value->format = "%d";
  value->type = STUMPLESS_INT_POINTER;
  value->data->i_p = malloc( sizeof( int ) * 10 );
  value->data->i_p[0] = 0;
  value->data->i_p[1] = 1;
  value->data->i_p[2] = 2;
  value->data->i_p[3] = 3;
  value->data->i_p[4] = 4;
  value->data->i_p[5] = 5;
  value->data->i_p[6] = 6;
  value->data->i_p[7] = 7;
  value->data->i_p[8] = 8;
  value->data->i_p[9] = 9;
  value->length = 10;
  
  return value;
}

StumplessValue *
GetTestVoidValue( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  value->type = STUMPLESS_VOID_POINTER;
  char * generic = malloc( sizeof( char ) * 10 );
  if( generic == NULL )
    return NULL;
  
  generic[0] = 'a';
  generic[1] = 'b';
  generic[2] = 'c';
  generic[3] = 'd';
  generic[4] = 'e';
  generic[5] = 'f';
  generic[6] = 'g';
  generic[7] = 'h';
  generic[8] = 'i';
  generic[9] = 'j';
  
  value->data->v_p = (void *) generic;
  value->length = sizeof( char ) * 10;
  
  return value;
}
