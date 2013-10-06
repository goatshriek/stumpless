#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/type.h"
#include "private/value_constructor.h"
#include "private/value_list.h"

#include "helper.h"

const char * test_appender( void );
const char * test_constructor( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_into_string( void );
const char * test_is_empty( void );
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
  RUN_TEST( constructor )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( into_string )
  RUN_TEST( is_empty )
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
  if( status != NULL )
    return "the list was not successfully appended";
  if( strcmp( list_1->last->value->data->c_p, "this should be last" ) != 0 )
    return "the lists were not properly appended";
  
  return NULL;
}

const char *
test_constructor( void )
{
  ValueList * list = NULL;
  
  list = NewValueList();
  
  if( list == NULL )
    return "the list was not created";
  
  if( list->first != NULL )
    return "the list had a node already in it";
  
  if( list->last != NULL )
    return "the list was not properly formed";
  
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
  if( copy == NULL )
    return "the copy was null for a non-null pointer";
  if( copy == list )
    return "the copy was equal to the original list";
  if( copy->first == NULL )
    return "the copy did not actually contain any information";
  if( copy->first == list->first )
    return "the copy's nodes were the same instead of a copy";
  if( copy->first->value != list->first->value )
    return "the copy did not have the same values";
  
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
test_into_string( void )
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
  if( status != NULL )
    return "a value could not be prepended to an empty list";
  FAIL_IF_NULL( list->first, "the list still did not have any members" )
  FAIL_IF_NULL( list->first->value, "the list's nodes were invalid" )
  if( list->first->value != value )
    return "the value was not actually prepended to the list";
  
  list = BuildValueList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  value = BuildIntArrayValue();
  FAIL_IF_NULL( list, "could not build a test array value" )
  status = PrependValueToValueList( list, value );
  if( status != NULL )
    return "the value was not correctly prepended to a populated list";
  FAIL_IF_NULL( list->first, "a populated list had it's members removed" );
  FAIL_IF_NULL( list->first->value, "the new element did not have a value" )
  if( list->first->value != value )
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
  if( strcmp( test_str, "this, is, a, test, list" ) != 0 )
    return "the separator was not added between all elements of the list";
  
  return NULL;
}

const char *
test_string_appender( void )
{
  Status * status;
  status = AppendStringToValueList( NULL, "str" );
  FAIL_IF_NULL( status, "an empty list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty list did not generate the correct error" )
  
  ValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  
  status = AppendStringToValueList( list, NULL );
  FAIL_IF_NULL( status, "an empty string did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty string did not generate the correct error" )
  
  status = AppendStringToValueList( list, "str" );
  if( status != NULL )
    return "the string was not successfully appended to the list";
  
  if( list->last == NULL )
    return "the list was empty";
  
  if( list->last->value == NULL )
    return "the list was improperly formed";
  
  if( list->last->value->data == NULL )
    return "the last value was not properly formed";
  
  if( strcmp( list->last->value->data->c_p, "str" ) != 0 )
    return "the list's last member was not the appended string";
  
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
  if( status != NULL )
    return "a string could not be prepended to an empty list";
  FAIL_IF_NULL( list->first, "the list still did not have any members" )
  FAIL_IF_NULL( list->first->value, "the list's nodes were invalid" )
  FAIL_IF_NULL( list->first->value->data, "the new value did not have any data" )
  if( strcmp( list->first->value->profile->name, "string" ) != 0 )
    return "the new value was not a string";
  if( strcmp( list->first->value->data->c_p, "lonely little guy" ) != 0 )
    return "the new string was not equivalent to the added one";
  
  list = BuildValueList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  status = PrependStringToValueList( list, "new beginning" );
  if( status != NULL )
    return "the string was not correctly prepended to a populated list";
  FAIL_IF_NULL( list->first, "a populated list had it's members removed" );
  FAIL_IF_NULL( list->first->value, "the new element did not have a value" )
  FAIL_IF_NULL( list->first->value->data, "the new value did not have any data" )
  if( strcmp( list->first->value->profile->name, "string" ) != 0 )
    return "the new value was not a string";
  if( strcmp( list->first->value->data->c_p, "new beginning" ) != 0 )
    return "the new string was not equivalent to the added one";
  
  return NULL;
}

const char *
test_to_string( void )
{
  ValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  char * str;
  
  str = ValueListToString( NULL );
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
  
  Status * status;
  status = AppendUnsignedIntToValueList( NULL, 3 );
  FAIL_IF_NULL( status, "a NULL list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a null list did not generate the proper error" )
  
  status = AppendUnsignedIntToValueList( list, 4 );
  if( status != NULL )
    return "an unsigned number was not correctly appended to the list";
  
  if( strcmp( list->last->value->profile->name, "unsigned int" ) != 0 )
    return "the new value was not an unsigned int";
  if( list->last->value->data->u_i != 4 )
    return "the new value did not have the intended value";
  
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
  
  if( list->first == NULL )
    return "the list did not have a first node";
  
  if( list->first->value != val_1 )
    return "the first value was not correct";
  
  if( list->last == NULL )
    return "the list did not have a last node";
  
  if( list->last->value != val_4 )
    return "the last value was not correct";
  
  return NULL;
}
