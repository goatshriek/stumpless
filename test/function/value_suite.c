#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless/value.h>
#include <stumpless/value/constructor.h>

#include "private/container/list/value.h"
#include "private/container/list/iterator/value.h"
#include "private/type.h"
#include "test/helper.h"

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
test_array_value_to_value_list
( void )
{
  Value *value;
  ValueList *list;
  ValueListIterator *values;

  value = BuildUnsignedShortValue();
  FAIL_IF_NULL( value, "could not build the test short value" )
  list = value->profile->to_value_list( value );
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

  values = BeginValueList( list );
  value = NextInValueListIterator( values );
  FAIL_IF_NULL( value, "the generated list was empty" )
  if( strcmp( value->profile->name, "int" ) != 0 )
    return "the values of the list did not have the proper type";
  if( value->i != 0 )
    return "the values of the list did not reflect the original array";

  value = NextInValueListIterator( values );

  FAIL_IF_NULL( value, "the list did not contain all nodes" )
  if( strcmp( value->profile->name, "int" ) != 0 )
    return "the values of the list did not have the proper type";
  if( value->i != 1 )
    return "the values of the list did not reflect the original array";

  DestroyValueListIterator( values );
  return NULL;
}

const char *
test_destructor( void )
{
  Value *value;

  DestroyValue( NULL );

  value = NewValueForString( "testing value" );
  if( !value )
    return "the value could not be created";

  DestroyValue( value );

  return NULL;
}

const char *
test_into_string
( void )
{
  char str[11];
  char *result;
  Value *value;

  value = BuildUnsignedIntValue();
  if( !value )
    return "could not build the test value";

  result = ValueIntoString( NULL, value, 11 );
  if( result )
    return "an empty string caused a problem";

  result = ValueIntoString( str, NULL, 11 );
  if( result != str )
    return "an empty Value caused a problem";

  result = ValueIntoString( str, value, 11 );
  if( result != str )
    return "a correct void pointer value and string caused a problem";

  if( strstr( str, "4294967196" ) == NULL )
    return "the string did not have the correct contents in it";

  value = BuildUnsignedIntValue();
  result = ValueIntoString( str, value, 11 );
  if( result != str )
    return "a singular unsigned int value and string generated an error";

  if( strcmp( str, "4294967196") != 0 )
    return "the unsigned int string did not match the value's data";

  return NULL;
}

const char *
test_outside_access
( void )
{
  long *num_list;
  Value *value;

  value = malloc( sizeof( Value ) );
  if( !value )
    return "the test value could not be created";

  num_list = malloc( sizeof( float ) * 7 );
  if( !num_list )
    return "the test array could not be created";

  num_list[0] = 4;
  num_list[1] = 7;
  num_list[2] = 3;
  num_list[3] = 666;
  num_list[4] = 0;
  num_list[5] = 5;
  num_list[6] = 45;

  value->l_p = num_list;

  num_list[2] = 4;

  if( value->l_p[2] != 4 )
    return "the array held by the value could not be modified from the outside";

  return NULL;
}

const char *
test_to_string( void )
{
  char *str;
  Value *value;

  value = BuildIntValue();

  if( !value )
    return "the test value could not be created";

  str = ValueToString( NULL );
  if( str )
    return "a null value did not create a null string";

  str = ValueToString( value );
  if( !str )
    return "a valid value returned a null string";

  if( !strstr( str, "45678" ) )
    return "the string did not contain the value's contents";

  return NULL;
}
