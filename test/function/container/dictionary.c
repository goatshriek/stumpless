#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/container/dictionary.h"
#include "private/type.h"

#include "helper.h"

const char * test_constructor( void );
const char * test_destructor( void );
const char * test_get_value( void );
const char * test_remove_value( void );
const char * test_set_value( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( constructor )
  RUN_TEST( destructor )
  RUN_TEST( get_value )
  RUN_TEST( remove_value )
  RUN_TEST( set_value )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_constructor
( void )
{
  Dictionary * dictionary = NewDictionary();
  
  FAIL_IF_NULL( dictionary, "the dictionary could not be created" )
  
  return NULL;
}

const char *
test_destructor
( void )
{
  Dictionary * dictionary = NewDictionary();
  
  FAIL_IF_NULL( dictionary, "the dictionary was not created" )
  
  DestroyDictionary( dictionary );
  
  dictionary = BuildDictionaryOfStrings();
  FAIL_IF_NULL( dictionary, "could not build the test dictionary" )
  
  DestroyDictionary( dictionary );
  
  return NULL;
}

const char *
test_get_value
( void )
{
  Dictionary * dictionary = BuildDictionaryOfStrings();
  FAIL_IF_NULL( dictionary, "could not build the test dictionary" )
  
  const char * string = GetDictionaryValue( NULL, NULL );
  FAIL_IF_NOT_NULL( string, "two empty arguments returned a value" )
  
  string = GetDictionaryValue( NULL, "third" );
  FAIL_IF_NOT_NULL( string, "a NULL dictionary returned a value" )
  
  string = GetDictionaryValue( dictionary, NULL );
  FAIL_IF_NOT_NULL( string, "a NULL key returned a value" );
  
  string = GetDictionaryValue( dictionary, "third" );
  FAIL_IF_NULL( string, "could not get the value" )
  
  ASSERT_STRINGS_EQUAL( "3rd", string, "the retrieved value was incorrect" )
  
  string = GetDictionaryValue( dictionary, "one hundred" );
  FAIL_IF_NOT_NULL( string, "a non-existent key returned a value" )
  
  return NULL;
}

const char *
test_remove_value
( void )
{
  Dictionary * dictionary = BuildDictionaryOfStrings();
  FAIL_IF_NULL( dictionary, "could not build the test dictionary" )
  
  const char * retrieved = GetDictionaryValue( dictionary, "third" );
  FAIL_IF_NULL( retrieved, "an existing value could not be retrieved" )
  
  const char * removed = RemoveDictionaryValue( dictionary, "third" );
  FAIL_IF_NULL( removed, "an existing value could not be removed" )
  ASSERT_STRINGS_EQUAL( retrieved, removed, "the value returned from a retrieval did not match that returned by a removal" )
  
  retrieved = GetDictionaryValue( dictionary, "third" );
  FAIL_IF_NOT_NULL( retrieved, "a removed value was still present" )
  
  return NULL;
}

const char *
test_set_value
( void )
{
  Dictionary * dictionary = BuildDictionaryOfStrings();
  FAIL_IF_NULL( dictionary, "the test dictionary could not be built" )
  
  const char * retrieved = GetDictionaryValue( NULL, NULL );
  FAIL_IF_NOT_NULL( retrieved, "two NULL arguments returned a value" )
  
  retrieved = GetDictionaryValue( NULL, "first" );
  FAIL_IF_NOT_NULL( retrieved, "a NULL dictionary returned a value" )
  
  retrieved = GetDictionaryValue( dictionary, NULL );
  FAIL_IF_NOT_NULL( retrieved, "a NULL key returned a value" )
  
  retrieved = GetDictionaryValue( dictionary, "first" );
  ASSERT_STRINGS_EQUAL( "1st", retrieved, "before an addition, a value could not be properly retrieved" )
  
  const char * key = "testing";
  const char * value = "1-2-3";
  
  retrieved = GetDictionaryValue( dictionary, key );
  FAIL_IF_NOT_NULL( retrieved, "a value was returned before the key was added" )
  
  Dictionary * result;
  result = SetDictionaryValue( NULL, NULL, NULL );
  FAIL_IF_NOT_NULL( result, "three NULL arguments did not cause failure" )
  
  result = SetDictionaryValue( NULL, NULL, ( void * ) value );
  FAIL_IF_NOT_NULL( result, "only a value did not cause failure" )
  
  result = SetDictionaryValue( dictionary, key, ( void * ) value );
  FAIL_IF_NULL( result, "the new value could not be added" )
  
  retrieved = GetDictionaryValue( dictionary, key );
  ASSERT_STRINGS_EQUAL( value, retrieved, "the retrieved value did not match that of the added value" )
  
  retrieved = GetDictionaryValue( dictionary, "first" );
  ASSERT_STRINGS_EQUAL( "1st", retrieved, "after an addition, a value could no longer be properly retrieved" )
  
  return NULL;
}
