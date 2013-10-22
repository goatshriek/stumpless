#include <stdio.h>
#include <string.h>

#include "private/configuration.h"
#include "private/list.h"
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
  
  List * result = AddSeparatorToList( list->list, ( void * ) separator );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  else
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
  
  List * result = AppendLists( beginning->list, end->list );
  if( result != beginning->list )
    return RaiseAbnormalStatus( "list failure" );
  else
    return NULL;
}

Status *
AppendValueToValueList
( ValueList * list, Value * value )
{
  if( list == NULL || value == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = AppendToList( list->list, value );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

Value *
BeginValueList
( ValueList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return BeginList( list->list );
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
  
  copy->list = CopyList( list->list );
  
  return copy;
}

void
DestroyValueList
( ValueList * list )
{
  DestroyList( list->list );
  
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
  
  list->list = NewList();
  if( list->list == NULL )
    return NULL;
  
  return list;
}

Value *
NextInValueList
( ValueList * list )
{
  if( list == NULL || list->list == NULL )
    return NULL;
  
  return NextInList( list->list );
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
  
  if( list->list == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  List * result = PrependToList( list->list, value );
  if( result != list->list )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
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
  
  Value * value = BeginList( list->list );
  char * value_str;
  while( value != NULL ){
    if( value == NULL || value->profile == NULL )
      return RaiseAbnormalStatus( "malformed structure" );
    
    if( value->profile->to_string == NULL ){
      value = NextInList( list->list );
      continue;
    }
    
    value_str = value->profile->to_string( value );
    if( value_str != NULL )
      strncat( str, value_str, buffer_size );
    value = NextInList( list->list );
  }
  
  return NULL;
}

unsigned short
ValueListIsEmpty
( ValueList * list )
{
  return list == NULL || ListIsEmpty( list->list );
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
  Value * value = BeginList( list->list );
  while( value != NULL ){
    str = value->profile->to_string( value );
    NULL_ON_FAILURE( AppendStringToValueList( output, str ) )
    
    value = NextInList( list->list );
  }
  
  return output;
}
