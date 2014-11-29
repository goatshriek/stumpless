#include <stdlib.h>

#include "private/comparator.h"
#include "private/comparator/initializer.h"
#include "private/container/dictionary.h"
#include "private/status.h"
#include "private/type.h"

static Dictionary * comparators = NULL;

Status *
AddComparator
( Comparator *comparator )
{
  void *value;

  if( !comparator || !comparator->name )
    return NULL;

  if( !comparators ){
    comparators = NewDictionary();

    if( !comparators )
      return RaiseStatus( "constructor failure" );
  }

  value = ( void * ) comparator;
  if( !SetDictionaryValue( comparators, comparator->name, value ) )
    return NULL;

  return NULL;
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

Status *
SetComparatorOption
( Comparator *comparator, const char *option, void *value )
{
  Dictionary *result;

  if( !comparator || !option )
    return RaiseStatus( "empty argument" );

  if( !comparator->options ){
    comparator->options = NewDictionary();

    if( !comparator->options )
      return RaiseStatus( "dictionary failure" );
  }

  result =  SetDictionaryValue( comparator->options, option, value );

  if( !result )
    return RaiseStatus( "dictionary failure" );
  else
    return NULL;
}
