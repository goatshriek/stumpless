#include <stdio.h>

#include <value.h>
#include <value_list.h>
#include <types.h>

StumplessStatusCode
StumplessAppendToValueList( StumplessValueList * list, StumplessValue * value )
{
  if( list == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  if( value == NULL )
    return STUMPLESS_SUCCESS;
  
  StumplessValueListNode * node = malloc( sizeof( StumplessValueListNode ) );
  if( node == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  node->value = value;
  node->next = NULL;
  
  if( list->last == NULL ){
    list->first = list->last = node;
  } else {
    list->last->next = node;
    list->last = node;
  }
  
  return STUMPLESS_SUCCESS;
}

void
StumplessDestroyValueList( StumplessValueList * list )
{
  StumplessValueListNode * prev = NULL;
  StumplessValueListNode * node = list->first;
  
  while( node != NULL ){
    if( prev != NULL ){
      StumplessDestroyValue( prev->value );
      free( prev );
    }
    
    prev = node;
    node = node->next;
  }
  
  free( list );
  
  return;
}

StumplessValueList *
StumplessNewValueList( void )
{
  StumplessValueList * list = malloc( sizeof( StumplessValueList ) );
  if( list == NULL )
    return NULL;
  
  list->first = NULL;
  list->last = NULL;
  
  return list;
}

char *
StumplessValueListToString( StumplessValueList * list )
{
  return NULL;
}

StumplessStatusCode
StumplessWriteValueListToStream( FILE * stream, StumplessValueList * list )
{
  return STUMPLESS_FAILURE;
}
