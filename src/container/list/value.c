#include <stdio.h>
#include <string.h>

#include <stumpless/value.h>
#include <stumpless/value/constructor.h>

#include "private/configuration.h"
#include "private/container/list.h"
#include "private/container/list/inheritance.h"
#include "private/container/list/iterator.h"
#include "private/container/list/value.h"
#include "private/container/list/const_iterator/value.h"
#include "private/container/list/const_reverse_iterator/value.h"
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

// todo rewrite to no longer depend on a buffer
Status *
ValueListIntoString
( char * str, const ValueList * list )
{
  if( !str || !list )
    return RaiseStatus( "empty argument" );

  str[0] = '\0';

  Configuration * configuration = GetConfiguration();
  if( !configuration )
    return RaiseStatus( "memory allocation failure" );

  size_t buffer_size = configuration->string->buffer_size;
  char * buffer = malloc( sizeof( char ) * ( buffer_size + 1 ) );
  if( !buffer )
    return RaiseStatus( "memory allocation failure" );

  Value * value;
  char * value_str;
  ListIterator * values = BeginList( list->list );
  while( value = NextInListIterator( values ) ){
    if( !value || !value->profile ){
      DestroyListIterator( values );
      return RaiseStatus( "malformed structure" );
    }

    if( !value->profile->to_string ){
      continue;
    }

    value_str = value->profile->to_string( value );
    if( value_str )
      strncat( str, value_str, buffer_size );
  }

  DestroyListIterator( values );
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
  char * list_str = malloc( sizeof( char ) * buffer_size + 1 );

  NULL_ON_FAILURE( ValueListIntoString( list_str, list ) )

  return list_str;
}

ValueList *
ValueListToStrings
( const ValueList * list )
{
  if( !list )
    return NULL;

  ValueList * output = NewValueList();
  if( !output )
    return NULL;

  char * str;
  Value * value;
  ListIterator * values = BeginList( list->list );
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
