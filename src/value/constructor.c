#include <stdlib.h>
#include <string.h>

#include <stumpless/value/constructor.h>
#include <stumpless/value/profile.h>

#include "private/type.h"

#define VALUE_FROM_FUNCTIONS( name, type, member )                             \
Value *                                                                        \
NewValueFor##name                                                              \
( type element )                                                               \
{                                                                              \
  Value *value;                                                                \
                                                                               \
  value = malloc( sizeof( Value ) );                                           \
  if( !value )                                                                 \
    return NULL;                                                               \
                                                                               \
  value->profile = FindValueProfileByName( #type );                            \
  if( !value->profile )                                                        \
    return NULL;                                                               \
                                                                               \
  value->member = element;                                                     \
                                                                               \
  return value;                                                                \
}                                                                              \
                                                                               \
Value *                                                                        \
NewValueFor##name##Array                                                       \
( const type *array, size_t length )                                           \
{                                                                              \
  Value *value;                                                                \
                                                                               \
  if( !array || !length )                                                      \
    return NULL;                                                               \
                                                                               \
  value = malloc( sizeof( Value ) );                                           \
  if( !value )                                                                 \
    return NULL;                                                               \
                                                                               \
  value->profile = FindValueProfileByName( #type " array" );                   \
  if( !value->profile )                                                        \
    return NULL;                                                               \
                                                                               \
  value->member##_p = malloc( sizeof( type ) * length );                       \
  if( !value->member##_p )                                                     \
    return NULL;                                                               \
                                                                               \
  memcpy( value->member##_p, array, length );                                  \
                                                                               \
  value->length = length;                                                      \
                                                                               \
  return value;                                                                \
}



Value *
NewValueForBoolean( const Boolean * boolean )
{
  Value *value;

  if( !boolean )
    return NULL;

  value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->profile = FindValueProfileByName( "boolean" );
  if( !value->profile )
    return NULL;

  value->v_p = malloc( sizeof( Boolean ) );
  if( !value->v_p )
    return NULL;

  memcpy( value->v_p, boolean, sizeof( Boolean ) );

  return value;
}

VALUE_FROM_FUNCTIONS( Char, char, c )

VALUE_FROM_FUNCTIONS( Double, double, d )

VALUE_FROM_FUNCTIONS( Float, float, f )

VALUE_FROM_FUNCTIONS( Int, int, i )

VALUE_FROM_FUNCTIONS( Long, long, l )

VALUE_FROM_FUNCTIONS( LongDouble, long double, l_d )

VALUE_FROM_FUNCTIONS( LongLong, long long, l_l )

VALUE_FROM_FUNCTIONS( Short, short, s )

VALUE_FROM_FUNCTIONS( SignedChar, signed char, s_c )

Value *
NewValueForString( const char *str )
{
  Value *value;

  if( !str )
    return NULL;

  value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->profile = FindValueProfileByName( "string" );
  if( !value->profile )
    return NULL;

  value->length = strlen( str ) + 1;
  value->c_p = malloc( sizeof( char ) * value->length );
  if( !value->c_p )
    return NULL;

  memcpy( value->c_p, str, value->length );

  return value;
}

VALUE_FROM_FUNCTIONS( UnsignedChar, unsigned char, u_c )

VALUE_FROM_FUNCTIONS( UnsignedInt, unsigned int, u_i )

VALUE_FROM_FUNCTIONS( UnsignedLong, unsigned long, u_l )

VALUE_FROM_FUNCTIONS( UnsignedLongLong, unsigned long long, u_l_l )

VALUE_FROM_FUNCTIONS( UnsignedShort, unsigned short, u_s )

Value *
NewValueForVoid
( void *pointer )
{
  Value *value;

  if( !pointer )
    return NULL;

  value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->profile = FindValueProfileByName( "void" );
  if( !value->profile )
    return NULL;

  value->v_p = pointer;
  if( !value->v_p )
    return NULL;

  return value;
}
