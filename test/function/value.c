#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/type.h"
#include "private/value.h"
#include "private/value_constructor.h"

#include "helper.h"

const char * test_array_value_to_value_list( void );
const char * test_destructor( void );
const char * test_into_string( void );
const char * test_outside_access ( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( array_value_to_value_list )
  RUN_TEST( destructor )
  RUN_TEST( into_string )
  RUN_TEST( outside_access )
  RUN_TEST( to_string )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_array_value_to_value_list( void )
{
  Value * value = BuildUnsignedShortValue();
  FAIL_IF_NULL( value, "could not build the test short value" )
  ValueList * list = value->profile->to_value_list( value );
  FAIL_IF_NULL( list, "a non-array value could not be converted to a list" )
  
  value = BuildEmptyUnsignedIntArrayValue();
  FAIL_IF_NULL( value, "could not build the test empty array value" )
  list = value->profile->to_value_list( value );
  FAIL_IF_NULL( list, "a list could not be built from an empty array value" )
  if( !ValueListIsEmpty( list ) )
    return "an empty list was not empty for an empty array value"; 
  
  value = BuildIntArrayValue();
  FAIL_IF_NULL( value, "could not build the test int array value" )
  list = value->profile->to_value_list( value );
  FAIL_IF_NULL( list, "a list could not be built from an int array value" )
  
  FAIL_IF_NULL( list->first, "the generated list was empty" )
  FAIL_IF_NULL( list->first->value, "the list nodes were invalid" )
  if( strcmp( list->first->value->profile->name, "int" ) != 0 )
    return "the values of the list did not have the proper type";
  if( list->first->value->data->i != 0 )
    return "the values of the list did not reflect the original array";
  
  FAIL_IF_NULL( list->last, "the generated list was not invalid" )
  FAIL_IF_NULL( list->last->value, "the list nodes were invalid" )
  if( strcmp( list->last->value->profile->name, "int" ) != 0 )
    return "the values of the list did not have the proper type";
  if( list->last->value->data->i != 9 )
    return "the values of the list did not reflect the original array";
 
  return NULL;
}

const char *
test_destructor( void )
{
  DestroyValue( NULL );
  
  Value * value = ValueFromString( "testing value" );
  if( value == NULL )
    return "the value could not be created";
  
  DestroyValue( value );
  
  return NULL;
}

const char *
test_into_string( void )
{
  Value * value = BuildUnsignedIntValue();
  if( value == NULL )
    return "could not build the test value";
  
  char str[11];
  
  StatusCode status = ValueIntoString( NULL, value );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty string did not generate the correct error";
  
  status = ValueIntoString( str, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty list did not generate the correct error";
  
  status = ValueIntoString( str, value );
  if( status != STUMPLESS_SUCCESS )
    return "a correct void pointer value and string generated an error";
 
  if( strstr( str, "4294967196" ) == NULL )
    return "the string did not have the correct contents in it";
  
  value = BuildUnsignedIntValue();
  status = ValueIntoString( str, value );
  if( status != STUMPLESS_SUCCESS )
    return "a singular unsigned int value and string generated an error";
  
  if( strcmp( str, "4294967196") != 0 )
    return "the unsigned int string did not match the value's data";
  
  return NULL;
}

const char *
test_outside_access( void )
{
  Value * value = malloc( sizeof( Value ) );
  if( value == NULL )
    return "the test value could not be created";
  
  value->data = malloc( sizeof( Type ) );
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
test_to_string( void )
{
  Value * value = BuildIntValue();
  if( value == NULL )
    return "the test value could not be created";
  char * str;
  
  str = ValueToString( NULL );
  if( str != NULL )
    return "a null value did not create a null string";
  
  str = ValueToString( value );
  if( str == NULL )
    return "a valid value returned a null string";
  
  if( strstr( str, "45678" ) == NULL )
    return "the string did not contain the value's contents";
  
  return NULL;
}
