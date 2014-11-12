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
  DictionaryConstIterator *copy = CopyDictionaryConstIterator( NULL );
  if( copy )
    return "an iterator was copied from a NULL iterator";

  DictionaryConstIterator *iterator = BuildDictionaryConstIterator();
  if( !iterator )
    return "could not build test iterator";

  copy = CopyDictionaryConstIterator( iterator );
  if( !copy )
    return "could not create a copy of an iterator";

  if( copy == iterator )
    return "the copy was the same as the original";
  if( copy->dictionary != iterator->dictionary )
    return "the copy did not point to the same dictionary";
  if( copy->current != iterator->current )
    return "the copy did not start in the same place as the original";

  return NULL;
}

const char *
TestDestroy
( void )
{
  DestroyDictionaryConstIterator( NULL );

  DictionaryConstIterator *iterator = BuildDictionaryConstIterator();
  if( !iterator )
    return "could not build test iterator";

  DestroyDictionaryConstIterator( iterator );

  return NULL;
}

const char *
TestHasNext
( void )
{
  Dictionary *dictionary = BuildDictionaryOfStrings();
  if( !dictionary )
    return "could not build test Dictionary";

  DictionaryConstIterator *iterator = CBeginDictionary( dictionary );
  if( !iterator )
    return "could not build test iterator";

  if( !DictionaryConstIteratorHasNext( iterator ) )
    return "the iterator did not show its first value";

  NextInDictionaryConstIterator( iterator );

  if( !DictionaryConstIteratorHasNext( iterator ) )
    return "the iterator did not show its second value";

  NextInDictionaryConstIterator( iterator );

  if( !DictionaryConstIteratorHasNext( iterator ) )
    return "the iterator did not show its third value";

  NextInDictionaryConstIterator( iterator );

  if( DictionaryConstIteratorHasNext( iterator ) )
    return "the iterator had a value after all were used";

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
