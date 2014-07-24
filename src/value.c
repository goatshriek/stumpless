#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private/boolean.h"
#include "private/configuration.h"
#include "private/container/list/value.h"
#include "private/status.h"
#include "private/status/checker.h"
#include "private/type.h"
#include "private/value.h"
#include "private/value/constructor.h"


#define ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( name, data_member )                \
ValueList *                                                                    \
name##ArrayValueToValueList                                                    \
( const Value *value )                                                         \
{                                                                              \
  if( !value || !value->data || !value->data->data_member )                    \
    return NULL;                                                               \
                                                                               \
  ValueList *list = NewValueList();                                            \
  if( !list )                                                                  \
    return NULL;                                                               \
                                                                               \
  Type *data = value->data;                                                    \
  Value *value_i;                                                              \
  unsigned i;                                                                  \
                                                                               \
  for( i = 0; i < value->length; i++ ){                                        \
    value_i = ValueFrom##name( data->data_member[i] );                         \
    if( !AppendToValueList( list, value_i ) )                                  \
      return NULL;                                                             \
  }                                                                            \
                                                                               \
  return list;                                                                 \
}

#define VALUE_INTO_STRING_FUNCTION( name, data_member, default_format )        \
Status *                                                                       \
name##ValueIntoString                                                          \
( char * str, const Value * value )                                            \
{                                                                              \
  if( !str || !value || !value->data )                                         \
    return RaiseStatus( "empty argument" );                            \
                                                                               \
  const char * format = value->format ? value->format : default_format;        \
                                                                               \
  str[0] = '\0';                                                               \
  int result = sprintf( str, format, value->data->data_member );               \
  if( result < 0 )                                                             \
    return RaiseStatus( "string write failure" );                      \
                                                                               \
  return NULL;                                                                 \
}

// todo this function can be adapted to no longer rely on the buffer, if
// snprintf is available. Create configuration check to handle this case
#define VALUE_TO_STRING_FUNCTION( name, data_member, default_format )          \
char *                                                                         \
name##ValueToString( const Value * value )                                     \
{                                                                              \
  if( !value || !value->data )                                                 \
    return NULL;                                                               \
                                                                               \
  const char * format = value->format ? value->format : default_format;        \
                                                                               \
  Configuration * configuration = GetConfiguration();                          \
  if( !configuration )                                                         \
    return NULL;                                                               \
                                                                               \
  size_t buffer_size = configuration->string->buffer_size;                     \
  size_t buffer_length = buffer_size - 1;                                      \
  char * buffer = malloc( sizeof( char ) * buffer_size );                      \
  if( !buffer )                                                                \
    return NULL;                                                               \
                                                                               \
  buffer[0] = '\0';                                                            \
  int result = sprintf( buffer, format, value->data->data_member );            \
  if( result < 0 )                                                             \
    return NULL;                                                               \
  buffer[buffer_length] = '\0';                                                \
                                                                               \
  size_t required_length = strlen( buffer );                                   \
  free( buffer );                                                              \
                                                                               \
  char * str = malloc( sizeof( char ) * ( required_length + 1 ) );             \
  if( !str )                                                                   \
    return NULL;                                                               \
                                                                               \
  str[0] = '\0';                                                               \
  result = sprintf( str, format, value->data->data_member );                   \
  if( result < 0 )                                                             \
    return NULL;                                                               \
  str[required_length] = '\0';                                                 \
                                                                               \
  return str;                                                                  \
}

ValueList *
BooleanArrayValueToValueList
( const Value *value )
{
  if( !value || !value->data || !value->data->v_p )
    return NULL;

  ValueList *list = NewValueList();
  if( !list )
    return NULL;

  const Boolean **boolean_list = ( const Boolean ** ) value->data->v_p;
  Value *boolean_value;

  unsigned i;
  for( i = 0; i < value->length; i++ ){
    boolean_value = ValueFromBoolean( boolean_list[i] );
    if( !AppendToValueList( list, boolean_value ) )
      return NULL;
  }

  return list;
}

Status *
BooleanValueIntoString
( char *str, const Value *value )
{
  // todo need to implement
  return NULL;
}

char *
BooleanValueToString
( const Value *value )
{
  if( !value || !value->data || !value->data->v_p )
    return NULL;

  Boolean *boolean = ( Boolean * ) value->data->v_p;

  const char *description;
  if( boolean->value )
    description = boolean->format->true_description;
  else
    description = boolean->format->false_description;

  size_t str_length = strlen( description );

  char *str = malloc( sizeof( char ) * ( str_length + 1 ) );
  if( !str )
    return NULL;

  str[0] = '\0';
  strncpy( str, description, str_length );
  str[str_length] = '\0';

  return str;
}

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Char, c_p )

VALUE_INTO_STRING_FUNCTION( Char, c, "%c" )

VALUE_TO_STRING_FUNCTION( Char, c, "%c" )

