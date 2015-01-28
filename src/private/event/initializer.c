#include <stdlib.h>

#include <stumpless/event.h>
#include <stumpless/exception.h>

#include "private/container/dictionary.h"
#include "private/event/initializer.h"
#include "private/level.h"

#define NEW_LEVEL_EVENT( event_name, function_name )                           \
Event *                                                                        \
New##function_name##Event                                                      \
( void )                                                                       \
{                                                                              \
  Event *event = malloc( sizeof( Event ) );                                    \
  if( !event )                                                                 \
    return NULL;                                                               \
                                                                               \
  event->name = event_name;                                                    \
  event->level = FindLevelByName( event_name );                                \
  event->attributes = NULL;                                                    \
                                                                               \
  return event;                                                                \
}

#define NEW_TYPE_EVENT( event_name, function_name )                            \
Event *                                                                        \
New##function_name##Event                                                      \
( void )                                                                       \
{                                                                              \
  Event *event = malloc( sizeof( Event ) );                                    \
  if( !event )                                                                 \
    return NULL;                                                               \
                                                                               \
  event->name = event_name;                                                    \
                                                                               \
  return event;                                                                \
}

#define ADD_EVENT( name, function )                                            \
SetDictionaryValue( initializers, name, New##function##Event );

static Dictionary *initializers = NULL;

Exception *
InitializeEventByName
( const char *name )
{
  Event *( *initializer )();

  if( !initializers ){
    initializers = NewDictionary();
    if( !initializers )
      return RaiseException( "constructor failure" );

    ADD_EVENT( "alert", Alert )
    ADD_EVENT( "char", Char )
    ADD_EVENT( "char array", CharArray )
    ADD_EVENT( "critical", Critical )
    ADD_EVENT( "debug", Debug )
    ADD_EVENT( "double", Double )
    ADD_EVENT( "double array", DoubleArray )
    ADD_EVENT( "emergency", Emergency )
    ADD_EVENT( "error", Error )
    ADD_EVENT( "float", Float )
    ADD_EVENT( "float array", FloatArray )
    ADD_EVENT( "informational", Informational )
    ADD_EVENT( "int", Int )
    ADD_EVENT( "long", Long )
    ADD_EVENT( "long array", LongArray )
    ADD_EVENT( "long double", LongDouble )
    ADD_EVENT( "long double array", LongDoubleArray )
    ADD_EVENT( "long long", LongLong )
    ADD_EVENT( "long long array", LongLongArray )
    ADD_EVENT( "notice", Notice )
    ADD_EVENT( "short", Short )
    ADD_EVENT( "short array", ShortArray )
    ADD_EVENT( "signed char", SignedChar )
    ADD_EVENT( "signed char array", SignedCharArray )
    ADD_EVENT( "string", String )
    ADD_EVENT( "string array", StringArray )
    ADD_EVENT( "unsigned char", UnsignedChar )
    ADD_EVENT( "unsigned char array", UnsignedCharArray )
    ADD_EVENT( "unsigned int", UnsignedInt )
    ADD_EVENT( "unsigned int array", UnsignedIntArray )
    ADD_EVENT( "unsigned long", UnsignedLong )
    ADD_EVENT( "unsigned long array", UnsignedLongArray )
    ADD_EVENT( "unsigned long long", UnsignedLongLong )
    ADD_EVENT( "unsigned long long array", UnsignedLongLongArray )
    ADD_EVENT( "unsigned short", UnsignedShort )
    ADD_EVENT( "unsigned short array", UnsignedShortArray )
    ADD_EVENT( "void", Void )
    ADD_EVENT( "warning", Warning )
  }

  initializer = GetDictionaryValue( initializers, name );
  if( !initializer ){
    return NULL;
  } else {
    AddEvent( initializer() );
    return NULL;
  }
}

NEW_LEVEL_EVENT( "alert", Alert )

NEW_TYPE_EVENT( "char", Char )

NEW_TYPE_EVENT( "char array", CharArray )

NEW_LEVEL_EVENT( "critical", Critical )

NEW_LEVEL_EVENT( "debug", Debug )

NEW_TYPE_EVENT( "double", Double )

NEW_TYPE_EVENT( "double array", DoubleArray )

NEW_LEVEL_EVENT( "emergency", Emergency )

NEW_LEVEL_EVENT( "error", Error )

NEW_TYPE_EVENT( "float", Float )

NEW_TYPE_EVENT( "float array", FloatArray )

NEW_LEVEL_EVENT( "informational", Informational )

NEW_TYPE_EVENT( "int", Int )

NEW_TYPE_EVENT( "int array", IntArray )

NEW_TYPE_EVENT( "long", Long )

NEW_TYPE_EVENT( "long array", LongArray )

NEW_TYPE_EVENT( "long double", LongDouble )

NEW_TYPE_EVENT( "long double array", LongDoubleArray )

NEW_TYPE_EVENT( "long long", LongLong )

NEW_TYPE_EVENT( "long long array", LongLongArray )

NEW_LEVEL_EVENT( "notice", Notice )

NEW_TYPE_EVENT( "short", Short )

NEW_TYPE_EVENT( "short array", ShortArray )

NEW_TYPE_EVENT( "signed char", SignedChar )

NEW_TYPE_EVENT( "signed char array", SignedCharArray )

NEW_TYPE_EVENT( "string", String )

NEW_TYPE_EVENT( "string array", StringArray )

NEW_TYPE_EVENT( "unsigned char", UnsignedChar )

NEW_TYPE_EVENT( "unsigned char array", UnsignedCharArray )

NEW_TYPE_EVENT( "unsigned int", UnsignedInt )

NEW_TYPE_EVENT( "unsigned int array", UnsignedIntArray )

NEW_TYPE_EVENT( "unsigned long", UnsignedLong )

NEW_TYPE_EVENT( "unsigned long array", UnsignedLongArray )

NEW_TYPE_EVENT( "unsigned long long", UnsignedLongLong )

NEW_TYPE_EVENT( "unsigned long long array", UnsignedLongLongArray )

NEW_TYPE_EVENT( "unsigned short", UnsignedShort )

NEW_TYPE_EVENT( "unsigned short array", UnsignedShortArray )

NEW_TYPE_EVENT( "void", Void )

NEW_LEVEL_EVENT( "warning", Warning )
