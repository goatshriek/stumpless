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
  StumplessValueList * list = StumplessGetNewStringList();
  
  status = StumplessAppendToValueList( list, "test" );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  status = StumplessAppendToValueList( list, "string" );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  status = StumplessAppendToValueList( list, "for" );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  status = StumplessAppendToValueList( list, "testing" );
  if( status != STUMPLESS_SUCCESS )
    return "the node was not successfully added";
  
  if( strcmp( list->first->str, "test" ) != 0 )
    return "the first string was not correct";
  
  if( strcmp( list->last->str, "testing" ) != 0 )
    return "the last string was not correct";
  
  return NULL;
}

const char *
test_list_constructor( void )
{
  StumplessValueList * list = NULL;
  
  list = StumplessGetNewValueList();
  
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
  return NULL;
}
