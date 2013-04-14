#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "builder.h"

const char * test_destructor( void );
const char * test_into_string( void );
const char * test_outside_access ( void );
const char * test_stream_write( void );
const char * test_to_string( void );
const char * test_value_from_string( void );
const char * test_value_from_unsigned_int( void );

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
  
  result = test_outside_access();
  if( result != NULL ){
    printf( "Outside Access Test Failed: %s\n", result );
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
  
  result = test_value_from_unsigned_int();
  if( result != NULL ){
    printf( "Value From Unsigned Int Test Failed: %s\n", result );
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
  StumplessValue * value = BuildVoidValue();
  if( value == NULL )
    return "could not build the test value";
  
  char str[11];
  
  StumplessStatusCode status = StumplessValueIntoString( NULL, value );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty string did not generate the correct error";
  
  status = StumplessValueIntoString( str, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty list did not generate the correct error";
  
  status = StumplessValueIntoString( str, value );
  if( status != STUMPLESS_SUCCESS )
    return "a correct void pointer value and string generated an error";
 
  if( strstr( str, "cdefghij" ) == NULL )
    return "the string did not have the correct contents in it";
  
  value = BuildUnsignedIntValue();
  status = StumplessValueIntoString( str, value );
  if( status != STUMPLESS_SUCCESS )
    return "a singular unsigned int value and string generated an error";
  
  if( strcmp( str, "4294967196") != 0 )
    return "the unsigned int string did not match the value's data";
  
  return NULL;
}

const char *
test_outside_access( void )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return "the test value could not be created";
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return "the test value's data could not be created";
  
  long * num_list = malloc( sizeof( float ) * 7 );
  if( num_list == NULL )
    return "the test array could not be created";
  
  num_list[0] = 4;
  num_list[1] = 7;
  num_list[2] = 3;
  num_list[3] = 666;
  num_list[4] = 0;
  num_list[5] = 5;
  num_list[6] = 45;
  
  value->data->l_p = num_list;
  
  num_list[2] = 4;
  
  if( value->data->l_p[2] != 4 )
    return "the array held by the value could not be modified from the outside";
  
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
  
  value = BuildIntArrayValue();
  status = StumplessWriteValueToStream( stdout, value );
  if( status != STUMPLESS_SUCCESS )
    return "a value with an array were not written to the stream successfully";
  
  value->format = NULL;
  status = StumplessWriteValueToStream( stdout, value );
  if( status != STUMPLESS_SUCCESS )
    return "a value array without a format specifier generated an error";
  
  value = BuildVoidValue();
  if( value == NULL )
    return "could not build the test value";
  status = StumplessWriteValueToStream( stdout, value );
  if( status != STUMPLESS_SUCCESS )
    return "the void pointer was not handled properly";
  
  return NULL;
}

const char *
test_to_string( void )
{
  StumplessValue * value = BuildIntArrayValue();
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

const char *
test_value_from_unsigned_int( void )
{
  StumplessValue * value = NULL;
  
  value = StumplessValueFromUnsignedInt( 3 );
  if( value == NULL )
    return "the value could not be created";
  if( value->type != STUMPLESS_UNSIGNED_INT )
    return "the created value did not have an unsigned int type";
  if( value->data == NULL || value->data->u_i != 3 )
    return "the value did not contain the correct number";
  
  return NULL;
}
