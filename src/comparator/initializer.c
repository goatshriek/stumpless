#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/comparator.h"
#include "private/comparator/base.h"
#include "private/comparator/initializer.h"
#include "private/container/dictionary.h"
#include "private/type.h"

#define ADD_COMPARATOR( name, function )                                       \
SetDictionaryValue( initializers, name, Initialize##function##Comparator );

#define COMPARATOR_INITIALIZER_FUNCTION( comparator_name, function_name )      \
Comparator *                                                                   \
Initialize##function_name##Comparator                                          \
( void )                                                                       \
{                                                                              \
  Comparator * comparator = malloc( sizeof( Comparator ) );                    \
  if( !comparator )                                                            \
    return NULL;                                                               \
                                                                               \
  comparator->name = comparator_name;                                          \
  comparator->compare = function_name##ComparatorCompare;                      \
  comparator->options = NULL;                                                  \
                                                                               \
  return comparator;                                                           \
}

static Dictionary *initializers = NULL;

Exception *
InitializeComparatorByName
( const char *name )
{
  Comparator *( *initializer )();

  if( !initializers ){
    initializers = NewDictionary();
    if( !initializers )
      return RaiseException( "constructor failure" );

    ADD_COMPARATOR( "string", String )
  }

  initializer = GetDictionaryValue( initializers, name );
  if( !initializer ){
    return NULL;
  } else {
    AddComparator( initializer() );
    return NULL;
  }
}

COMPARATOR_INITIALIZER_FUNCTION( "string", String )
