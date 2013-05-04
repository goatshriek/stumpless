#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "helper.h"

const char * test_array_value_to_value_list( void );
const char * test_default_format( void );
const char * test_destructor( void );
const char * test_into_string( void );
const char * test_is_array( void );
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
  
  RUN_TEST( array_value_to_value_list )
  RUN_TEST( default_format )
  RUN_TEST( destructor )
  RUN_TEST( into_string )
  RUN_TEST( is_array )
  RUN_TEST( outside_access )
  RUN_TEST( stream_write )
  RUN_TEST( to_string )
  RUN_TEST( value_from_string )
  RUN_TEST( value_from_unsigned_int )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_array_value_to_value_list( void )
{
  StumplessValue * value = BuildUnsignedShortValue();
  FAIL_IF_NULL( value, "could not build the test short value" )
  StumplessValueList * list = StumplessArrayValueToValueList( value );
  FAIL_IF_NOT_NULL( list, "a non-array value was converted to a list" )
  
  value = BuildEmptyUnsignedIntArrayValue();
  FAIL_IF_NULL( value, "could not build the test empty array value" )
  list = StumplessArrayValueToValueList( value );
  FAIL_IF_NULL( list, "a list could not be built from an empty array value" )
  if( !StumplessValueListIsEmpty( list ) )
    return "an empty list was not empty for an empty array value"; 
  
  value = BuildIntArrayValue();
  FAIL_IF_NULL( value, "could not build the test int array value" )
  list = StumplessArrayValueToValueList( value );
  FAIL_IF_NULL( list, "a list could not be built from an int array value" )
  
  FAIL_IF_NULL( list->first, "the generated list was empty" )
  FAIL_IF_NULL( list->first->value, "the list nodes were invalid" )
  if( list->first->value->type != STUMPLESS_INT )
    return "the values of the list did not have the proper type";
  if( list->first->value->data->i != 0 )
    return "the values of the list did not reflect the original array";
  
  FAIL_IF_NULL( list->last, "the generated list was not invalid" )
  FAIL_IF_NULL( list->last->value, "the list nodes were invalid" )
  if( list->last->value->type != STUMPLESS_INT )
    return "the values of the list did not have the proper type";
  if( list->last->value->data->i != 9 )
    return "the values of the list did not reflect the original array";
 
  return NULL;
}

const char *
test_default_format( void )
{
  StumplessValue * value = BuildUnsignedShortValue();
  if( value == NULL )
    return "the first test value could not be built";
  const char * format = StumplessValueTypeDefaultFormat( value->type );
  if( format == NULL )
    return "the default format could not be retrieved";
  if( strcmp( format, "%hu" ) != 0 )
    return "an unsigned short did not have the proper format";
  
  value = BuildIntArrayValue();
  format = StumplessValueTypeDefaultFormat( value->type );
  if( format == NULL )
    return "the default format could not be retrieved";
  if( strcmp( format, "%i" ) != 0 )
    return "an int array did not have the proper format";
  
  return NULL;
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
test_is_array( void )
{
  StumplessValue * value = BuildUnsignedShortValue();
  if( value == NULL )
    return "could not build the test value";
  if( StumplessValueIsArray( value ) )
    return "a non-array value was listed as an array";
  
  value = BuildIntArrayValue();
  if( value == NULL )
    return "could not build the test array value";
  if( !StumplessValueIsArray( value ) )
    return "an array value was listed as not an array";
  
  value = BuildVoidValue();
  if( value == NULL )
    return "could not build the test void value";
  if( StumplessValueIsArray( value ) )
    return "a void array was listed as an array";
  
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
    return "a value with an array was not written to the stream successfully";
  
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
