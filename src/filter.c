#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/dictionary.h"
#include "private/filter.h"
#include "private/filter/initializer.h"
#include "private/type.h"

static Dictionary *filters = NULL;

Filter *
AddFilter
( Filter * filter )
{
  if( !filter || !filter->name )
    return filter;

  if( !filters ){
    filters = NewDictionary();

    // todo throw constructor Exception
    if( !filters )
      return filter;
  }

  SetDictionaryValue( filters, filter->name, ( void * ) filter );

  return filter;
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
( const Filter *filter, const char *option )
{
  if( !filter )
    return NULL;

  return GetDictionaryValue( filter->options, option );
}

Filter *
SetFilterOption
( Filter *filter, const char *option, void *value )
{
  if( !filter || !option )
    return filter;

  if( !filter->options ){
    filter->options = NewDictionary();

    // todo throw constructor failure Exception
    if( !filter->options )
      return filter;
  }

  SetDictionaryValue( filter->options, option, value );

  return filter;
}
