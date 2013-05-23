#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "helper.h"

const char * test_appender( void );
const char * test_constructor( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_into_string( void );
const char * test_is_empty( void );
const char * test_prepender( void );
const char * test_separator( void );
const char * test_stream_write( void );
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
  RUN_TEST( stream_write )
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
  StumplessStatusCode status;
  
  StumplessValueList * list_1 = BuildValueList();
  if( list_1 == NULL )
    return "could not build the first list";

  StumplessValueList * list_2 = BuildValueList();
  if( list_2 == NULL )
    return "could not build the second list";
  status = StumplessAppendStringToValueList( list_2, "this should be last" );
  if( status != STUMPLESS_SUCCESS )
    return "an extra value could not be added to the second list";
  
  status = StumplessAppendValueLists( NULL, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "empty arguments did not generate the appropriate error";
  
  status = StumplessAppendValueLists( list_1, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty first argument did not generate the appropriate error";
  
  status = StumplessAppendValueLists( NULL, list_2 );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty second argument did not generate the appropriate error";
  
  status = StumplessAppendValueLists( list_1, list_2 );
  if( status != STUMPLESS_SUCCESS )
    return "the list was not successfully appended";
  if( strcmp( list_1->last->value->data->c_p, "this should be last" ) != 0 )
    return "the lists were not properly appended";
  
  return NULL;
}

const char *
test_constructor( void )
{
  StumplessValueList * list = NULL;
  
  list = StumplessNewValueList();
  
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
  StumplessValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  
  StumplessValueList * copy;
  
  copy = StumplessCopyValueList( NULL );
  if( copy != NULL )
    return "the copy was not null for a null pointer";
  
  copy = StumplessCopyValueList( list );
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
  StumplessValueList * list = StumplessNewValueList();
  
  if( list == NULL )
    return "the list was not created";
  
  StumplessDestroyValueList( list );
  
  list = BuildValueList();
  if( list == NULL )
     return "could not build the test list";
  
  StumplessDestroyValueList( list );
  
  return NULL;
}

const char *
test_into_string( void )
{
  StumplessValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  char str[1000];
  
  StumplessStatusCode status = StumplessValueListIntoString( NULL, list );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty string did not generate the correct error";
  
  status = StumplessValueListIntoString( str, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
     return "an empty list did not generate the correct error";
  
  status = StumplessValueListIntoString( str, list );
  if( status != STUMPLESS_SUCCESS )
    return "a valid string was not properly written into";
  
  if( strstr( str, "234567" ) == NULL )
    return "the new string did not contain parts of the list";
  
  return NULL;
}

const char *
test_is_empty( void )
{
  StumplessValueList * list = NULL;
  if( !StumplessValueListIsEmpty( list ) )
    return "a null list pointer was deemed empty";
  
  list = StumplessNewValueList();
  if( !StumplessValueListIsEmpty( list ) )
    return "a newly created list pointer was not deemed empty";
  
  list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  if( StumplessValueListIsEmpty( list ) )
    return "a full list was deemed empty";
  
  return NULL;
}

const char *
test_prepender( void )
{
  StumplessValueList * list = StumplessNewValueList();
  FAIL_IF_NULL( list, "could not build a new test list" )
  
  StumplessValue * value = BuildIntValue();
  FAIL_IF_NULL( list, "could not build the test value" );
  
  StumplessStatusCode status = StumplessPrependValueToValueList( NULL, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "two empty arguments did not generate the appropriate status code";
  
  status = StumplessPrependValueToValueList( list, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty value did not generate the appropriate status code";
  
  status = StumplessPrependValueToValueList( NULL, value );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a NULL list did not generate the approprate status code";
 
  status = StumplessPrependValueToValueList( list, value );
  if( status != STUMPLESS_SUCCESS )
    return "a value could not be prepended to an empty list";
  FAIL_IF_NULL( list->first, "the list still did not have any members" )
  FAIL_IF_NULL( list->first->value, "the list's nodes were invalid" )
  if( list->first->value != value )
    return "the value was not actually prepended to the list";
  
  list = BuildValueList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  value = BuildIntArrayValue();
  FAIL_IF_NULL( list, "could not build a test array value" )
  status = StumplessPrependValueToValueList( list, value );
  if( status != STUMPLESS_SUCCESS )
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
  StumplessValueList * list = BuildValueListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  StumplessValue * separator = StumplessValueFromString( ", " );
  FAIL_IF_NULL( separator, "could not build the test separator value" )
  
  StumplessStatusCode status;
  status = StumplessAddSeparatorToValueList( list, separator );
  if( status != STUMPLESS_SUCCESS )
    return "the separator was not properly added to the list";
  
  char * test_str = StumplessValueListToString( list );
  FAIL_IF_NULL( test_str, "the list could not be converted to a string" )
  printf( "\n%s\n", test_str );
  if( strcmp( test_str, "this, is, a, test, list" ) != 0 )
    return "the separator was not added between all elements of the list";
  
  return NULL;
}

const char *
test_stream_write( void )
{
  StumplessValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  
  StumplessStatusCode status = StumplessWriteValueListToStream( stdout, list );
  if( status != STUMPLESS_SUCCESS )
    return "the list was not correctly written to the output";
  
  return NULL;
}

const char *
test_string_appender( void )
{
  StumplessStatusCode status;
  status = StumplessAppendStringToValueList( NULL, "str" );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty list did not generate the correct error";
  
  StumplessValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  
  status = StumplessAppendStringToValueList( list, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "an empty string did not generate the correct error";
  
  status = StumplessAppendStringToValueList( list, "str" );
  if( status != STUMPLESS_SUCCESS )
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
  StumplessValueList * list = StumplessNewValueList();
  FAIL_IF_NULL( list, "could not build a new test list" )
  
  StumplessStatusCode status = StumplessPrependStringToValueList( NULL, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "two empty arguments did not generate the appropriate status code";
  
  status = StumplessPrependStringToValueList( list, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a null string did not generate the appropriate status code";
  
  status = StumplessPrependStringToValueList( NULL, "shouldn't work" );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a NULL list did not generate the approprate status code";
  
  status = StumplessPrependStringToValueList( list, "lonely little guy" );
  if( status != STUMPLESS_SUCCESS )
    return "a string could not be prepended to an empty list";
  FAIL_IF_NULL( list->first, "the list still did not have any members" )
  FAIL_IF_NULL( list->first->value, "the list's nodes were invalid" )
  FAIL_IF_NULL( list->first->value->data, "the new value did not have any data" )
  if( list->first->value->type != STUMPLESS_STRING )
    return "the new value was not a string";
  if( strcmp( list->first->value->data->c_p, "lonely little guy" ) != 0 )
    return "the new string was not equivalent to the added one";
  
  list = BuildValueList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  status = StumplessPrependStringToValueList( list, "new beginning" );
  if( status != STUMPLESS_SUCCESS )
    return "the string was not correctly prepended to a populated list";
  FAIL_IF_NULL( list->first, "a populated list had it's members removed" );
  FAIL_IF_NULL( list->first->value, "the new element did not have a value" )
  FAIL_IF_NULL( list->first->value->data, "the new value did not have any data" )
  if( list->first->value->type != STUMPLESS_STRING )
    return "the new value was not a string";
  if( strcmp( list->first->value->data->c_p, "new beginning" ) != 0 )
    return "the new string was not equivalent to the added one";
  
  return NULL;
}

const char *
test_to_string( void )
{
  StumplessValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  char * str;
  
  str = StumplessValueListToString( NULL );
  if( str != NULL )
    return "a null list did not return a null string";
  
  str = StumplessValueListToString( list );
  if( str == NULL )
    return "a valid list returend a null string";
  
  if( strstr( str, "3456789" ) == NULL )
    return "the new string did not contain parts of the list";
  
  return NULL;
}

const char *
test_unsigned_int_appender( void )
{
  StumplessValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";
  
  StumplessStatusCode status;
  status = StumplessAppendUnsignedIntToValueList( NULL, 3 );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a null list did not generate the proper error";
  
  status = StumplessAppendUnsignedIntToValueList( list, 4 );
  if( status != STUMPLESS_SUCCESS )
    return "an unsigned number was not correctly appended to the list";
  
  if( list->last->value->type != STUMPLESS_UNSIGNED_INT )
    return "the new value was not an unsigned int";
  if( list->last->value->data->u_i != 4 )
    return "the new value did not have the intended value";
  
  return NULL;
}

const char *
test_value_appender( void )
{
  StumplessStatusCode status;
  StumplessValueList * list = StumplessNewValueList();
  if( list == NULL )
    return "the list was not created";
  
  StumplessValue * val_1 = StumplessValueFromString( "test" );
  StumplessValue * val_2 = StumplessValueFromString( "string" );
  StumplessValue * val_3 = StumplessValueFromString( "tor" );
  StumplessValue * val_4 = StumplessValueFromString( "testing" );
  
  status = StumplessAppendValueToValueList( list, val_1 );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  status = StumplessAppendValueToValueList( list, val_2 );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  status = StumplessAppendValueToValueList( list, val_3 );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  status = StumplessAppendValueToValueList( list, val_4 );
  if( status != STUMPLESS_SUCCESS )
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
