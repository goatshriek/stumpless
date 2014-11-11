#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/container/dictionary.h"
#include "private/container/dictionary/const_iterator.h"
#include "static/container/dictionary.h"
#include "static/container/dictionary/const_iterator.h"
#include "test/function/container/dictionary/const_iterator.h"
#include "test/helper.h"
#include "test/type.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;
 
  TEST( Copy )
  TEST( Destroy )
  TEST( HasNext )
  TEST( New )
  TEST( Next ) 
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestCopy
( void )
{
  return NULL;
}

const char *
TestDestroy
( void )
{
  return NULL;
}

const char *
TestHasNext
( void )
{
  return NULL;
}

const char *
TestNew
( void )
{
  DictionaryConstIterator *iterator = NewDictionaryConstIterator( NULL, 0 );
  if( iterator )
    return "an iterator was created from a NULL Dictionary";

  Dictionary *dictionary = BuildDictionaryOfStrings();
  if( !dictionary )
    return "could not build a test Dictionary";
  
  iterator = NewDictionaryConstIterator( dictionary, 0 );
  if( !iterator )
    return "could not create an iterator from a Dictionary";

  if( iterator->dictionary != dictionary )
    return "the iterator did not have the correct Dictionary";
  
  ASSERT_STRINGS_EQUAL( "1st", iterator->current->value, "the value returned was not the first in the Dictionary"  )

  return NULL;
}

const char *
TestNext
( void )
{
  Dictionary *dictionary = BuildDictionaryOfStrings();
  if( !dictionary )
    return "could not build a test Dictionary";

  DictionaryConstIterator *iterator = NewDictionaryConstIterator( dictionary, 0 );
  if( !iterator )
    return "could not build a test iterator";
  
  const char *value = NextInDictionaryConstIterator( iterator );
  if( !value )
    return "could not get the first value";
  ASSERT_STRINGS_EQUAL( "1st", value, "the first value returned was not correct" );
  
  value = NextInDictionaryConstIterator( iterator );
  if( !value )
    return "could not get the second value";
  ASSERT_STRINGS_EQUAL( "2nd", value, "the second value returned was not correct" );
  
  value = NextInDictionaryConstIterator( iterator );
  if( !value )
    return "could not get the third value";
  ASSERT_STRINGS_EQUAL( "3rd", value, "the third value returned was not correct" );

  value = NextInDictionaryConstIterator( iterator );
  if( value )
    return "a value existed after the Dictionary was completely traversed";

  return NULL;
}
