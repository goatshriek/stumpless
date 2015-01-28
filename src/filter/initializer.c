#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/dictionary.h"
#include "private/filter.h"
#include "private/filter/base.h"
#include "private/filter/initializer.h"
#include "private/type.h"

#define ADD_FILTER( name, function )                                           \
SetDictionaryValue( initializers, name, Initialize##function##Filter );

#define FILTER_INITIALIZER_FUNCTION( filter_name, function_name )              \
Filter *                                                                       \
Initialize##function_name##Filter                                              \
( void )                                                                       \
{                                                                              \
  Filter * filter = malloc( sizeof( Filter ) );                                \
  if( filter == NULL )                                                         \
    return NULL;                                                               \
                                                                               \
  filter->name = filter_name;                                                  \
                                                                               \
  filter->accept_record = function_name##FilterAcceptRecord;                   \
  filter->accept_output = function_name##FilterAcceptOutput;                   \
  filter->accept_value = function_name##FilterAcceptValue;                     \
                                                                               \
  filter->options = NULL;                                                      \
                                                                               \
  return filter;                                                               \
}

static Dictionary *initializers = NULL;

FILTER_INITIALIZER_FUNCTION( "empty", Empty )

Exception *
InitializeFilterByName
( const char *name )
{
  Filter *( *initializer )();

  if( !initializers ){
    initializers = NewDictionary();
    if( !initializers )
      return RaiseException( "constructor failure" );

    ADD_FILTER( "empty", Empty )
    ADD_FILTER( "level", Level )
  }

  initializer = GetDictionaryValue( initializers, name );
  if( !initializer ){
    return NULL;
  } else {
    AddFilter( initializer() );
    return NULL;
  }
}

FILTER_INITIALIZER_FUNCTION( "level", Level )
