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
  Value *value = malloc( sizeof( Value ) );                                    \
  if( !value )                                                                 \
    return NULL;                                                               \
                                                                               \
  value->data = malloc( sizeof( Data ) );                                      \
  if( !value->data )                                                           \
    return NULL;                                                               \
                                                                               \
  value->profile = FindValueProfileByName( #type );                            \
  if( !value->profile )                                                        \
    return NULL;                                                               \
                                                                               \
  value->data->member = element;                                               \
                                                                               \
  return value;                                                                \
}                                                                              \
                                                                               \
Value *                                                                        \
NewValueFor##name##Array                                                       \
( const type *array, size_t length )                                           \
{                                                                              \
  if( !array || !length )                                                      \
    return NULL;                                                               \
                                                                               \
  Value *value = malloc( sizeof( Value ) );                                    \
  if( !value )                                                                 \
    return NULL;                                                               \
                                                                               \
  value->data = malloc( sizeof( Value ) );                                     \
  if( !value->data )                                                           \
    return NULL;                                                               \
                                                                               \
  value->profile = FindValueProfileByName( #type " array" );                   \
  if( !value->profile )                                                        \
    return NULL;                                                               \
                                                                               \
  value->data->member##_p = malloc( sizeof( type ) * length );                 \
  if( !value->data->member##_p )                                               \
    return NULL;                                                               \
                                                                               \
  memcpy( value->data->member##_p, array, length );                            \
                                                                               \
  value->length = length;                                                      \
                                                                               \
  return value;                                                                \
}



Value *
NewValueForBoolean( const Boolean * boolean )
{
  if( !boolean )
    return NULL;

  Value *value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( !value->data )
    return NULL;

  value->profile = FindValueProfileByName( "boolean" );
  if( !value->profile )
    return NULL;

  value->data->v_p = malloc( sizeof( Boolean ) );
  if( !value->data->v_p )
    return NULL;

  memcpy( value->data->v_p, boolean, sizeof( Boolean ) );

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
  if( !str )
    return NULL;

  Value *value = malloc( sizeof( Value ) );
  if( !value )
    return NULL;

  value->data = malloc( sizeof( Data ) );
  if( !value->data )
    return NULL;

  value->profile = FindValueProfileByName( "string" );
  if( !value->profile )
    return NULL;

  value->length = strlen( str ) + 1;
  value->data->c_p = malloc( sizeof( char ) * value->length );
  if( !value->data->c_p )
    return NULL;

  memcpy( value->data->c_p, str, value->length );

  return value;
}

VALUE_FROM_FUNCTIONS( UnsignedChar, unsigned char, u_c )

VALUE_FROM_FUNCTIONS( UnsignedInt, unsigned int, u_i )

VALUE_FROM_FUNCTIONS( UnsignedLong, unsigned long, u_l )

VALUE_FROM_FUNCTIONS( UnsignedLongLong, unsigned long long, u_l_l )

VALUE_FROM_FUNCTIONS( UnsignedShort, unsigned short, u_s )

Value *
NewValueForVoid
( const void *value )
{
  return NULL;
}
