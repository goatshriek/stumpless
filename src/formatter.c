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

Formatter *
AddFormatter
( Formatter *formatter )
{
  if( !formatter || !formatter->name )
    return formatter;

  if( !formatters ){
    formatters = NewDictionary();

    if( !formatters )
      return formatter;
  }

  SetDictionaryValue( formatters, formatter->name, ( void * ) formatter );

  return formatter;
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

  if( !formatter )
    return InitializeFormatterByName( name );

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

Formatter *
SetFormatterOption
( Formatter *formatter, const char *option, void *value )
{
  if( !formatter || !option )
    return formatter;

  if( !formatter->options )
    formatter->options = NewDictionary();

  SetDictionaryValue( formatter->options, option, value );

  return formatter;
}
