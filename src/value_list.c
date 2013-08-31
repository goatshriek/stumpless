#include <stdio.h>
#include <string.h>

#include "private/configuration.h"
#include "private/status_checker.h"
#include "private/type.h"
#include "private/value.h"
#include "private/value_constructor.h"
#include "private/value_list.h"

static
StatusCode
AppendValueListNodeToValueList
( ValueList * list, ValueListNode * node )
{
  if( list == NULL || node == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  node->next = NULL;
  
  if( list->first == NULL )
    list->first = node;
  else
    list->last->next = node;
  
  list->last = node;
  
  return STUMPLESS_SUCCESS;
}

static
void
DestroyValueListNode
( ValueListNode * node )
{
  if( node == NULL )
    return;
  
  DestroyValue( node->value );
  
  free( node );
}

static
StatusCode
PrependValueListNodeToValueList
( ValueList * list, ValueListNode * node )
{
  if( list == NULL || node == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  node->next = list->first;
  list->first = node;
  
  if( list->last == NULL )
    list->last = node;
  
  return STUMPLESS_SUCCESS;
}

StatusCode
AddSeparatorToValueList
( ValueList * list, Value * separator )
{
  if( list == NULL || separator == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  ValueListNode * new_node;
  ValueListNode * current = list->first;
  while( current != list->last ){
    new_node = malloc( sizeof( ValueListNode ) );
    if( new_node == NULL )
      return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
    new_node->value = separator;
    new_node->next = current->next;
    current->next = new_node;
    
    current = new_node->next;
  }
  
  return STUMPLESS_SUCCESS;
}

StatusCode
AppendStringToValueList
( ValueList * list, const char * str )
{
  if( list == NULL || str == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  Value * value = ValueFromString( str );
  if( value == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  return AppendValueToValueList( list, value );
}

StatusCode
AppendUnsignedIntToValueList
( ValueList * list, unsigned num )
{
  if( list == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  Value * value = ValueFromUnsignedInt( num );
  if( value == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  else
    return AppendValueToValueList( list, value );
}

StatusCode
AppendValueLists
( ValueList * beginning, ValueList * end )
{
  if( beginning == NULL || end == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  ValueList * copy = CopyValueList( end );
  if( copy == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  if( beginning->first == NULL )
    beginning->first = copy->first;
  else
    beginning->last->next = copy->first;
  beginning->last = copy->last;
  
  free( copy );
  
  return STUMPLESS_SUCCESS;
}

StatusCode
AppendValueToValueList
( ValueList * list, Value * value )
{
  if( list == NULL || value == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  ValueListNode * node = malloc( sizeof( ValueListNode ) );
  if( node == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  node->value = value;
  
  return AppendValueListNodeToValueList( list, node );
}

ValueList *
CopyValueList
( ValueList * list )
{
  if( list == NULL )
    return NULL;
  
  ValueList * copy = malloc( sizeof( ValueList ) );
  if( copy == NULL )
    return NULL;
  
  copy->first = copy->last =  NULL;
  
  ValueListNode * node = list->first;
  ValueListNode * copied_node;
  while( node != NULL ){
    copied_node = malloc( sizeof( ValueListNode ) );
    if( copied_node == NULL )
      return NULL;
    
    NULL_ON_FAILURE( AppendValueListNodeToValueList( copy, copied_node ) )
    
    copied_node->value = node->value; 
    
    node = node->next;
  }
  
  return copy;
}

void
DestroyValueList
( ValueList * list )
{
  ValueListNode * prev = NULL;
  ValueListNode * node = list->first;
  
  while( node != NULL ){
    if( prev != NULL ){
      DestroyValue( prev->value );
      free( prev );
    }
    
    prev = node;
    node = node->next;
  }
  
  free( list );
  
  return;
}

ValueList *
NewValueList
( void )
{
  ValueList * list = malloc( sizeof( ValueList ) );
  if( list == NULL )
    return NULL;
  
  list->first = NULL;
  list->last = NULL;
  
  return list;
}

StatusCode
PrependStringToValueList
( ValueList * list, const char * str )
{
  if( list == NULL || str == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  Value * value = ValueFromString( str );
  if( value == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  return PrependValueToValueList( list, value );
}

StatusCode
PrependValueToValueList
( ValueList * list, Value * value )
{
  if( list == NULL || value == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  ValueListNode * node = malloc( sizeof( ValueListNode ) );
  if( node == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  node->value = value;
  
  return PrependValueListNodeToValueList( list, node );
}

StatusCode
ValueListIntoString
( char * str, ValueList * list )
{
  if( str == NULL || list == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StatusCode status;
  str[0] = '\0';
  
  Configuration * configuration = GetConfiguration();
  if( configuration == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  size_t buffer_size = configuration->string->buffer_size;
  char * buffer = malloc( sizeof( char ) * ( buffer_size + 1 ) );
  if( buffer == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  ValueListNode * node = list->first;
  char * value_str;
  while( node != NULL ){
    if( node->value == NULL || node->value->profile == NULL )
      return STUMPLESS_MALFORMED_STRUCTURE;
    
    if( node->value->profile->to_string == NULL ){
      node = node->next;
      continue;
    }
    
    value_str = node->value->profile->to_string( node->value );
    if( value_str != NULL )
      strncat( str, value_str, buffer_size );
    node = node->next;
  }
  
  return STUMPLESS_SUCCESS;
}

unsigned short
ValueListIsEmpty
( ValueList * list )
{
  return list == NULL || list->first == NULL;
}

char *
ValueListToString
( ValueList * list )
{
  Configuration * configuration = GetConfiguration();
  size_t buffer_size = configuration->string->buffer_size;
  char * list_str = malloc( sizeof( char ) * buffer_size + 1 );
  
  NULL_ON_FAILURE( ValueListIntoString( list_str, list ) )
  
  return list_str;
}

ValueList *
ValueListToStrings
( ValueList * list )
{
  if( list == NULL )
    return NULL;
  
  ValueList * output = NewValueList();
  if( output == NULL )
    return NULL;
  
  char * str;
  ValueListNode * node = list->first;
  while( node != NULL ){
    str = node->value->profile->to_string( node->value );
    NULL_ON_FAILURE( AppendStringToValueList( output, str ) )
    
    node = node->next;
  }
  
  return output;
}
