#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/filter.h"
#include "private/filter/initializer.h"
#include "private/status.h"
#include "private/type.h"

static Dictionary * filters = NULL;

Status *
AddFilter
( Filter * filter )
{
  void *value;

  if( !filter || !filter->name )
    return NULL;

  if( filters == NULL ){
    filters = NewDictionary();

    if( filters == NULL )
      return RaiseStatus( "constructor failure" );
  }

  value = ( void * ) filter;
  if( !SetDictionaryValue( filters, filter->name, value ) )
    return NULL;

  return NULL;
}

// todo implement
void
DestroyFilter
( Filter *filter )
{
  return;
}

Filter *
FindFilterByName
( const char * name )
{
  Filter *filter;

  if( !filters ){
    filters = NewDictionary();

    if( !filters )
      return NULL;
  }

  filter = GetDictionaryValue( filters, name );

  if( !filter ){
    if( InitializeFilterByName( name ) != NULL )
      return NULL;
    filter = GetDictionaryValue( filters, name );
  }

  return filter;
}

void *
GetFilterOption
( const Filter * filter, const char * option )
{
  if( filter == NULL || option == NULL || filter->options == NULL )
    return NULL;

  return GetDictionaryValue( filter->options, option );
}

Status *
SetFilterOption
( Filter * filter, const char * option, void * value )
{
  Dictionary *result;

  if( !filter || !option )
    return RaiseStatus( "empty argument" );

  if( filter->options == NULL ){
    filter->options = NewDictionary();

    if( filter->options == NULL )
      return RaiseStatus( "dictionary failure" );
  }

  result =  SetDictionaryValue( filter->options, option, value );

  if( !result )
    return RaiseStatus( "dictionary failure" );
  else
    return NULL;
}
