#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/container/list.h"
#include "private/container/list/iterator.h"
#include "private/container/list/reverse_iterator.h"
#include "private/type.h"
#include "static/container/list.h"
#include "test/helper.h"

const char * test_append_value( void );
const char * test_appender( void );
const char * test_back( void );
const char * test_constructor( void );
const char * test_contains( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_front( void );
const char * test_is_empty( void );
const char * test_prepend_value( void );
const char * test_separator( void );
const char * test_size( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  RUN_TEST( append_value )
  RUN_TEST( appender )
  RUN_TEST( back )
  RUN_TEST( constructor )
  RUN_TEST( contains )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( front )
  RUN_TEST( is_empty )
  RUN_TEST( prepend_value )
  RUN_TEST( separator )
  RUN_TEST( size )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_append_value
( void )
{
  List *list, *result;
  void *str;

  list = BuildListOfStrings();
  FAIL_IF_NULL( list, "the test list could not be built" );
  ASSERT_STRINGS_EQUAL( "Strings!", list->last->value, "the last part of the list was not what it was expected to be before the appending" )

  str = ( void * ) "sucka";
  result = AppendToList( list, str );
  ASSERT_STRINGS_EQUAL( "sucka", list->last->value, "the last part of the list was not what was appended" )

  return NULL;
}

const char *
test_appender
( void )
{
  List *list_1, *list_2, *result;

  list_1 = BuildListOfStrings();
  FAIL_IF_NULL( list_1, "could not build the first list" )

  list_2 = BuildListOfStrings();
  FAIL_IF_NULL( list_2, "could not build the second list" )

  result = AppendToList( list_2, "this should be last" );
  FAIL_IF_NULL( result, "an extra value could not be added to the second list" )

  result = AppendLists( NULL, NULL );
  FAIL_IF_NOT_NULL( result, "empty arguments did not cause an error" )

  result = AppendLists( NULL, list_2 );
  FAIL_IF_NOT_NULL( result, "an empty first argument did not cause an error" )

  result = AppendLists( list_1, list_2 );
  FAIL_IF_NULL( result, "the list was not successfully appended" )
  ASSERT_STRINGS_EQUAL( "this should be last", list_1->last->value, "the lists were not properly appended" )

  return NULL;
}

const char *
test_back
( void )
{
  List *list;
  ListReverseIterator *iterator;
  void *value;

  value = ListBack( NULL );
  if( value )
    return "a null list had a back element";

  list = BuildListOfStrings();
  if( !list )
    return "could not build a test list";

  value = ListBack( list );
  iterator = RBeginList( list );
  if( value != NextInListReverseIterator( iterator ) )
    return "the last record in the list was not returned";

  return NULL;
}

const char *
test_constructor
( void )
{
  List *list;

  list = NewList();

  FAIL_IF_NULL( list, "the list was not created" )
  FAIL_IF_NOT_NULL( list->first, "the list had a node already in it" )
  FAIL_IF_NOT_NULL( list->last, "the list was not properly formed" )

  return NULL;
}

const char *
test_contains
( void )
{
  char *value;
  List *list;
  ListIterator *iterator;

  list = BuildListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )

  iterator = BeginList( list );
  value = NextInListIterator( iterator );
  FAIL_IF_NULL( value, "could not get the first list member" )

  if( !ListContains( list, value ) )
    return "the list did not contain a value pulled from the beginning";

  value = NextInListIterator( iterator );
  if( !ListContains( list, value ) )
    return "the list did not contain a value pulled from the middle";

  value = "not in the list";
  if( ListContains( list, value ) )
    return "the list contained a value not held in it";

  AppendToList( list, value );
  if( !ListContains( list, value ) )
    return "the list did not contain a value added to it";

  DestroyListIterator( iterator );

  return NULL;
}

const char *
test_copy
( void )
{
  List *copy, *list;

  list = BuildListOfStrings();
  if( !list )
    return "could not build the test list";

  copy = CopyList( NULL );
  if( copy )
    return "the copy was not null for a null pointer";

  copy = CopyList( list );
  if( !copy )
    return "the copy was null for a non-null pointer";
  if( copy == list )
    return "the copy was equal to the original list";
  if( !copy->first )
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
  List *list;

  DestroyList( NULL );

  list = NewList();

  if( !list )
    return "the list was not created";

  DestroyList( list );

  list = BuildListOfStrings();
  if( !list )
     return "could not build the test list";

  DestroyList( list );

  return NULL;
}

const char *
test_front
( void )
{
  List *list;
  ListIterator *iterator;
  void *value;

  value = ListFront( NULL );
  if( value )
    return "a null list had a front element";

  list = BuildListOfStrings();
  if( !list )
    return "could not build a test list";

  value = ListFront( list );
  iterator = BeginList( list );
  if( value != NextInListIterator( iterator ) )
    return "the first record in the list was not returned";

  return NULL;
}

const char *
test_is_empty
( void )
{
  List *list = NULL;

  if( !ListIsEmpty( list ) )
    return "a null list pointer was deemed empty";

  list = NewList();
  if( !ListIsEmpty( list ) )
    return "a newly created list pointer was not deemed empty";

  list = BuildListOfStrings();
  if( !list )
    return "could not build the test list";
  if( ListIsEmpty( list ) )
    return "a full list was deemed empty";

  return NULL;
}

const char *
test_prepend_value( void )
{
  List *list, *result;
  void *value;

  list = NewList();
  FAIL_IF_NULL( list, "could not build a new test list" )

  value = ( void * ) "new start";

  result = PrependToList( NULL, NULL );
  FAIL_IF_NOT_NULL( result, "two empty arguments did not generate an error" )

  result = PrependToList( NULL, value );
  FAIL_IF_NOT_NULL( result, "a NULL list did not generate an error" )

  result = PrependToList( list, value );
  FAIL_IF_NULL( result, "a value could not be prepended to an empty list" )
  FAIL_IF_NULL( list->first, "the list still did not have any members" )
  FAIL_IF_NULL( list->first->value, "the list's nodes were invalid" )
  if( list->first->value != value )
    return "the value was not actually prepended to the list";

  list = BuildListOfStrings();
  FAIL_IF_NULL( list, "could not build a populated test list" )
  value = "yet another start";
  result = PrependToList( list, value );
  FAIL_IF_NULL( result, "the value was not correctly prepended to a populated list" )
  FAIL_IF_NULL( list->first, "a populated list had it's members removed" );
  FAIL_IF_NULL( list->first->value, "the new element did not have a value" )
  if( list->first->value != value )
    return "the value was not actually prepended to a full list";

  return NULL;
}

const char *
test_separator( void )
{
  const char *str, *temp;
  List *list, *result;
  ListIterator *iterator;
  void *separator = ( void * ) ", ";

  list = NewList();
  result = AddSeparatorToList( list, separator );
  if( list != result )
    return "an empty list was not handled properly";

  list = BuildListOfStrings();
  FAIL_IF_NULL( list, "could not build the test list" )
  result = AddSeparatorToList( list, separator );

  if( list != result )
    return "the separator was not properly added to the list";

  iterator = BeginList( list );
  str = NextInListIterator( iterator );
  ASSERT_STRINGS_EQUAL( "This", str, "the first part of the list was not what was expected" )
  str = NextInListIterator( iterator );
  ASSERT_STRINGS_EQUAL( ", ", str, "the second part of the list was not what was expected" )
  temp = NextInListIterator( iterator );
  while( temp ){
    str = temp;
    temp = NextInListIterator( iterator );
  }

  if( strcmp( ", ", str ) == 0 )
    return "the separator was present at the end of the list";

  DestroyListIterator( iterator );

  return NULL;
}

const char *
test_size
( void )
{
  List *list;

  list = NewList();
  FAIL_IF_NULL( list, "could not build empty test list" )

  if( ListSize( list ) != 0 )
    return "an empty list did not have a size of 0";

  list = BuildListOfStrings();
  FAIL_IF_NULL( list, "could not build the full test list" )

  if( ListSize( list ) != 7 )
    return "a full list did not have the proper size";

  return NULL;
}
