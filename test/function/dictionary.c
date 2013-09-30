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

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( add_value )
  RUN_TEST( constructor )
  RUN_TEST( destructor )
  RUN_TEST( get_value )
  
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
  
  Dictionary * result;
  result = AddValueToDictionary( dictionary, "testing", "1-2-3" );
  FAIL_IF_NULL( result, "the new value could not be added" )
  
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
  
  return NULL;
}
