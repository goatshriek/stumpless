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
  if( filter == NULL || filter->name == NULL )
    return NULL;

  if( filters == NULL ){
    filters = NewDictionary();

    if( filters == NULL )
      return RaiseStatus( "constructor failure" );
  }

  void * value = ( void * ) filter;
  if( SetDictionaryValue( filters, filter->name, value ) == NULL )
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
  if( filters == NULL ){
    filters = NewDictionary();

    if( filters == NULL )
      return NULL;
  }

  Filter * filter = GetDictionaryValue( filters, name );

  if( filter == NULL ){
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
  if( filter == NULL || option == NULL )
    return RaiseStatus( "empty argument" );

  if( filter->options == NULL ){
    filter->options = NewDictionary();

    if( filter->options == NULL )
      return RaiseStatus( "dictionary failure" );
  }

  Dictionary * result;
  result =  SetDictionaryValue( filter->options, option, value );

  if( result == NULL )
    return RaiseStatus( "dictionary failure" );
  else
    return NULL;
}
