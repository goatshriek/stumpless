#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/compare_base.h"
#include "private/sortable_list.h"
#include "private/sortable_list_static.h"
#include "private/type.h"

#include "helper.h"

const char * test_add_value( void );
const char * test_begin( void );
const char * test_constructor( void );
const char * test_contains( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_is_empty( void );
const char * test_merge( void );
const char * test_next( void );
const char * test_set_comparison( void );
const char * test_set_options( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( add_value )
  RUN_TEST( begin )
  RUN_TEST( constructor )
  RUN_TEST( contains )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( is_empty )
  RUN_TEST( merge )
  RUN_TEST( next )
  RUN_TEST( set_comparison )
  RUN_TEST( set_options )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_value
( void )
{
  SortableList * list = BuildSortableListOfStrings();
  FAIL_IF_NULL( list, "the test list could not be built" );
  ASSERT_STRINGS_EQUAL( "third", list->last->value, "the last part of the list was not what it was expected to be before the appending" )
  
  char * str = "sucka";
  SortableList * result = AddToSortableList( list, ( void * ) str );
  FAIL_IF_NULL( result, "the addition was not successfull" )
  
  char * next = BeginSortableList( list );
  FAIL_IF_NULL( next, "could not get the first list member" )
  ASSERT_STRINGS_EQUAL( "first", next, "the first element was not correct" )
  
  next = NextInSortableList( list );
  FAIL_IF_NULL( next, "could not get the second list member" )
  ASSERT_STRINGS_EQUAL( "second", next, "the second element was not correct" )
  
  next = NextInSortableList( list );
  FAIL_IF_NULL( next, "could not get the third list member" )
  ASSERT_STRINGS_EQUAL( "sucka", next, "the third element was not correct (the list was not sorted)" )
  
  next = NextInSortableList( list );
  FAIL_IF_NULL( next, "could not get the fourth list member" )
  ASSERT_STRINGS_EQUAL( "third", next, "the fourth element was not correct" )
  
  FAIL_IF_NOT_NULL( NextInSortableList( list ), "there were extra elements added" )
  
  FAIL_IF_NULL( SetSortableListComparison( list, NULL ), "could not change the comparison function" )
  FAIL_IF_NOT_NULL( AddToSortableList( list, ( void * ) str ), "addition without a comparison function was allowed" )
  
  return NULL;
}

const char *
test_begin
( void )
{
  SortableList * list = NewSortableList();
  FAIL_IF_NULL( list, "a new list could not be built" );
  
  const char * value = BeginSortableList( list );
  FAIL_IF_NOT_NULL( value, "an empty list returned a value first" )
  
  list = BuildSortableListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  value = BeginSortableList( list );
  FAIL_IF_NULL( value, "a value was not returned from the list" )
  if( value != list->first->value )
    return "the first element of the list was not returned";
  
  return NULL;
}

const char *
test_constructor
( void )
{
  SortableList * list = NULL;
  
  list = NewSortableList();
  
  FAIL_IF_NULL( list, "the list was not created" )
  FAIL_IF_NOT_NULL( list->compare, "the list had a comparison function" )
  FAIL_IF_NOT_NULL( list->first, "the list had a node already in it" )
  FAIL_IF_NOT_NULL( list->last, "the list was not properly formed" )
  
  return NULL;
}

const char *
test_contains
( void )
{
  SortableList * list = BuildSortableListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  void * value = BeginSortableList( list );
  FAIL_IF_NULL( value, "could not get the first list member" )
  
  if( !SortableListContains( list, value ) )
    return "the list did not contain a value pulled from the beginning";
  
  value = NextInSortableList( list );
  if( !SortableListContains( list, value ) )
    return "the list did not contain a value pulled from the middle";
  
  value = "not in the list";
  if( SortableListContains( list, value ) )
    return "the list contained a value not held in it";
  
  AddToSortableList( list, value );
  if( !SortableListContains( list, value ) )
    return "the list did not contain a value added to it";
  
  return NULL;
}

const char *
test_copy
( void )
{
  SortableList * list = BuildSortableListOfStrings();
  if( list == NULL )
    return "could not build the test list";
  
  SortableList * copy;
  
  copy = CopySortableList( NULL );
  if( copy != NULL )
    return "the copy was not null for a null pointer";
  
  copy = CopySortableList( list );
  if( copy == NULL )
    return "the copy was null for a non-null pointer";
  if( copy == list )
    return "the copy was equal to the original list";
  if( copy->compare != list->compare )
    return "the same comparison function was not used";
  if( copy->first == NULL )
    return "the copy did not actually contain any information";
  if( copy->first == list->first )
    return "the copy's nodes were the same instead of a copy";
  if( copy->first->value != list->first->value )
    return "the copy did not have the same values";
  // todo add tests for option copying
  
  return NULL;
}

const char *
test_destructor( void )
{
  SortableList * list = NewSortableList();
  
  if( list == NULL )
    return "the list was not created";
  
  DestroySortableList( list );
  
  list = BuildSortableListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  DestroySortableList( list );
  
  return NULL;
}

const char *
test_is_empty( void )
{
  SortableList * list = NULL;
  if( !SortableListIsEmpty( list ) )
    return "a null list pointer was deemed empty";
  
  list = NewSortableList();
  if( !SortableListIsEmpty( list ) )
    return "a newly created list pointer was not deemed empty";
  
  list = BuildSortableListOfStrings();
  if( list == NULL )
    return "could not build the test list";
  if( SortableListIsEmpty( list ) )
    return "a full list was deemed empty";
  
  // todo add tests for a full list made empty
  
  return NULL;
}

const char *
test_merge
( void )
{
  SortableList * list_1 = BuildSortableListOfStrings();
  FAIL_IF_NULL( list_1, "could not build the first list" )

  SortableList * list_2 = BuildSortableListOfStrings();
  FAIL_IF_NULL( list_2, "could not build the second list" )
  
  const char * first = "AAA: this should be first";
  SortableList * result = AddToSortableList( list_2, ( void * ) first );
  FAIL_IF_NULL( result, "an extra value could not be added to the second list" )
  
  const char * last = "ZZZ: this should be last";
  result = AddToSortableList( list_1, ( void * ) last );
  FAIL_IF_NULL( result, "an extra value could not be added to the first list" )
  
  result = MergeSortableLists( NULL, NULL );
  FAIL_IF_NOT_NULL( result, "empty arguments did not cause an error" )
  
  result = MergeSortableLists( NULL, list_2 );
  FAIL_IF_NOT_NULL( result, "an empty first argument did not cause an error" )
  
  result = MergeSortableLists( list_1, NULL );
  FAIL_IF_NULL( result, "the list was not successfully merged with nothing" )
  ASSERT_STRINGS_EQUAL( last, list_1->last->value, "the last value disappeared" )
  
  result = MergeSortableLists( list_1, list_2 );
  FAIL_IF_NULL( result, "the list was not successfully appended" )
  ASSERT_STRINGS_EQUAL( first, list_1->first->value, "the lists were not properly merged" )
  ASSERT_STRINGS_EQUAL( last, list_1->last->value, "the lists were not properly merged" )
  
  return NULL;
}

const char *
test_next
( void )
{
  SortableList * list = BuildSortableListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  const char * value = BeginSortableList( list );
  FAIL_IF_NULL( value, "a value was not returned from the start call" )
  
  value = NextInSortableList( list );
  FAIL_IF_NULL( value, "the next value was not returned" )
  ASSERT_STRINGS_EQUAL( "second", value, "the next value in the list was not returned" )
  
  value = NextInSortableList( list );
  FAIL_IF_NULL( value, "the next value was not returned" )
  ASSERT_STRINGS_EQUAL( "third", value, "the next value in the list was not returned" )
  
  value = NextInSortableList( list );
  FAIL_IF_NOT_NULL( value, "a value beyond the last was returned" )
  
  return NULL;
}

const char *
test_set_comparison
( void )
{
  SortableList * list = NewSortableList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  FAIL_IF_NOT_NULL( list->compare, "a new list had a comparison function" )
  
  FAIL_IF_NULL( SetSortableListComparison( list, CompareStrings ), "the list comparison could not be set" )
  if( list->compare != CompareStrings )
    return "the list comparison was not actually set";
  
  // todo add test to make sure that a re-sort is done
  
  return NULL;
}

const char *
test_set_options
( void )
{
  SortableList * list = NewSortableList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  FAIL_IF_NOT_NULL( list->options, "a new list had options" )
  
  Dictionary * options = BuildDictionaryOfStrings();
  FAIL_IF_NULL( options, "could not build the test dictionary" )
  
  FAIL_IF_NULL( SetSortableListOptions( list, options ), "could not set the options of a list" )
  if( list->options != options )
    return "the options of the list were not actually set";
  
  return NULL;
}
