#include <stdlib.h>

#include "private/container/dictionary/const_iterator.h"
#include "private/type.h"
#include "static/container/dictionary.h"
#include "static/container/dictionary/const_iterator.h"

DictionaryConstIterator *
CopyDictionaryConstIterator
( const DictionaryConstIterator *iterator )
{
  if( !iterator )
    return NULL;

  DictionaryConstIterator *copy = malloc( sizeof( DictionaryConstIterator ) );
  if( !copy )
    return NULL;

  copy->dictionary = iterator->dictionary;
  copy->current = iterator->current;

  return copy;
}

void
DestroyDictionaryConstIterator
( DictionaryConstIterator *iterator )
{
  if( !iterator )
    return;

  free( iterator );

  return;
}

unsigned short
DictionaryConstIteratorHasNext
( const DictionaryConstIterator *iterator )
{
  return iterator != NULL && iterator->current != NULL;
}

DictionaryConstIterator *
NewDictionaryConstIterator
( const Dictionary *dictionary, int position )
{
  if( DictionaryIsEmpty( dictionary ) )
    return NULL;

  DictionaryConstIterator *iterator = malloc( sizeof( DictionaryConstIterator ) );
  if( !iterator )
    return NULL;

  iterator->dictionary = dictionary;
  iterator->current = dictionary->root;
  while( iterator->current->left_child )
    iterator->current = iterator->current->left_child;

  return iterator;
}

const void *
NextInDictionaryConstIterator
( DictionaryConstIterator *iterator )
{
  if( !iterator || !iterator->current )
    return NULL;

  void *value = iterator->current->value;

  if( iterator->current->right_child ){
    iterator->current = iterator->current->right_child;
    while( iterator->current->left_child ){
      iterator->current = iterator->current->left_child;
    }
  }

  Node *previous = iterator->current;
  iterator->current = iterator->current->parent;
  while( iterator->current ){
    if( previous == iterator->current->left_child )
      return value;

    previous = iterator->current;
    iterator->current = iterator->current->parent;
  }

  return value;
}
