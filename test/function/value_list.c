#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/type.h"
#include "private/value_constructor.h"
#include "private/value_list.h"
#include "private/value_list_static.h"

#include "helper.h"

const char * test_appender( void );
const char * test_begin( void );
const char * test_constructor( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_into_string( void );
const char * test_is_empty( void );
const char * test_next( void );
const char * test_prepender( void );
const char * test_separator( void );
const char * test_string_appender( void );
const char * test_string_prepender( void );
const char * test_to_string( void );
const char * test_unsigned_int_appender( void );
const char * test_value_appender( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( appender )
  RUN_TEST( begin )
  RUN_TEST( constructor )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( into_string )
  RUN_TEST( is_empty )
  RUN_TEST( next )
  RUN_TEST( prepender )
  RUN_TEST( separator )
  RUN_TEST( string_appender )
  RUN_TEST( string_prepender )
  RUN_TEST( to_string )
  RUN_TEST( unsigned_int_appender )
  RUN_TEST( value_appender )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_appender( void )
{
  Status * status;
  
  ValueList * list_1 = BuildValueList();
  FAIL_IF_NULL( list_1, "could not build the first list" )

  ValueList * list_2 = BuildValueList();
  FAIL_IF_NULL( list_2, "could not build the second list" )
  
  status = AppendStringToValueList( list_2, "this should be last" );
  FAIL_IF_NOT_NULL( status, "an extra value could not be added to the second list" )
  
  status = AppendValueLists( NULL, NULL );
  FAIL_IF_NULL( status, "empty arguments did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "empty arguments did not generate the appropriate error" )
  
  status = AppendValueLists( list_1, NULL );
  FAIL_IF_NULL( status, "an empty first argument did not generate an abnormaa status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty first argument did not generate the appropriate error" )
  
  status = AppendValueLists( NULL, list_2 );
  FAIL_IF_NULL( status, "an empty second argument did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty second argument did not generate the appropriate error" )
  
  status = AppendValueLists( list_1, list_2 );
  FAIL_IF_NOT_NULL( status, "the list was not successfully appended" )
  
  return NULL;
}

const char *
test_begin
( void )
{
  ValueList * list = BuildValueList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Value * value = BeginValueList( list );
  FAIL_IF_NULL( value, "a value was not returned from the list" )
  
  return NULL;
}

const char *
test_constructor( void )
{
  ValueList * list = NULL;
  
  list = NewValueList();
  
  if( list == NULL )
    return "the list was not created";
  
  Value * value = BeginValueList( list );
  FAIL_IF_NOT_NULL( value, "a newly-constructed list already had members" )
  
  return NULL;
}

const char *
test_copy( void )
{
  ValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  
  ValueList * copy;
  
  copy = CopyValueList( NULL );
  if( copy != NULL )
    return "the copy was not null for a null pointer";
  
  copy = CopyValueList( list );
  FAIL_IF_NULL( copy, "the copy was null for a non-null pointer" )
  if( copy == list )
    return "the copy was equal to the original list";
  
  Value * original_value = BeginValueList( list );
  Value * copy_value = BeginValueList( copy );
  while( original_value != NULL ){
    if( original_value != copy_value )
      return "the copy was not an accurate copy of the original";
    original_value = NextInValueList( list );
    copy_value = NextInValueList( copy );
  }
  
  return NULL;
}

const char *
test_destructor( void )
{
  ValueList * list = NewValueList();
  
  if( list == NULL )
    return "the list was not created";
  
  DestroyValueList( list );
  
  list = BuildValueList();
  if( list == NULL )
     return "could not build the test list";
  
  DestroyValueList( list );
  
  return NULL;
}

const char *
test_into_string
( void )
{
  ValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  char str[1000];
  
  Status * status = ValueListIntoString( NULL, list );
  FAIL_IF_NULL( status, "an empty string did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty string did not generate the correct error" )
  
  status = ValueListIntoString( str, NULL );
  FAIL_IF_NULL( status, "an empty list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty list did not generate the correct error" )
  
  status = ValueListIntoString( str, list );
  if( status != NULL )
    return "a valid string was not properly written into";
  
  if( strstr( str, "4294967196" ) == NULL )
    return "the new string did not contain parts of the list";
  
  return NULL;
}

const char *
test_is_empty( void )
{
  ValueList * list = NULL;
  if( !ValueListIsEmpty( list ) )
    return "a null list pointer was deemed empty";
  
  list = NewValueList();
  if( !ValueListIsEmpty( list ) )
    return "a newly created list pointer was not deemed empty";
  
  list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  if( ValueListIsEmpty( list ) )
    return "a full list was deemed empty";
  
  return NULL;
}

const char *
test_next
( void )
{
  ValueList * list = BuildValueList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Value * value = BeginValueList( list );
  FAIL_IF_NULL( value, "a value was not returned from the start call" )
  
  value = NextInValueList( list );
  FAIL_IF_NULL( value, "a value was not returned from the next call" )
  
  return NULL;
}

const char *
test_prepender( void )
{
  ValueList * list = NewValueList();
  FAIL_IF_NULL( list, "could not build a new test list" )
  
  Value * value = BuildIntValue();
  FAIL_IF_NULL( list, "could not build the test value" );
  
  Status * status = PrependValueToValueList( NULL, NULL );
  FAIL_IF_NULL( status, "two empty arguments did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "two empty arguments did not generate the appropriate status code" )
  
  status = PrependValueToValueList( list, NULL );
  FAIL_IF_NULL( status, "an empty value did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty value did not generate the appropriate status code" )
  
  status = PrependValueToValueList( NULL, value );
  FAIL_IF_NULL( status, "a NULL list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a NULL list did not generate the appropriate status code" )
 
  status = PrependValueToValueList( list, value );
  FAIL_IF_NOT_NULL( status, "a value could not be prepended to an empty list" )
  Value * retrieved_value = BeginValueList( list );
  FAIL_IF_NULL( retrieved_value, "the list's nodes were invalid" )
  if( retrieved_value != value )
    return "the value was not actually prepended to the list";
  
  list = BuildValueList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  value = BuildIntArrayValue();
  FAIL_IF_NULL( list, "could not build a test array value" )
  status = PrependValueToValueList( list, value );
  FAIL_IF_NOT_NULL( status, "the value was not correctly prepended to a populated list" )
  retrieved_value = BeginValueList( list );
  FAIL_IF_NULL( retrieved_value, "a populated list had it's members removed" )
  if( retrieved_value != value )
    return "the value was not actually prepended to a full list";
  
  return NULL;
}

const char *
test_separator( void )
{
  ValueList * list = BuildValueListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Value * separator = ValueFromString( ", " );
  FAIL_IF_NULL( separator, "could not build the test separator value" )
  
  Status * status;
  status = AddSeparatorToValueList( list, separator );
  if( status != NULL )
    return "the separator was not properly added to the list";
  
  char * test_str = ValueListToString( list );
  FAIL_IF_NULL( test_str, "the list could not be converted to a string" )
  ASSERT_STRINGS_EQUAL( "this, is, a, test, list", test_str, "the separator was not added between all elements of the list" )
  
  return NULL;
}

const char *
test_string_appender( void )
{
  Status * status = AppendStringToValueList( NULL, "str" );
  FAIL_IF_NULL( status, "an empty list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty list did not generate the correct error" )
  
  ValueList * list = BuildValueList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  status = AppendStringToValueList( list, NULL );
  FAIL_IF_NULL( status, "an empty string did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty string did not generate the correct error" )
  
  status = AppendStringToValueList( list, "str" );
  FAIL_IF_NOT_NULL( status, "the string was not successfully appended to the list" )
  
  return NULL;
}

const char *
test_string_prepender( void )
{
  ValueList * list = NewValueList();
  FAIL_IF_NULL( list, "could not build a new test list" )
  
  Status * status = PrependStringToValueList( NULL, NULL );
  FAIL_IF_NULL( status, "two empty arguments did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "two empty arguments did not generate the appropriate status code" )
  
  status = PrependStringToValueList( list, NULL );
  FAIL_IF_NULL( status, "a NULL string did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a NULL string did not generate the appropriate status code" )
  
  status = PrependStringToValueList( NULL, "shouldn't work" );
  FAIL_IF_NULL( status, "a NULL list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a NULL list did not generate the appropriate status code" )
  
  status = PrependStringToValueList( list, "lonely little guy" );
  FAIL_IF_NOT_NULL( status, "a string could not be prepended to an empty list" )
  Value * value = BeginValueList( list );
  FAIL_IF_NULL( value, "the list still did not have any members" )
  FAIL_IF_NULL( value->data, "the new value did not have any data" )
  ASSERT_STRINGS_EQUAL( "string", value->profile->name, "the new value was not a string" )
  ASSERT_STRINGS_EQUAL( "lonely little guy", value->data->c_p, "the new string was not equivalent to the added one" )
  
  list = BuildValueList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  status = PrependStringToValueList( list, "new beginning" );
  FAIL_IF_NOT_NULL( status, "the string was not correctly prepended to a populated list" )
  value = BeginValueList( list );
  FAIL_IF_NULL( value, "a populated list had it's members removed" );
  FAIL_IF_NULL( value->data, "the new value did not have any data" )
  ASSERT_STRINGS_EQUAL( "string", value->profile->name, "the new value was not a string" )
  ASSERT_STRINGS_EQUAL( "new beginning", value->data->c_p, "the new string was not equivalent to the added one" )
  
  return NULL;
}

const char *
test_to_string( void )
{
  ValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";

  char * str = ValueListToString( NULL );
  if( str != NULL )
    return "a null list did not return a null string";
  
  str = ValueListToString( list );
  if( str == NULL )
    return "a valid list returend a null string";
  
  if( strstr( str, "4294967196" ) == NULL )
    return "the new string did not contain parts of the list";
  
  return NULL;
}

const char *
test_unsigned_int_appender( void )
{
  ValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  
  Status * status = AppendUnsignedIntToValueList( NULL, 3 );
  FAIL_IF_NULL( status, "a NULL list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a null list did not generate the proper error" )
  
  status = AppendUnsignedIntToValueList( list, 4 );
  FAIL_IF_NOT_NULL( status, "an unsigned number was not correctly appended to the list" )
  
  return NULL;
}

const char *
test_value_appender( void )
{
  Status * status;
  ValueList * list = NewValueList();
  if( list == NULL )
    return "the list was not created";
  
  Value * val_1 = ValueFromString( "test" );
  Value * val_2 = ValueFromString( "string" );
  Value * val_3 = ValueFromString( "tor" );
  Value * val_4 = ValueFromString( "testing" );
  
  status = AppendValueToValueList( list, val_1 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendValueToValueList( list, val_2 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendValueToValueList( list, val_3 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendValueToValueList( list, val_4 );
  if( status != NULL )
    return "the node was not successfully added";
  
  Value * value = BeginValueList( list );
  FAIL_IF_NULL( value, "the list did not have a first node" )
  if( value != val_1 )
    return "the first value was not correct";
  
  return NULL;
}
