#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helper.h"

#include "inheritance/list.h"

#include "private/value.h"

#include "private/container/list/value.h"

#include "private/container/list/iterator/value.h"

const char * test_add_separator( void );
const char * test_append( void );
const char * test_append_to( void );
const char * test_back( void );
const char * test_begin( void );
const char * test_cbegin( void );
const char * test_cend( void );
const char * test_constructor( void );
const char * test_contains( void );
const char * test_copy( void );
const char * test_crbegin( void );
const char * test_crend( void );
const char * test_destructor( void );
const char * test_end( void );
const char * test_front( void );
const char * test_into_string( void );
const char * test_is_empty( void );
const char * test_prepend_to( void );
const char * test_rbegin( void );
const char * test_rend( void );
const char * test_size( void );
const char * test_string_appender( void );
const char * test_string_prepender( void );
const char * test_to_string( void );
const char * test_unsigned_int_appender( void );

int
main
( void )
{
  unsigned failure_count = 0;
  const char *result;

  RUN_TEST( add_separator )
  RUN_TEST( append )
  RUN_TEST( append_to )
  RUN_TEST( back )
  RUN_TEST( begin )
  RUN_TEST( cbegin )
  RUN_TEST( cend )
  RUN_TEST( constructor )
  RUN_TEST( contains )
  RUN_TEST( copy )
  RUN_TEST( crbegin )
  RUN_TEST( crend )
  RUN_TEST( destructor )
  RUN_TEST( end )
  RUN_TEST( front )
  RUN_TEST( into_string )
  RUN_TEST( is_empty )
  RUN_TEST( prepend_to )
  RUN_TEST( rbegin )
  RUN_TEST( rend )
  RUN_TEST( size )
  RUN_TEST( string_appender )
  RUN_TEST( string_prepender )
  RUN_TEST( to_string )
  RUN_TEST( unsigned_int_appender )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

TEST_ADD_SEPARATOR( Value )

TEST_APPEND( Value )

TEST_APPEND_TO( Value )

TEST_BACK( Value )

TEST_BEGIN( Value )

TEST_CBEGIN( Value )

TEST_CEND( Value )

TEST_CONSTRUCTOR( Value )

TEST_CONTAINS( Value )

TEST_COPY( Value )

TEST_CRBEGIN( Value )

TEST_CREND( Value )

TEST_DESTRUCTOR( Value )

TEST_END( Value )

TEST_FRONT( Value )

const char *
test_into_string
( void )
{
  ValueList * list = BuildValueList();
  if( !list )
    return "could not build the test list";
  char str[1000];

  Status * status = ValueListIntoString( NULL, list );
  FAIL_IF_NULL( status, "an empty string did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty string did not generate the correct error" )

  status = ValueListIntoString( str, NULL );
  FAIL_IF_NULL( status, "an empty list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty list did not generate the correct error" )

  status = ValueListIntoString( str, list );
  if( status )
    return "a valid string was not properly written into";

  if( !strstr( str, "4294967196" ) )
    return "the new string did not contain parts of the list";

  return NULL;
}

TEST_IS_EMPTY( Value )

TEST_PREPEND_TO( Value )

TEST_RBEGIN( Value )

TEST_REND( Value )

TEST_SIZE( Value )


const char *
test_string_appender( void )
{
  ValueList * result = AppendStringToValueList( NULL, "str" );
  FAIL_IF_NOT_NULL( result, "an empty list did not generate an abnormal status" )

  ValueList * list = BuildValueList();
  FAIL_IF_NULL( list, "could not build the test list" )

  result = AppendStringToValueList( list, NULL );
  FAIL_IF_NOT_NULL( result, "an empty string did not generate an abnormal status" )

  result = AppendStringToValueList( list, "str" );
  if( result != list )
    return "the string was not successfully appended to the list";

  return NULL;
}

const char *
test_string_prepender( void )
{
  ValueList *list = NewValueList();
  if( !list )
    return "could not build a new test list";

  ValueList *result = PrependStringToValueList( NULL, NULL );
  if( result )
    return "two null arguments did not return null";

  result = PrependStringToValueList( list, NULL );
  if( result )
    return "a null string did not return null";

  result = PrependStringToValueList( NULL, "shouldn't work" );
  if( result )
    return "a null list did not return null";

  result = PrependStringToValueList( list, "lonely little guy" );
  if( result != list )
    return "a string could not be prepended to an empty list";

  ValueListIterator *iterator = BeginValueList( list );
  Value * value = NextInValueListIterator( iterator );
  FAIL_IF_NULL( value, "the list still did not have any members" )
  FAIL_IF_NULL( value->data, "the new value did not have any data" )
  ASSERT_STRINGS_EQUAL( "string", value->profile->name, "the new value was not a string" )
  ASSERT_STRINGS_EQUAL( "lonely little guy", value->data->c_p, "the new string was not equivalent to the added one" )
  DestroyValueListIterator( iterator );

  list = BuildValueList();
  FAIL_IF_NULL( list, "could not build a populated test list" )
  result = PrependStringToValueList( list, "new beginning" );
  if( result != list )
    return "the string was not correctly prepended to a populated list";

  iterator = BeginValueList( list );
  value = NextInValueListIterator( iterator );
  FAIL_IF_NULL( value, "a populated list had it's members removed" );
  FAIL_IF_NULL( value->data, "the new value did not have any data" )
  ASSERT_STRINGS_EQUAL( "string", value->profile->name, "the new value was not a string" )
  ASSERT_STRINGS_EQUAL( "new beginning", value->data->c_p, "the new string was not equivalent to the added one" )

  DestroyValueListIterator( iterator );
  return NULL;
}

const char *
test_to_string( void )
{
  ValueList * list = BuildValueList();
  if( list == NULL )
    return "could not build the test list";

  char * str = ValueListToString( NULL );
  if( str != NULL )
    return "a null list did not return a null string";

  str = ValueListToString( list );
  if( str == NULL )
    return "a valid list returend a null string";

  if( strstr( str, "4294967196" ) == NULL )
    return "the new string did not contain parts of the list";

  return NULL;
}

const char *
test_unsigned_int_appender( void )
{
  ValueList *list = BuildValueList();
  if( !list )
    return "could not build the test list";

  ValueList *result  = AppendUnsignedIntToValueList( NULL, 3 );
  if( result )
    return "a null list did not generate an abnormal status";

  result = AppendUnsignedIntToValueList( list, 4 );
  if( result != list )
    return "an unsigned number was not correctly appended to the list";

  return NULL;
}
