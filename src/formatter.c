#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/formatter.h"
#include "private/status.h"
#include "private/type.h"

#include "private/formatter/initializer.h"

#include "private/container/list/handler.h"

static Dictionary * formatters = NULL;

Status *
AddFormatter
( Formatter * formatter )
{
  if( formatter == NULL || formatter->name == NULL )
    return NULL;
  
  if( formatters == NULL ){
    formatters = NewDictionary();
    
    if( formatters == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  void * value = ( void * ) formatter;
  if( SetDictionaryValue( formatters, formatter->name, value ) == NULL )
    return NULL;
  
  return NULL;
}

Status *
AppendHandlerToFormatter
( Formatter * formatter, Handler * handler )
{
  if( !formatter || !handler )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( !formatter->handlers ){
    formatter->handlers = NewHandlerList();
    if( !formatter->handlers )
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  if( !AppendToHandlerList( formatter->handlers, handler ) )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

// todo implement
void
DestroyFormatter
( Formatter *formatter )
{
  return;
}

Formatter *
FindFormatterByName
( const char * name )
{
  if( formatters == NULL ){
    formatters = NewDictionary();
    
    if( formatters == NULL )
      return NULL;
  }
  
  Formatter * formatter = GetDictionaryValue( formatters, name );
  
  if( formatter == NULL ){
    if( InitializeFormatterByName( name ) != NULL )
      return NULL;
    formatter = GetDictionaryValue( formatters, name );
  }
  
  return formatter;
}

void *
GetFormatterOption
( const Formatter * formatter, const char * option )
{
  if( formatter == NULL || option == NULL || formatter->options == NULL )
    return NULL;
  
  return GetDictionaryValue( formatter->options, option );
}

Status *
SetFormatterOption
( Formatter * formatter, const char * option, void * value )
{
  if( formatter == NULL || option == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( formatter->options == NULL ){
    formatter->options = NewDictionary();
    
    if( formatter->options == NULL )
      return RaiseAbnormalStatus( "dictionary failure" );
  }
  
  Dictionary * result;
  result =  SetDictionaryValue( formatter->options, option, value );
  
  if( result == NULL )
    return RaiseAbnormalStatus( "dictionary failure" );
  else
    return NULL;
}
