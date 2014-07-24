#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/container/list/handler.h"
#include "private/formatter.h"
#include "private/formatter/initializer.h"
#include "private/status.h"
#include "private/type.h"

static Dictionary *formatters = NULL;

Status *
AddFormatter
( Formatter * formatter )
{
  if( formatter == NULL || formatter->name == NULL )
    return NULL;

  if( formatters == NULL ){
    formatters = NewDictionary();

    if( formatters == NULL )
      return RaiseStatus( "constructor failure" );
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
    return RaiseStatus( "empty argument" );

  if( !formatter->handlers ){
    formatter->handlers = NewHandlerList();
    if( !formatter->handlers )
      return RaiseStatus( "constructor failure" );
  }

  if( !AppendToHandlerList( formatter->handlers, handler ) )
    return RaiseStatus( "list failure" );

  return NULL;
}

void
DestroyFormatter
( Formatter *formatter )
{
  if( !formatter )
    return;

  DestroyFilterList( formatter->filters );
  DestroyHandlerList( formatter->handlers );
  DestroyDictionary( formatter->options );

  free( formatter );

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
    return RaiseStatus( "empty argument" );

  if( formatter->options == NULL ){
    formatter->options = NewDictionary();

    if( formatter->options == NULL )
      return RaiseStatus( "dictionary failure" );
  }

  Dictionary * result;
  result =  SetDictionaryValue( formatter->options, option, value );

  if( result == NULL )
    return RaiseStatus( "dictionary failure" );
  else
    return NULL;
}
