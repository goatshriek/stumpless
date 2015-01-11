#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/dictionary.h"
#include "private/container/list/filter.h"
#include "private/container/list/formatter.h"
#include "private/container/list/handler.h"
#include "private/formatter.h"
#include "private/formatter/initializer.h"
#include "private/type.h"

static Dictionary *formatters = NULL;

Exception *
AddFormatter
( Formatter * formatter )
{
  void *value;

  if( !formatter || !formatter->name )
    return NULL;

  if( !formatters ){
    formatters = NewDictionary();

    if( !formatters )
      return RaiseException( "constructor failure" );
  }

  value = ( void * ) formatter;
  if( !SetDictionaryValue( formatters, formatter->name, value ) )
    return NULL;

  return NULL;
}

void
DestroyFormatter
( Formatter *formatter )
{
  if( !formatter )
    return;

  DestroyFilterList( formatter->filters );
  DestroyDictionary( formatter->options );

  free( formatter );

  return;
}

Formatter *
FindFormatterByName
( const char *name )
{
  Formatter *formatter;

  if( !formatters ){
    formatters = NewDictionary();

    if( !formatters )
      return NULL;
  }

  formatter = GetDictionaryValue( formatters, name );

  if( !formatter ){
    if( InitializeFormatterByName( name ) )
      return NULL;
    formatter = GetDictionaryValue( formatters, name );
  }

  return formatter;
}

Output *
FormatRecord
( const Formatter *formatter, const Record *record )
{
  if( !formatter || !formatter->format )
    return NULL;

  return formatter->format( formatter, record );
}

void *
GetFormatterOption
( const Formatter *formatter, const char *option )
{
  if( !formatter || !option || !formatter->options )
    return NULL;

  return GetDictionaryValue( formatter->options, option );
}

Exception *
SetFormatterOption
( Formatter * formatter, const char * option, void * value )
{
  if( !formatter || !option )
    return RaiseException( "empty argument" );

  if( !formatter->options ){
    formatter->options = NewDictionary();

    if( !formatter->options )
      return RaiseException( "dictionary failure" );
  }

  if( !SetDictionaryValue( formatter->options, option, value ) )
    return RaiseException( "dictionary failure" );
  else
    return NULL;
}
