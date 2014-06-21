#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/filter.h"
#include "private/filter_base.h"
#include "private/filter_initializer.h"
#include "private/status.h"
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
  filter->accept_entry = function_name##FilterAcceptEntry;                     \
  filter->accept_output = function_name##FilterAcceptOutput;                   \
  filter->accept_value = function_name##FilterAcceptValue;                     \
                                                                               \
  filter->options = NULL;                                                      \
                                                                               \
  return filter;                                                               \
}

static Dictionary * initializers = NULL;

FILTER_INITIALIZER_FUNCTION( "empty", Empty )

Status *
InitializeFilterByName
( const char * name )
{
  if( initializers == NULL ){
    
    initializers = NewDictionary();
    if( initializers == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
    
    ADD_FILTER( "empty", Empty )
    ADD_FILTER( "level", Level )
  }
  
  Filter * ( *initializer )();
  initializer = GetDictionaryValue( initializers, name );
  if( initializer == NULL )
    return NULL;
  else 
    return AddFilter( initializer() );
}

FILTER_INITIALIZER_FUNCTION( "level", Level )
