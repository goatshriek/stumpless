#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/formatter_list.h"
#include "private/formatter_list_static.h"
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
  FormatterList * list = NewFormatterList();
  if( list == NULL )
    return "the list was not created";
  
  Formatter * formatter_1 = BuildFormatter();
  formatter_1->name = "first test formatter";
  
  Formatter * formatter_2 = BuildFormatter();
  formatter_2->name = "second test formatter";
  
  Formatter * formatter_3 = BuildFormatter();
  formatter_3->name = "third test formatter";
  
  Formatter * formatter_4 = BuildFormatter();
  formatter_4->name = "fourth test formatter";
  
  status = AppendToFormatterList( list, formatter_1 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToFormatterList( list, formatter_2 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToFormatterList( list, formatter_3 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToFormatterList( list, formatter_4 );
  if( status != NULL )
    return "the node was not successfully added";
  
  Formatter * formatter = BeginFormatterList( list );
  FAIL_IF_NULL( formatter, "the list did not have a first node" )
  if( formatter != formatter_1 )
    return "the first formatter was not correct";
  
  return NULL;
}

const char *
test_begin
( void )
{
  FormatterList * list = BuildFormatterList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Formatter * formatter = BeginFormatterList( list );
  FAIL_IF_NULL( formatter, "a formatter was returned from a newly-constructed list" )
  
  return NULL;
}

const char *
test_constructor
( void )
{
  FormatterList * list = NULL;
  
  list = NewFormatterList();
  
  if( list == NULL )
    return "the list was not created";
  
  Formatter * formatter = BeginFormatterList( list );
  FAIL_IF_NOT_NULL( formatter, "a newly-constructed list already had members" )
  
  return NULL;
}

const char *
test_copy
( void )
{
  FormatterList * list = BuildFormatterList();
  if( list == NULL )
    return "could not build the test list";
  
  FormatterList * copy;
  
  copy = CopyFormatterList( NULL );
  if( copy != NULL )
    return "the copy was not null for a null pointer";
  
  copy = CopyFormatterList( list );
  FAIL_IF_NULL( copy, "the copy was null for a non-null pointer" )
  if( copy == list )
    return "the copy was equal to the original list";
  
  Formatter * original_formatter = BeginFormatterList( list );
  Formatter * copy_formatter = BeginFormatterList( copy );
  while( original_formatter != NULL ){
    if( original_formatter != copy_formatter )
      return "the copy was not an accurate copy of the original";
    original_formatter = NextInFormatterList( list );
    copy_formatter = NextInFormatterList( copy );
  }
  
  return NULL;
}

const char *
test_destructor
( void )
{
  FormatterList * list = NewFormatterList();
  
  if( list == NULL )
    return "the list was not created";
  
  DestroyFormatterList( list );
  
  list = BuildFormatterList();
  if( list == NULL )
     return "could not build the test list";
  
  DestroyFormatterList( list );
  
  return NULL;
}

const char *
test_is_empty
( void )
{
  FormatterList * list = NULL;
  if( !FormatterListIsEmpty( list ) )
    return "a null list pointer was deemed empty";
  
  list = NewFormatterList();
  if( !FormatterListIsEmpty( list ) )
    return "a newly created list pointer was not deemed empty";
  
  list = BuildFormatterList();
  if( list == NULL )
    return "could not build the test list";
  if( FormatterListIsEmpty( list ) )
    return "a full list was deemed empty";
  
  return NULL;
}

const char *
test_next
( void )
{
  FormatterList * list = BuildFormatterList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  Formatter * formatter = BeginFormatterList( list );
  FAIL_IF_NULL( formatter, "a formatter was not returned from the start call" )
  
  formatter = NextInFormatterList( list );
  FAIL_IF_NULL( formatter, "a formatter was not returned from the next call" )
  
  return NULL;
}

const char *
test_prepender( void )
{
  FormatterList * list = NewFormatterList();
  FAIL_IF_NULL( list, "could not build a new test list" )
  
  Formatter * formatter = BuildFormatter();
  FAIL_IF_NULL( list, "could not build the test formatter" );
  
  Status * status = PrependToFormatterList( NULL, NULL );
  FAIL_IF_NULL( status, "two empty arguments did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "two empty arguments did not generate the appropriate status code" )
  
  status = PrependToFormatterList( list, NULL );
  FAIL_IF_NULL( status, "an empty value did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty value did not generate the appropriate status code" )
  
  status = PrependToFormatterList( NULL, formatter );
  FAIL_IF_NULL( status, "a NULL list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a NULL list did not generate the appropriate status code" )
 
  status = PrependToFormatterList( list, formatter );
  FAIL_IF_NOT_NULL( status, "a value could not be prepended to an empty list" )
  Formatter * retrieved_formatter = BeginFormatterList( list );
  FAIL_IF_NULL( retrieved_formatter, "the list's nodes were invalid" )
  if( retrieved_formatter != formatter )
    return "the formatter was not actually prepended to the list";
  
  list = BuildFormatterList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  formatter = BuildFormatter();
  FAIL_IF_NULL( list, "could not build a test formatter" )
  status = PrependToFormatterList( list, formatter );
  FAIL_IF_NOT_NULL( status, "the formatter was not correctly prepended to a populated list" )
  retrieved_formatter = BeginFormatterList( list );
  FAIL_IF_NULL( retrieved_formatter, "a populated list had its members removed" )
  if( retrieved_formatter != formatter )
    return "the formatter was not actually prepended to a full list";
  
  return NULL;
}

const char *
test_value_through
( void )
{
  return NULL;
}
