#include <stdlib.h>

#include "private/dictionary.h"
#include "private/filter.h"
#include "private/filter_initializer.h"
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
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  void * value = ( void * ) filter;
  if( AddValueToDictionary( filters, filter->name, value ) == NULL )
    return NULL;
  
  return NULL;
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
  
  Filter * filter = GetValueFromDictionary( filters, name );
  
  if( filter == NULL ){
    if( InitializeFilterByName( name ) != NULL )
      return NULL;
    filter = GetValueFromDictionary( filters, name );
  }
  
  return filter;
}
