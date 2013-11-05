#include <dictionary.h>

#include "private/dictionary.h"

void
__STUMPLESS_NAME( DestroyDictionary )
( __STUMPLESS_NAME( Dictionary ) * dictionary )
{
  DestroyDictionary( dictionary );
}

void *
__STUMPLESS_NAME( GetDictionaryValue )
( __STUMPLESS_NAME( Dictionary ) * dictionary, const char * key )
{
  return GetDictionaryValue( dictionary, key );
}

__STUMPLESS_NAME( Dictionary ) *
__STUMPLESS_NAME( NewDictionary )
()
{
  return NewDictionary();
}

void *
__STUMPLESS_NAME( RemoveDictionaryValue )
( __STUMPLESS_NAME( Dictionary ) * dictionary, const char * key )
{
  return RemoveDictionaryValue( dictionary, key );
}

__STUMPLESS_NAME( Dictionary ) *
__STUMPLESS_NAME( SetDictionaryValue )
( __STUMPLESS_NAME( Dictionary ) * dictionary, const char * key, void * value )
{
  return SetDictionaryValue( dictionary, key, value );
}