Value *
CopyValue
( const Value *value )
{
  if( !value )
    return NULL;

  Value *copy = malloc( sizeof( Value ) );
  if( !copy )
    return NULL;

  copy->data = value->data;
  copy->format = value->format;
  copy->length = value->length;
  copy->profile = value->profile;

  return copy;
}

void
DestroyValue
( Value *value )
{
  if( !value )
    return;

  free( value->data );

  free( value );

  return;
}

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Double, d_p )

VALUE_INTO_STRING_FUNCTION( Double, d, "%g" )

VALUE_TO_STRING_FUNCTION( Double, d, "%g" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Float, f_p )

VALUE_INTO_STRING_FUNCTION( Float, f, "%g" )

VALUE_TO_STRING_FUNCTION( Float, f, "%g" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Int, i_p )

VALUE_INTO_STRING_FUNCTION( Int, i, "%i" )

VALUE_TO_STRING_FUNCTION( Int, i, "%i" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Long, l_p )

VALUE_INTO_STRING_FUNCTION( Long, l, "%li" )

VALUE_TO_STRING_FUNCTION( Long, l, "%li" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( LongDouble, l_d_p )

VALUE_INTO_STRING_FUNCTION( LongDouble, l_d, "%Lg" )

VALUE_TO_STRING_FUNCTION( LongDouble, l_d, "%Lg" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( LongLong, l_l_p )

VALUE_INTO_STRING_FUNCTION( LongLong, l_l, "%lli" )

VALUE_TO_STRING_FUNCTION( LongLong, l_l, "%lli" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Short, s_p )

VALUE_INTO_STRING_FUNCTION( Short, s, "%hi" )

VALUE_TO_STRING_FUNCTION( Short, s, "%hi" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( SignedChar, s_c_p )

VALUE_INTO_STRING_FUNCTION( SignedChar, s_c, "%c" )

VALUE_TO_STRING_FUNCTION( SignedChar, s_c, "%c" )

ValueList *
StringArrayValueToValueList
( const Value *value )
{
  if( !value || !value->data || !value->data->v_p )
    return NULL;

  ValueList *list = NewValueList();
  if( !list )
    return NULL;

  const char **string_list = ( const char ** ) value->data->v_p;
  Value *string_value;

  unsigned i;
  for( i = 0; i < value->length; i++ ){
    string_value = ValueFromString( string_list[i] );
    if( !AppendToValueList( list, string_value ) )
      return NULL;
  }

  return list;
}

Status *
StringValueIntoString
( char *str, const Value *value )
{
  // todo need to implement
  return NULL;
}

char *
StringValueToString
( const Value *value )
{
  if( !value || !value->data || !value->data->c_p )
    return NULL;

  size_t str_length = strlen( value->data->c_p );

  char *str = malloc( sizeof( char ) * ( str_length + 1 ) );
  if( !str )
    return NULL;

  str[0] = '\0';
  strncpy( str, value->data->c_p, str_length );
  str[str_length] = '\0';

  return str;
}

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( UnsignedChar, u_c_p )

VALUE_INTO_STRING_FUNCTION( UnsignedChar, u_c, "%c" )

VALUE_TO_STRING_FUNCTION( UnsignedChar, u_c, "%c" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( UnsignedInt, u_i_p )

VALUE_INTO_STRING_FUNCTION( UnsignedInt, u_i, "%u" )

VALUE_TO_STRING_FUNCTION( UnsignedInt, u_i, "%u" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( UnsignedLong, u_l_p )

VALUE_INTO_STRING_FUNCTION( UnsignedLong, u_l, "%lu" )

VALUE_TO_STRING_FUNCTION( UnsignedLong, u_l, "%lu" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( UnsignedLongLong, u_l_l_p )

VALUE_INTO_STRING_FUNCTION( UnsignedLongLong, u_l_l, "%llu" )

VALUE_TO_STRING_FUNCTION( UnsignedLongLong, u_l_l, "%llu" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( UnsignedShort, u_s_p )

VALUE_INTO_STRING_FUNCTION( UnsignedShort, u_s, "%hu" )

VALUE_TO_STRING_FUNCTION( UnsignedShort, u_s, "%hu" )

Status *
ValueIntoString
( char *str, const Value *value )
{
  if( !value )
    return RaiseStatus( "empty argument" );

  if( !value->profile || !value->profile->into_string )
    return RaiseStatus( "malformed structure" );

  return value->profile->into_string( str, value );
}

char *
ValueToString
( const Value *value )
{
  if( !value || !value->profile || !value->profile->to_string )
    return NULL;

  return value->profile->to_string( value );
}

ValueList *
ValueToValueList
( const Value *value )
{
  if( !value )
    return NULL;

  ValueList *list = NewValueList();
  if( !list )
    return NULL;

  if( !AppendToValueList( list, CopyValue( value ) ) )
    return NULL;

  return list;
}
