#include <stdlib.h>
#include <string.h>

#include "private/dictionary.h"
#include "private/type.h"

Dictionary *
AddValueToDictionary
( Dictionary * dictionary, const char * key, void * value )
{
  unsigned int index = dictionary->count++;
  
  dictionary->keys[index] = key;
  dictionary->values[index] = value;
  
  return dictionary;
}

void
DestroyDictionary
( Dictionary * dictionary )
{
  free( dictionary->keys );
  free( dictionary->values );
  free( dictionary );
  
  return;
}

void *
GetValueFromDictionary
( Dictionary * dictionary, const char * key )
{
  unsigned i = 0;
  
  for( i; i < dictionary->count; i++ )
    if( strcmp( dictionary->keys[i], key ) == 0 )
      return dictionary->values[i];
  
  return NULL;
}

Dictionary *
NewDictionary
()
{
  Dictionary * dictionary = malloc( sizeof( Dictionary ) );
  if( dictionary == NULL )
    return NULL;
  
  dictionary->keys = malloc( sizeof( char * ) * 100 );
  if( dictionary->keys == NULL )
    return NULL;
  
  dictionary->values = malloc( sizeof( void * ) * 100 );
  if( dictionary->values == NULL )
    return NULL;
  
  dictionary->count = 0;
  
  return dictionary;
}

Dictionary *
RemoveValueFromDictionary
( Dictionary * dictionary, const char * key )
{
  return NULL;
}
