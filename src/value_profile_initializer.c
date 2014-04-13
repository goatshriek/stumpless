#include <stdlib.h>

#include "private/dictionary.h"
#include "private/status.h"
#include "private/type.h"
#include "private/value.h"
#include "private/value_profile.h"
#include "private/value_profile_initializer.h"

#include "private/formatter/text.h"

#define ADD_PROFILE( name, function )                                          \
SetDictionaryValue( initializers, name, Initialize##function##ValueProfile );

#define ARRAY_PROFILE_INITIALIZER( profile_name, type_name )                   \
ValueProfile *                                                                 \
Initialize##type_name##ArrayValueProfile                                       \
( void )                                                                       \
{                                                                              \
  ValueProfile * profile = malloc( sizeof( ValueProfile ) );                   \
  if( profile == NULL )                                                        \
    return NULL;                                                               \
                                                                               \
  profile->into_string = NULL;                                                 \
  profile->name = profile_name;                                                \
  profile->to_binary = NULL;                                                   \
  profile->to_csv = NULL;                                                      \
  profile->to_json = NULL;                                                     \
  profile->to_string = NULL;                                                   \
  profile->to_text = ArrayValueToText;                                         \
  profile->to_value_list = type_name##ArrayValueToValueList;                   \
  profile->to_xml = NULL;                                                      \
                                                                               \
  return profile;                                                              \
}

#define SINGULAR_PROFILE_INITIALIZER( profile_name, type_name )                \
ValueProfile *                                                                 \
Initialize##type_name##ValueProfile                                            \
( void )                                                                       \
{                                                                              \
  ValueProfile * profile = malloc( sizeof( ValueProfile ) );                   \
  if( profile == NULL )                                                        \
    return NULL;                                                               \
                                                                               \
  profile->into_string = type_name##ValueIntoString;                           \
  profile->name = profile_name;                                                \
  profile->to_binary = NULL;                                                   \
  profile->to_csv = NULL;                                                      \
  profile->to_json = NULL;                                                     \
  profile->to_string = type_name##ValueToString;                               \
  profile->to_text = SingularValueToText;                                      \
  profile->to_value_list = ValueToValueList;                                   \
  profile->to_xml = NULL;                                                      \
                                                                               \
  return profile;                                                              \
}

static Dictionary * initializers = NULL;

ARRAY_PROFILE_INITIALIZER( "boolean array", Boolean )
SINGULAR_PROFILE_INITIALIZER( "boolean", Boolean )

ARRAY_PROFILE_INITIALIZER( "char array", Char )
SINGULAR_PROFILE_INITIALIZER( "char", Char )

ARRAY_PROFILE_INITIALIZER( "float array", Float )
SINGULAR_PROFILE_INITIALIZER( "float", Float )

ARRAY_PROFILE_INITIALIZER( "double array", Double )
SINGULAR_PROFILE_INITIALIZER( "double", Double )

ARRAY_PROFILE_INITIALIZER( "int array", Int )
SINGULAR_PROFILE_INITIALIZER( "int", Int )

ARRAY_PROFILE_INITIALIZER( "long array", Long )
SINGULAR_PROFILE_INITIALIZER( "long", Long )

ARRAY_PROFILE_INITIALIZER( "long double array", LongDouble )
SINGULAR_PROFILE_INITIALIZER( "long double", LongDouble )

ARRAY_PROFILE_INITIALIZER( "long long array", LongLong )
SINGULAR_PROFILE_INITIALIZER( "long long", LongLong )

ARRAY_PROFILE_INITIALIZER( "short array", Short )
SINGULAR_PROFILE_INITIALIZER( "short", Short )

ARRAY_PROFILE_INITIALIZER( "signed char array", SignedChar )
SINGULAR_PROFILE_INITIALIZER( "signed char", SignedChar )

ARRAY_PROFILE_INITIALIZER( "string array", String )
SINGULAR_PROFILE_INITIALIZER( "string", String )

ARRAY_PROFILE_INITIALIZER( "unsigned char array", UnsignedChar )
SINGULAR_PROFILE_INITIALIZER( "unsigned char", UnsignedChar )

ARRAY_PROFILE_INITIALIZER( "unsigned int array", UnsignedInt )
SINGULAR_PROFILE_INITIALIZER( "unsigned int", UnsignedInt )

ARRAY_PROFILE_INITIALIZER( "unsigned long array", UnsignedLong )
SINGULAR_PROFILE_INITIALIZER( "unsigned long", UnsignedLong )

ARRAY_PROFILE_INITIALIZER( "unsigned long long array", UnsignedLongLong )
SINGULAR_PROFILE_INITIALIZER( "unsigned long long", UnsignedLongLong )

ARRAY_PROFILE_INITIALIZER( "unsigned short array", UnsignedShort )
SINGULAR_PROFILE_INITIALIZER( "unsigned short", UnsignedShort )

Status *
InitializeValueProfileByName
( const char * name )
{
  if( initializers == NULL ){
    
    initializers = NewDictionary();
    if( initializers == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
    
    ADD_PROFILE( "boolean array", BooleanArray  )
    ADD_PROFILE( "boolean", Boolean )
    ADD_PROFILE( "char array", CharArray )
    ADD_PROFILE( "char", Char )
    ADD_PROFILE( "float array", FloatArray )
    ADD_PROFILE( "float", Float )
    ADD_PROFILE( "double array", DoubleArray )
    ADD_PROFILE( "double", Double )
    ADD_PROFILE( "int array", IntArray )
    ADD_PROFILE( "int", Int )
    ADD_PROFILE( "long array", LongArray )
    ADD_PROFILE( "long", Long )
    ADD_PROFILE( "long double array", LongDoubleArray )
    ADD_PROFILE( "long double", LongDouble )
    ADD_PROFILE( "long long array", LongLongArray )
    ADD_PROFILE( "long long", LongLong )
    ADD_PROFILE( "short array", ShortArray )
    ADD_PROFILE( "short", Short )
    ADD_PROFILE( "signed char array", SignedCharArray )
    ADD_PROFILE( "signed char", SignedChar )
    ADD_PROFILE( "string array", StringArray )
    ADD_PROFILE( "string", String )
    ADD_PROFILE( "unsigned char array", UnsignedCharArray )
    ADD_PROFILE( "unsigned char", UnsignedChar )
    ADD_PROFILE( "unsigned int array", UnsignedIntArray )
    ADD_PROFILE( "unsigned int", UnsignedInt )
    ADD_PROFILE( "unsigned long array", UnsignedLongArray )
    ADD_PROFILE( "unsigned long", UnsignedLong )
    ADD_PROFILE( "unsigned long long array", UnsignedLongLongArray )
    ADD_PROFILE( "unsigned long long", UnsignedLongLong )
    ADD_PROFILE( "unsigned short array", UnsignedShortArray )
    ADD_PROFILE( "unsigned short", UnsignedShort )
  }
  
  ValueProfile * ( *initializer )();
  initializer = GetDictionaryValue( initializers, name );
  if( initializer == NULL )
    return NULL;
  else 
    return AddValueProfile( initializer() );
}
