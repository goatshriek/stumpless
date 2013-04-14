#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "helper.h"

const char * test_copy( void );
const char * test_destructive_write( void );
const char * test_list_appender( void );
const char * test_list_constructor( void );
const char * test_list_destructor( void );
const char * test_into_string( void );
const char * test_is_empty( void );
const char * test_stream_write( void );
const char * test_string_appender( void );
const char * test_to_string( void );
const char * test_unsigned_int_appender( void );
const char * test_value_appender( void );

StumplessValueList * GetTestList( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_copy();
  if( result != NULL ){
    printf( "Copy Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_destructive_write();
  if( result != NULL ){
    printf( "Destructive Write Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_list_appender();
  if( result != NULL ){
    printf( "List Appender Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_list_constructor();
  if( result != NULL ){
    printf( "List Constructor Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_list_destructor();
  if( result != NULL ){
    printf( "List Destrutor Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_into_string();
  if( result != NULL ){
    printf( "Write Into String Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_is_empty();
  if( result != NULL ){
    printf( "Is Empty Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_stream_write();
  if( result != NULL ){
    printf( "Stream Write Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_string_appender();
  if( result != NULL ){
    printf( "String Appender Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_unsigned_int_appender();
  if( result != NULL ){
    printf( "Unsigned Appender Test Failed: %s\n", result );
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
test_copy( void )
{
  StumplessValueList * list = GetTestList();
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
test_destructive_write( void )
{
  StumplessStatusCode status;
  
  status = StumplessWriteAndDestroyValueList( NULL, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a null file did not generate the correct error";
  
  status = StumplessWriteAndDestroyValueList( stdout, NULL );
  if( status != STUMPLESS_EMPTY_ARGUMENT )
    return "a null file did not generate the correct error";
  
  StumplessValueList * list = GetTestList();
  if( list == NULL )
    return "the test list could not be created";
  
  status = StumplessWriteAndDestroyValueList( stdout, list );
  if( status != STUMPLESS_SUCCESS )
    return "the list was not correctly written to the output";
  
  return NULL;
}

const char *
test_list_appender( void )
{
  StumplessStatusCode status;
  
  StumplessValueList * list_1 = GetTestList();
  if( list_1 == NULL )
    return "the first test list could not be created";

  StumplessValueList * list_2 = GetTestList();
  if( list_2 == NULL )
    return "the second test list could not be created";
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
test_list_constructor( void )
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
test_list_destructor( void )
{
  StumplessValueList * list = StumplessNewValueList();
  
  if( list == NULL )
    return "the list was not created";
  
  StumplessDestroyValueList( list );
  
  list = GetTestList();
  
  if( list == NULL )
     return "the list was not created";
  
  StumplessDestroyValueList( list );
  
  return NULL;
}

const char *
test_into_string( void )
{
  StumplessValueList * list = GetTestList();
  if( list == NULL )
    return "the test list could not be created";
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
  
  if( strstr( str, "testing" ) == NULL )
    return "the new string did not contain the list strings";
  
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
  
  list = GetTestList();
  if( StumplessValueListIsEmpty( list ) )
    return "a full list was deemed empty";
  
  return NULL;
}

const char *
test_stream_write( void )
{
  StumplessValueList * list = GetTestList();
  if( list == NULL )
    return "the test list could not be created";
  
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
  
  StumplessValueList * list = GetTestList();
  if( list == NULL )
    return "the test list could not be created";
  
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
test_to_string( void )
{
  StumplessValueList * list = GetTestList();
  if( list == NULL )
    return "the test list could not be created";
  char * str;
  
  str = StumplessValueListToString( NULL );
  if( str != NULL )
    return "a null list did not return a null string";
  
  str = StumplessValueListToString( list );
  if( str == NULL )
    return "a valid list returend a null string";
  
  if( strstr( str, "testing" ) == NULL )
    return "the new string did not contain the list strings";
  
  return NULL;
}

const char *
test_unsigned_int_appender( void )
{
  StumplessValueList * list = GetTestList();
  if( list == NULL )
    return "the test list could not be created";
  
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

StumplessValueList *
GetTestList( void )
{
  StumplessStatusCode status;
  StumplessValueList * list = StumplessNewValueList();
  if( list == NULL )
    return NULL;
  
  StumplessValue * val_1 = StumplessValueFromString( "test" );
  StumplessValue * val_2 = StumplessValueFromString( "string" );
  StumplessValue * val_3 = StumplessValueFromString( "tor" );
  StumplessValue * val_4 = StumplessValueFromString( "testing" );
  
  status = StumplessAppendValueToValueList( list, val_1 );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  status = StumplessAppendValueToValueList( list, val_2 );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  status = StumplessAppendValueToValueList( list, val_3 );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  status = StumplessAppendValueToValueList( list, val_4 );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  return list;
}
