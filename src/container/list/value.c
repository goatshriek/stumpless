#include <stdio.h>
#include <string.h>

#include <stumpless/value.h>
#include <stumpless/value/constructor.h>

#include "private/configuration.h"
#include "private/container/list.h"
#include "private/container/list/const_iterator.h"
#include "private/container/list/const_iterator/value.h"
#include "private/container/list/const_reverse_iterator/value.h"
#include "private/container/list/inheritance.h"
#include "private/container/list/iterator.h"
#include "private/container/list/value.h"
#include "private/container/list/iterator/value.h"
#include "private/container/list/reverse_iterator/value.h"
#include "private/status.h"
#include "private/status/checker.h"
#include "private/type.h"
#include "static/container/list/value.h"

ADD_SEPARATOR_TO_LIST( Value )

ValueList *
AppendCharToValueList
( ValueList *list, char character )
{
  if( !list )
    return NULL;

  return AppendToValueList( list, NewValueForChar( character ) );
}

ValueList *
AppendStringToValueList
( ValueList * list, const char * str )
{
  if( !list || !str )
    return NULL;

  return AppendToValueList( list, NewValueForString( str ) );
}

APPEND_TO_LIST( Value )

ValueList *
AppendUnsignedIntToValueList
( ValueList * list, unsigned num )
{
  if( !list )
    return NULL;

  return AppendToValueList( list, NewValueForUnsignedInt( num ) );
}

APPEND_LISTS( Value )

BEGIN_LIST( Value )

CBEGIN_LIST( Value )

CEND_LIST( Value )

COPY_LIST( Value )

CRBEGIN_LIST( Value )

CREND_LIST( Value )

DESTROY_LIST( Value )

END_LIST( Value )

NEW_LIST( Value )

ValueList *
PrependStringToValueList
( ValueList * list, const char * str )
{
  if( !list || !str )
    return NULL;

  return PrependToValueList( list, NewValueForString( str ) );
}

PREPEND_TO_LIST( Value )

RBEGIN_LIST( Value )

REND_LIST( Value )

LIST_BACK( Value )

LIST_CONTAINS( Value )

LIST_FRONT( Value )

Status *
ValueListIntoString
( char *str, const ValueList *list, size_t length )
{
  ListConstIterator *values;
  size_t current_position = 0, remaining_length;
  Status *result;
  const Value *value;

  if( !str || !list || length == 0 )
    return RaiseStatus( "empty argument" );

  str[0] = '\0';

  values = CBeginList( list->list );
  while( value = NextInListConstIterator( values ) ){
    current_position += strlen( str + current_position );
    if( length < current_position )
      remaining_length = current_position - length;
    else
      remaining_length = length - current_position;
    result = ValueIntoString( str + current_position, value, remaining_length );
    if( result )
      return result;
  }

  DestroyListConstIterator( values );
  return NULL;
}

LIST_IS_EMPTY( Value )

LIST_SIZE( Value )

char *
ValueListToString
( const ValueList * list )
{
  Configuration * configuration = GetConfiguration();
  size_t buffer_size = configuration->string->buffer_size;
  char *list_str = malloc( sizeof( char ) * buffer_size + 1 );

  NULL_ON_FAILURE( ValueListIntoString( list_str, list, buffer_size ) )

  list_str[buffer_size + 1] = '\0';

  return list_str;
}

ValueList *
ValueListToStrings
( const ValueList * list )
{
  char *str;
  ListIterator *values;
  Value *value;
  ValueList *output;

  if( !list )
    return NULL;

  output = NewValueList();
  if( !output )
    return NULL;

  values = BeginList( list->list );
  while( value = NextInListIterator( values ) ){
    str = value->profile->to_string( value );
    if( !AppendStringToValueList( output, str ) ){
      DestroyListIterator( values );
      return NULL;
    }
  }

  DestroyListIterator( values );
  return output;
}
