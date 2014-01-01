#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/comparator_list.h"
#include "private/static/comparator_list.h"
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
const char * test_run( void );

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
  RUN_TEST( run )
  
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
  ComparatorList * list = NewComparatorList();
  if( list == NULL )
    return "the list was not created";
  
  Comparator * comparator_1 = BuildComparator();
  comparator_1->name = "first test comparator";
  
  Comparator * comparator_2 = BuildComparator();
  comparator_2->name = "second test comparator";
  
  Comparator * comparator_3 = BuildComparator();
  comparator_3->name = "third test comparator";
  
  Comparator * comparator_4 = BuildComparator();
  comparator_4->name = "fourth test comparator";
  
  status = AppendToComparatorList( list, comparator_1 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToComparatorList( list, comparator_2 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToComparatorList( list, comparator_3 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToComparatorList( list, comparator_4 );
  if( status != NULL )
    return "the node was not successfully added";
  
  Comparator * comparator = BeginComparatorList( list );
  FAIL_IF_NULL( comparator, "the list did not have a first node" )
  if( comparator != comparator_1 )
    return "the first comparator was not correct";
  
  return NULL;
}

const char *
test_begin
( void )
{
  ComparatorList * list = BuildComparatorList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Comparator * comparator = BeginComparatorList( list );
  FAIL_IF_NULL( comparator, "a comparator was returned from a newly-constructed list" )
  
  return NULL;
}

const char *
test_constructor
( void )
{
  ComparatorList * list = NULL;
  
  list = NewComparatorList();
  
  if( list == NULL )
    return "the list was not created";
  
  Comparator * comparator = BeginComparatorList( list );
  FAIL_IF_NOT_NULL( comparator, "a newly-constructed list already had members" )
  
  return NULL;
}

const char *
test_copy
( void )
{
  ComparatorList * list = BuildComparatorList();
  if( list == NULL )
    return "could not build the test list";
  
  ComparatorList * copy;
  
  copy = CopyComparatorList( NULL );
  if( copy != NULL )
    return "the copy was not null for a null pointer";
  
  copy = CopyComparatorList( list );
  FAIL_IF_NULL( copy, "the copy was null for a non-null pointer" )
  if( copy == list )
    return "the copy was equal to the original list";
  
  Comparator * original_comparator = BeginComparatorList( list );
  Comparator * copy_comparator = BeginComparatorList( copy );
  while( original_comparator != NULL ){
    if( original_comparator != copy_comparator )
      return "the copy was not an accurate copy of the original";
    original_comparator = NextInComparatorList( list );
    copy_comparator = NextInComparatorList( copy );
  }
  
  return NULL;
}

const char *
test_destructor
( void )
{
  ComparatorList * list = NewComparatorList();
  
  if( list == NULL )
    return "the list was not created";
  
  DestroyComparatorList( list );
  
  list = BuildComparatorList();
  if( list == NULL )
     return "could not build the test list";
  
  DestroyComparatorList( list );
  
  return NULL;
}

const char *
test_is_empty
( void )
{
  ComparatorList * list = NULL;
  if( !ComparatorListIsEmpty( list ) )
    return "a null list pointer was deemed empty";
  
  list = NewComparatorList();
  if( !ComparatorListIsEmpty( list ) )
    return "a newly created list pointer was not deemed empty";
  
  list = BuildComparatorList();
  if( list == NULL )
    return "could not build the test list";
  if( ComparatorListIsEmpty( list ) )
    return "a full list was deemed empty";
  
  return NULL;
}

const char *
test_next
( void )
{
  ComparatorList * list = BuildComparatorList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Comparator * comparator = BeginComparatorList( list );
  FAIL_IF_NULL( comparator, "a comparator was not returned from the start call" )
  
  comparator = NextInComparatorList( list );
  FAIL_IF_NULL( comparator, "a comparator was not returned from the next call" )
  
  return NULL;
}

const char *
test_prepender( void )
{
  ComparatorList * list = NewComparatorList();
  FAIL_IF_NULL( list, "could not build a new test list" )
  
  Comparator * comparator = BuildComparator();
  FAIL_IF_NULL( list, "could not build the test comparator" );
  
  Status * status = PrependToComparatorList( NULL, NULL );
  FAIL_IF_NULL( status, "two empty arguments did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "two empty arguments did not generate the appropriate status code" )
  
  status = PrependToComparatorList( list, NULL );
  FAIL_IF_NULL( status, "an empty value did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty value did not generate the appropriate status code" )
  
  status = PrependToComparatorList( NULL, comparator );
  FAIL_IF_NULL( status, "a NULL list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a NULL list did not generate the appropriate status code" )
 
  status = PrependToComparatorList( list, comparator );
  FAIL_IF_NOT_NULL( status, "a value could not be prepended to an empty list" )
  Comparator * retrieved_comparator = BeginComparatorList( list );
  FAIL_IF_NULL( retrieved_comparator, "the list's nodes were invalid" )
  if( retrieved_comparator != comparator )
    return "the comparator was not actually prepended to the list";
  
  list = BuildComparatorList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  comparator = BuildComparator();
  FAIL_IF_NULL( list, "could not build a test comparator" )
  status = PrependToComparatorList( list, comparator );
  FAIL_IF_NOT_NULL( status, "the comparator was not correctly prepended to a populated list" )
  retrieved_comparator = BeginComparatorList( list );
  FAIL_IF_NULL( retrieved_comparator, "a populated list had its members removed" )
  if( retrieved_comparator != comparator )
    return "the comparator was not actually prepended to a full list";
  
  return NULL;
}

const char *
test_run
( void )
{
  // todo finish
  return NULL;
}
