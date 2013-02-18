#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_list_appender( void );
const char * test_list_constructor( void );
const char * test_list_destructor( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
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
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
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
  
  StumplessStatusCode status = StumplessDestroyValueList( list );
  if( status != STUMPLESS_SUCCESS )
    return "the list was not completely destroyed";
  
  return NULL;
}
