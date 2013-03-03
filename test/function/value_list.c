#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_destructive_write( void );
const char * test_list_appender( void );
const char * test_list_constructor( void );
const char * test_list_destructor( void );
const char * test_is_empty( void );
const char * test_stream_write( void );
const char * test_string_appender( void );

StumplessValueList * GetTestList( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_destructive_write();
  if( result != NULL ){
    printf( "Destructive Write Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_list_constructor();
  if( result != NULL ){
    printf( "List Constructor Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_list_appender();
  if( result != NULL ){
    printf( "Append to List Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_list_destructor();
  if( result != NULL ){
    printf( "List Destrutor Test Failed: %s\n", result );
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
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
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
  StumplessValueList * list = StumplessNewValueList();
  if( list == NULL )
    return "the list was not created";
  
  StumplessValue * val_1 = StumplessValueFromString( "test" );
  StumplessValue * val_2 = StumplessValueFromString( "string" );
  StumplessValue * val_3 = StumplessValueFromString( "tor" );
  StumplessValue * val_4 = StumplessValueFromString( "testing" );
  
  status = StumplessAppendToValueList( list, val_1 );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  status = StumplessAppendToValueList( list, val_2 );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  status = StumplessAppendToValueList( list, val_3 );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  status = StumplessAppendToValueList( list, val_4 );
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
  
  status = StumplessAppendToValueList( list, val_1 );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  status = StumplessAppendToValueList( list, val_2 );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  status = StumplessAppendToValueList( list, val_3 );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  status = StumplessAppendToValueList( list, val_4 );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  
  return list;
}
