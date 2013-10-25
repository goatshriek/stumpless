#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/filter_list.h"
#include "private/filter_list_static.h"
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
  FilterList * list = NewFilterList();
  if( list == NULL )
    return "the list was not created";
  
  Filter * filter_1 = BuildFilter();
  filter_1->name = "first test filter";
  
  Filter * filter_2 = BuildFilter();
  filter_2->name = "second test filter";
  
  Filter * filter_3 = BuildFilter();
  filter_3->name = "third test filter";
  
  Filter * filter_4 = BuildFilter();
  filter_4->name = "fourth test filter";
  
  status = AppendToFilterList( list, filter_1 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToFilterList( list, filter_2 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToFilterList( list, filter_3 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToFilterList( list, filter_4 );
  if( status != NULL )
    return "the node was not successfully added";
  
  Filter * filter = BeginFilterList( list );
  FAIL_IF_NULL( filter, "the list did not have a first node" )
  if( filter != filter_1 )
    return "the first filter was not correct";
  
  return NULL;
}

const char *
test_begin
( void )
{
  FilterList * list = BuildFilterList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Filter * filter = BeginFilterList( list );
  FAIL_IF_NULL( filter, "a filter was returned from a newly-constructed list" )
  
  return NULL;
}

const char *
test_constructor
( void )
{
  FilterList * list = NULL;
  
  list = NewFilterList();
  
  if( list == NULL )
    return "the list was not created";
  
  Filter * filter = BeginFilterList( list );
  FAIL_IF_NOT_NULL( filter, "a newly-constructed list already had members" )
  
  return NULL;
}

const char *
test_copy
( void )
{
  FilterList * list = BuildFilterList();
  if( list == NULL )
    return "could not build the test list";
  
  FilterList * copy;
  
  copy = CopyFilterList( NULL );
  if( copy != NULL )
    return "the copy was not null for a null pointer";
  
  copy = CopyFilterList( list );
  FAIL_IF_NULL( copy, "the copy was null for a non-null pointer" )
  if( copy == list )
    return "the copy was equal to the original list";
  
  Filter * original_filter = BeginFilterList( list );
  Filter * copy_filter = BeginFilterList( copy );
  while( original_filter != NULL ){
    if( original_filter != copy_filter )
      return "the copy was not an accurate copy of the original";
    original_filter = NextInFilterList( list );
    copy_filter = NextInFilterList( copy );
  }
  
  return NULL;
}

const char *
test_destructor
( void )
{
  FilterList * list = NewFilterList();
  
  if( list == NULL )
    return "the list was not created";
  
  DestroyFilterList( list );
  
  list = BuildFilterList();
  if( list == NULL )
     return "could not build the test list";
  
  DestroyFilterList( list );
  
  return NULL;
}

const char *
test_is_empty( void )
{
  FilterList * list = NULL;
  if( !FilterListIsEmpty( list ) )
    return "a null list pointer was deemed empty";
  
  list = NewFilterList();
  if( !FilterListIsEmpty( list ) )
    return "a newly created list pointer was not deemed empty";
  
  list = BuildFilterList();
  if( list == NULL )
    return "could not build the test list";
  if( FilterListIsEmpty( list ) )
    return "a full list was deemed empty";
  
  return NULL;
}

const char *
test_next
( void )
{
  FilterList * list = BuildFilterList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Filter * filter = BeginFilterList( list );
  FAIL_IF_NULL( filter, "a filter was not returned from the start call" )
  
  filter = NextInFilterList( list );
  FAIL_IF_NULL( filter, "a filter was not returned from the next call" )
  
  return NULL;
}

const char *
test_prepender( void )
{
  FilterList * list = NewFilterList();
  FAIL_IF_NULL( list, "could not build a new test list" )
  
  Filter * filter = BuildFilter();
  FAIL_IF_NULL( list, "could not build the test filter" );
  
  Status * status = PrependToFilterList( NULL, NULL );
  FAIL_IF_NULL( status, "two empty arguments did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "two empty arguments did not generate the appropriate status code" )
  
  status = PrependToFilterList( list, NULL );
  FAIL_IF_NULL( status, "an empty value did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty value did not generate the appropriate status code" )
  
  status = PrependToFilterList( NULL, filter );
  FAIL_IF_NULL( status, "a NULL list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a NULL list did not generate the appropriate status code" )
 
  status = PrependToFilterList( list, filter );
  FAIL_IF_NOT_NULL( status, "a value could not be prepended to an empty list" )
  Filter * retrieved_filter = BeginFilterList( list );
  FAIL_IF_NULL( retrieved_filter, "the list's nodes were invalid" )
  if( retrieved_filter != filter )
    return "the filter was not actually prepended to the list";
  
  list = BuildFilterList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  filter = BuildFilter();
  FAIL_IF_NULL( list, "could not build a test filter" )
  status = PrependToFilterList( list, filter );
  FAIL_IF_NOT_NULL( status, "the filter was not correctly prepended to a populated list" )
  retrieved_filter = BeginFilterList( list );
  FAIL_IF_NULL( retrieved_filter, "a populated list had its members removed" )
  if( retrieved_filter != filter )
    return "the filter was not actually prepended to a full list";
  
  return NULL;
}
