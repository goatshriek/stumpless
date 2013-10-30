#include <stdlib.h>

#include "private/dictionary.h"
#include "private/filter.h"
#include "private/filter_initializer.h"
#include "private/status.h"

#define ADD_FILTER( name, function )                                           \
AddValueToDictionary( initializers, name, Initialize##function##Filter );

static Dictionary * initializers = NULL;

Filter *
InitializeEmptyFilter
( void )
{
  Filter * filter = malloc( sizeof( Filter ) );
  if( filter == NULL )
    return NULL;
  
  filter->name = "empty";
  
  filter->accept_entry = NULL;
  filter->accept_output = NULL;
  filter->accept_value = NULL;
  
  return filter;
}

Status *
InitializeFilterByName
( const char * name )
{
  if( initializers == NULL ){
    
    initializers = NewDictionary();
    if( initializers == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
    
    ADD_FILTER( "empty", Empty )
  }
  
  Filter * ( *initializer )();
  initializer = GetValueFromDictionary( initializers, name );
  if( initializer == NULL )
    return NULL;
  else 
    return AddFilter( initializer() );
}
