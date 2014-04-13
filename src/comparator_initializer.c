#include <stdlib.h>

#include "private/comparator.h"
#include "private/comparator_base.h"
#include "private/comparator_initializer.h"
#include "private/dictionary.h"
#include "private/status.h"
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

static Dictionary * initializers = NULL;

Status *
InitializeComparatorByName
( const char * name )
{
  if( !initializers ){
    
    initializers = NewDictionary();
    if( !initializers )
      return RaiseAbnormalStatus( "constructor failure" );
    
    ADD_COMPARATOR( "string", String )
  }
  
  Comparator * ( *initializer )();
  initializer = GetDictionaryValue( initializers, name );
  if( !initializer )
    return NULL;
  else 
    return AddComparator( initializer() );
}

COMPARATOR_INITIALIZER_FUNCTION( "string", String )
