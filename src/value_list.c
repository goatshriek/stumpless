#include <stdio.h>
#include <string.h>

#include "private/configuration.h"
#include "private/status.h"
#include "private/status_checker.h"
#include "private/type.h"
#include "private/value.h"
#include "private/value_constructor.h"
#include "private/value_list.h"
#include "private/value_list_static.h"

Status *
AddSeparatorToValueList
( ValueList * list, Value * separator )
{
  if( list == NULL || separator == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  Node * new_node;
  Node * current = list->first;
  while( current != list->last ){
    new_node = malloc( sizeof( Node ) );
    if( new_node == NULL )
      return RaiseAbnormalStatus( "memory allocation failure" );
    new_node->value = separator;
    new_node->next = current->next;
    current->next = new_node;
    
    current = new_node->next;
  }
  
  return NULL;
}

Status *
AppendStringToValueList
( ValueList * list, const char * str )
{
  if( list == NULL || str == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  Value * value = ValueFromString( str );
  if( value == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  
  return AppendValueToValueList( list, value );
}

Status *
AppendUnsignedIntToValueList
( ValueList * list, unsigned num )
{
  if( list == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  Value * value = ValueFromUnsignedInt( num );
  if( value == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  else
    return AppendValueToValueList( list, value );
}

Status *
AppendValueLists
( ValueList * beginning, ValueList * end )
{
  if( beginning == NULL || end == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  ValueList * copy = CopyValueList( end );
  if( copy == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  
  if( beginning->first == NULL )
    beginning->first = copy->first;
  else
    beginning->last->next = copy->first;
  beginning->last = copy->last;
  
  free( copy );
  
  return NULL;
}

Status *
AppendValueToValueList
( ValueList * list, Value * value )
{
  if( list == NULL || value == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  Node * node = malloc( sizeof( Node ) );
  if( node == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  
  node->value = value;
  
  return AppendNodeToValueList( list, node );
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
  
  Node * node = list->first;
  Node * copied_node;
  while( node != NULL ){
    copied_node = malloc( sizeof( Node ) );
    if( copied_node == NULL )
      return NULL;
    
    NULL_ON_FAILURE( AppendNodeToValueList( copy, copied_node ) )
    
    copied_node->value = node->value; 
    
    node = node->next;
  }
  
  return copy;
}

void
DestroyValueList
( ValueList * list )
{
  Node * prev = NULL;
  Node * node = list->first;
  
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

Value *
NextInValueList
( ValueList * list )
{
  if( list == NULL || list->current == NULL )
    return NULL;
  
  list->current = list->current->next;
  if( list->current == NULL )
    return NULL;
  
  return list->current->value;
}

Status *
PrependStringToValueList
( ValueList * list, const char * str )
{
  if( list == NULL || str == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  Value * value = ValueFromString( str );
  if( value == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  
  return PrependValueToValueList( list, value );
}

Status *
PrependValueToValueList
( ValueList * list, Value * value )
{
  if( list == NULL || value == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  Node * node = malloc( sizeof( Node ) );
  if( node == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  
  node->value = value;
  
  return PrependNodeToValueList( list, node );
}

Value *
StartValueList
( ValueList * list )
{
  if( list == NULL || list->first == NULL )
    return NULL;
  
  list->current = list->first;
  return list->current->value;
}

// todo rewrite to longer depend on a buffer
Status *
ValueListIntoString
( char * str, ValueList * list )
{
  if( str == NULL || list == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  str[0] = '\0';
  
  Configuration * configuration = GetConfiguration();
  if( configuration == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  
  size_t buffer_size = configuration->string->buffer_size;
  char * buffer = malloc( sizeof( char ) * ( buffer_size + 1 ) );
  if( buffer == NULL )
    return RaiseAbnormalStatus( "memory allocation failure" );
  
  Node * node = list->first;
  char * value_str;
  while( node != NULL ){
    if( node->value == NULL || node->value->profile == NULL )
      return RaiseAbnormalStatus( "malformed structure" );
    
    if( node->value->profile->to_string == NULL ){
      node = node->next;
      continue;
    }
    
    value_str = node->value->profile->to_string( node->value );
    if( value_str != NULL )
      strncat( str, value_str, buffer_size );
    node = node->next;
  }
  
  return NULL;
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
  Node * node = list->first;
  while( node != NULL ){
    str = node->value->profile->to_string( node->value );
    NULL_ON_FAILURE( AppendStringToValueList( output, str ) )
    
    node = node->next;
  }
  
  return output;
}

static
Status *
AppendNodeToValueList
( ValueList * list, Node * node )
{
  if( list == NULL || node == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  node->next = NULL;
  
  if( list->first == NULL )
    list->first = node;
  else
    list->last->next = node;
  
  list->last = node;
  
  return NULL;
}

static
void
DestroyNode
( Node * node )
{
  if( node == NULL )
    return;
  
  free( node );
}

static
Status *
PrependNodeToValueList
( ValueList * list, Node * node )
{
  if( list == NULL || node == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  node->next = list->first;
  list->first = node;
  
  if( list->last == NULL )
    list->last = node;
  
  return NULL;
}
