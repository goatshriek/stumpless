#include <stdio.h>

#include <value.h>
#include <value_list.h>
#include <types.h>

static
void
DestroyValueListNode( StumplessValueListNode * node )
{
  if( node == NULL )
    return;
  
  StumplessDestroyValue( node->value );
  
  free( node );
}

StumplessStatusCode
StumplessAppendStringToValueList( StumplessValueList * list, char * str )
{
  if( list == NULL || str == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessValue * value = StumplessValueFromString( str );
  if( value == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  return StumplessAppendToValueList( list, value );
}

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

short
StumplessValueListIsEmpty( StumplessValueList * list )
{
  if( list == NULL )
    return 1;
  else
    return list->first == NULL;
}

char *
StumplessValueListToString( StumplessValueList * list )
{
  return NULL;
}

StumplessStatusCode
StumplessWriteAndDestroyValueList( FILE * stream, StumplessValueList * list )
{
  if( stream == NULL || list == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessStatusCode status;
  StumplessValueListNode * previous = NULL;
  StumplessValueListNode * current = list->first;
  
  while( current != NULL ){
    status = StumplessWriteValueToStream( stream, current->value );
    if( status != STUMPLESS_SUCCESS )
      return status;
    
    previous = current;
    current = current->next;
    DestroyValueListNode( previous );
  }
  
  free( list );
  return STUMPLESS_SUCCESS;
}

StumplessStatusCode
StumplessWriteValueListToStream( FILE * stream, StumplessValueList * list )
{
  if( stream == NULL || list == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessStatusCode status;
  StumplessValueListNode * current = list->first;
  
  while( current != NULL ){
    status = StumplessWriteValueToStream( stream, current->value );
    if( status != STUMPLESS_SUCCESS )
      return status;
    
    current = current->next;
  }
  
  return STUMPLESS_SUCCESS;
}
