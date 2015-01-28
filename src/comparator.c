#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/comparator.h"
#include "private/comparator/initializer.h"
#include "private/container/dictionary.h"
#include "private/type.h"

static Dictionary * comparators = NULL;

Comparator *
AddComparator
( Comparator *comparator )
{
  if( !comparator || !comparator->name )
    return NULL;

  if( !comparators ){
    comparators = NewDictionary();

    // todo throw constructor failure exception
    if( !comparators )
      return comparator;
  }

  SetDictionaryValue( comparators, comparator->name, ( void * ) comparator );

  return comparator;
}

void
DestroyComparator
( Comparator *comparator )
{
  if( !comparator )
    return;

  DestroyDictionary( comparator->options );
  free( comparator );

  return;
}

Comparator *
FindComparatorByName
( const char * name )
{
  Comparator *comparator;

  if( !comparators ){
    comparators = NewDictionary();

    if( !comparators )
      return NULL;
  }

  comparator = GetDictionaryValue( comparators, name );

  if( !comparator ){
    if( InitializeComparatorByName( name ) )
      return NULL;
    comparator = GetDictionaryValue( comparators, name );
  }

  return comparator;
}

void *
GetComparatorOption
( const Comparator * comparator, const char * option )
{
  if( !comparator || !option || !comparator->options )
    return NULL;

  return GetDictionaryValue( comparator->options, option );
}

Comparator *
SetComparatorOption
( Comparator *comparator, const char *option, void *value )
{
  if( !comparator || !option )
    return comparator;

  if( !comparator->options ){
    comparator->options = NewDictionary();

    // todo throw dictionary constructor failure
    if( !comparator->options )
      return comparator;
  }

  SetDictionaryValue( comparator->options, option, value );

  return comparator;
}
