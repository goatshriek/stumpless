#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/dictionary.h"
#include "private/type.h"

#include "helper.h"

const char * test_add_value( void );
const char * test_constructor( void );
const char * test_destructor( void );
const char * test_get_value( void );
const char * test_remove_value( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( add_value )
  RUN_TEST( constructor )
  RUN_TEST( destructor )
  RUN_TEST( get_value )
  RUN_TEST( remove_value )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_value
( void )
{
  Dictionary * dictionary = BuildDictionaryOfStrings();
  FAIL_IF_NULL( dictionary, "the test dictionary could not be built" )
  
  const char * retrieved = GetValueFromDictionary( dictionary, NULL );
  FAIL_IF_NOT_NULL( retrieved, "a NULL key returned a value" )
  
  retrieved = GetValueFromDictionary( dictionary, "first" );
  ASSERT_STRINGS_EQUAL( "1st", retrieved, "before an addition, a value could not be properly retrieved" )
  
  const char * key = "testing";
  const char * value = "1-2-3";
  
  retrieved = GetValueFromDictionary( dictionary, key );
  FAIL_IF_NOT_NULL( retrieved, "a value was returned before the key was added" )
  
  Dictionary * result;
  result = AddValueToDictionary( dictionary, key, ( void * ) value );
  FAIL_IF_NULL( result, "the new value could not be added" )
  
  retrieved = GetValueFromDictionary( dictionary, key );
  ASSERT_STRINGS_EQUAL( value, retrieved, "the retrieved value did not match that of the added value" )
  
  retrieved = GetValueFromDictionary( dictionary, "first" );
  ASSERT_STRINGS_EQUAL( "1st", retrieved, "after an addition, a value could no longer be properly retrieved" )
  
  return NULL;
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
  
  const char * string = GetValueFromDictionary( dictionary, "third" );
  FAIL_IF_NULL( string, "could not get the value" )
  
  ASSERT_STRINGS_EQUAL( "3rd", string, "the retrieved value was incorrect" )
  
  string = GetValueFromDictionary( dictionary, "one hundred" );
  FAIL_IF_NOT_NULL( string, "a non-existent key returned a value" )
  
  return NULL;
}

const char *
test_remove_value
( void )
{
  Dictionary * dictionary = BuildDictionaryOfStrings();
  FAIL_IF_NULL( dictionary, "could not build the test dictionary" )
  
  const char * retrieved = GetValueFromDictionary( dictionary, "third" );
  FAIL_IF_NULL( retrieved, "an existing value could not be retrieved" )
  
  const char * removed = RemoveValueFromDictionary( dictionary, "third" );
  FAIL_IF_NULL( removed, "an existing value could not be removed" )
  ASSERT_STRINGS_EQUAL( retrieved, removed, "the value returned from a retrieval did not match that returned by a removal" )
  
  retrieved = GetValueFromDictionary( dictionary, "third" );
  FAIL_IF_NOT_NULL( retrieved, "a removed value was still present" )
  
  return NULL;
}
