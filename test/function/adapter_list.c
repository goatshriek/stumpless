#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/adapter_list.h"
#include "private/adapter_list_static.h"
#include "private/type.h"

#include "helper.h"

const char * test_appender( void );
const char * test_begin( void );
const char * test_constructor( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_is_empty( void );
const char * test_next( void );
const char * test_prepender( void );
const char * test_value_through( void );

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
  RUN_TEST( is_empty )
  RUN_TEST( next )
  RUN_TEST( prepender )
  RUN_TEST( value_through )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_appender
( void )
{
  Status * status;
  AdapterList * list = NewAdapterList();
  if( list == NULL )
    return "the list was not created";
  
  Adapter * adapter_1 = BuildAdapter();
  adapter_1->name = "first test adapter";
  
  Adapter * adapter_2 = BuildAdapter();
  adapter_2->name = "second test adapter";
  
  Adapter * adapter_3 = BuildAdapter();
  adapter_3->name = "third test adapter";
  
  Adapter * adapter_4 = BuildAdapter();
  adapter_4->name = "fourth test adapter";
  
  status = AppendToAdapterList( list, adapter_1 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToAdapterList( list, adapter_2 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToAdapterList( list, adapter_3 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToAdapterList( list, adapter_4 );
  if( status != NULL )
    return "the node was not successfully added";
  
  Adapter * adapter = BeginAdapterList( list );
  FAIL_IF_NULL( adapter, "the list did not have a first node" )
  if( adapter != adapter_1 )
    return "the first adapter was not correct";
  
  return NULL;
}

const char *
test_begin
( void )
{
  AdapterList * list = BuildAdapterList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Adapter * adapter = BeginAdapterList( list );
  FAIL_IF_NULL( adapter, "a adapter was returned from a newly-constructed list" )
  
  return NULL;
}

const char *
test_constructor
( void )
{
  AdapterList * list = NULL;
  
  list = NewAdapterList();
  
  if( list == NULL )
    return "the list was not created";
  
  Adapter * adapter = BeginAdapterList( list );
  FAIL_IF_NOT_NULL( adapter, "a newly-constructed list already had members" )
  
  return NULL;
}

const char *
test_copy
( void )
{
  AdapterList * list = BuildAdapterList();
  if( list == NULL )
    return "could not build the test list";
  
  AdapterList * copy;
  
  copy = CopyAdapterList( NULL );
  if( copy != NULL )
    return "the copy was not null for a null pointer";
  
  copy = CopyAdapterList( list );
  FAIL_IF_NULL( copy, "the copy was null for a non-null pointer" )
  if( copy == list )
    return "the copy was equal to the original list";
  
  Adapter * original_adapter = BeginAdapterList( list );
  Adapter * copy_adapter = BeginAdapterList( copy );
  while( original_adapter != NULL ){
    if( original_adapter != copy_adapter )
      return "the copy was not an accurate copy of the original";
    original_adapter = NextInAdapterList( list );
    copy_adapter = NextInAdapterList( copy );
  }
  
  return NULL;
}

const char *
test_destructor
( void )
{
  AdapterList * list = NewAdapterList();
  
  if( list == NULL )
    return "the list was not created";
  
  DestroyAdapterList( list );
  
  list = BuildAdapterList();
  if( list == NULL )
     return "could not build the test list";
  
  DestroyAdapterList( list );
  
  return NULL;
}

const char *
test_is_empty
( void )
{
  AdapterList * list = NULL;
  if( !AdapterListIsEmpty( list ) )
    return "a null list pointer was deemed empty";
  
  list = NewAdapterList();
  if( !AdapterListIsEmpty( list ) )
    return "a newly created list pointer was not deemed empty";
  
  list = BuildAdapterList();
  if( list == NULL )
    return "could not build the test list";
  if( AdapterListIsEmpty( list ) )
    return "a full list was deemed empty";
  
  return NULL;
}

const char *
test_next
( void )
{
  AdapterList * list = BuildAdapterList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Adapter * adapter = BeginAdapterList( list );
  FAIL_IF_NULL( adapter, "a adapter was not returned from the start call" )
  
  adapter = NextInAdapterList( list );
  FAIL_IF_NULL( adapter, "a adapter was not returned from the next call" )
  
  return NULL;
}

const char *
test_prepender( void )
{
  AdapterList * list = NewAdapterList();
  FAIL_IF_NULL( list, "could not build a new test list" )
  
  Adapter * adapter = BuildAdapter();
  FAIL_IF_NULL( list, "could not build the test adapter" );
  
  Status * status = PrependToAdapterList( NULL, NULL );
  FAIL_IF_NULL( status, "two empty arguments did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "two empty arguments did not generate the appropriate status code" )
  
  status = PrependToAdapterList( list, NULL );
  FAIL_IF_NULL( status, "an empty value did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty value did not generate the appropriate status code" )
  
  status = PrependToAdapterList( NULL, adapter );
  FAIL_IF_NULL( status, "a NULL list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a NULL list did not generate the appropriate status code" )
 
  status = PrependToAdapterList( list, adapter );
  FAIL_IF_NOT_NULL( status, "a value could not be prepended to an empty list" )
  Adapter * retrieved_adapter = BeginAdapterList( list );
  FAIL_IF_NULL( retrieved_adapter, "the list's nodes were invalid" )
  if( retrieved_adapter != adapter )
    return "the adapter was not actually prepended to the list";
  
  list = BuildAdapterList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  adapter = BuildAdapter();
  FAIL_IF_NULL( list, "could not build a test adapter" )
  status = PrependToAdapterList( list, adapter );
  FAIL_IF_NOT_NULL( status, "the adapter was not correctly prepended to a populated list" )
  retrieved_adapter = BeginAdapterList( list );
  FAIL_IF_NULL( retrieved_adapter, "a populated list had its members removed" )
  if( retrieved_adapter != adapter )
    return "the adapter was not actually prepended to a full list";
  
  return NULL;
}

const char *
test_value_through
( void )
{
  return NULL;
}
