#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stumpless/config/check.h>
#include <stumpless/exception.h>
#include <stumpless/value.h>
#include <stumpless/value/constructor.h>

#include "private/boolean.h"
#include "private/configuration.h"
#include "private/container/list/value.h"
#include "private/exception/checker.h"
#include "private/string_helper.h"
#include "private/type.h"

#define ARRAY_VALUE_INTO_STRING_FUNCTION( name, data_member, default_format )  \
char *                                                                         \
name##ArrayValueIntoString                                                     \
( char *str, const Value *value, size_t length )                               \
{                                                                              \
  const char *format;                                                          \
  size_t i, current_position = 0, remaining_length;                            \
                                                                               \
  if( !str || !value || length == 0 )                                          \
    return str;                                                                \
                                                                               \
  format = value->format ? value->format : default_format;                     \
                                                                               \
  str[0] = '[';                                                                \
  if( length > 1 )                                                             \
    str[1] = '\0';                                                             \
  else                                                                         \
    return NULL;                                                               \
                                                                               \
  for( i = 0; i < value->length; i++ ){                                        \
    current_position += strlen( str + current_position );                      \
    if( length < current_position )                                            \
      remaining_length = current_position - length;                            \
    else                                                                       \
      remaining_length = length - current_position;                            \
                                                                               \
    safe_sprintf( str + current_position, remaining_length, format, value->data_member[i] );\
                                                                               \
    if( i + 1 >= value->length ){                                              \
      current_position += strlen( str + current_position );                    \
      if( length < current_position )                                          \
        remaining_length = current_position - length;                          \
      else                                                                     \
        remaining_length = length - current_position;                          \
      safe_sprintf( str + current_position, remaining_length, "," );           \
    }                                                                          \
  }                                                                            \
                                                                               \
  current_position += strlen( str + current_position );                        \
  if( length < current_position )                                              \
    remaining_length = current_position - length;                              \
  else                                                                         \
    remaining_length = length - current_position;                              \
  safe_sprintf( str + current_position, remaining_length, "]" );               \
                                                                               \
  return str;                                                                  \
}

#define ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( name, data_member )                \
ValueList *                                                                    \
name##ArrayValueToValueList                                                    \
( const Value *value )                                                         \
{                                                                              \
  unsigned i;                                                                  \
  Value *value_i;                                                              \
  ValueList *list;                                                             \
                                                                               \
  if( !value )                                                                 \
    return NULL;                                                               \
                                                                               \
  list = NewValueList();                                                       \
  if( !list )                                                                  \
    return NULL;                                                               \
                                                                               \
  for( i = 0; i < value->length; i++ ){                                        \
    value_i = NewValueFor##name( value->data_member[i] );                      \
    if( !AppendToValueList( list, value_i ) )                                  \
      return NULL;                                                             \
  }                                                                            \
                                                                               \
  return list;                                                                 \
}

#define SINGULAR_VALUE_INTO_STRING_FUNCTION( name, data_member, default_format )\
char *                                                                         \
name##ValueIntoString                                                          \
( char *str, const Value *value, size_t length )                               \
{                                                                              \
  const char *format;                                                          \
                                                                               \
  if( !str || !value  )                                                        \
    return str;                                                                \
                                                                               \
  format = value->format ? value->format : default_format;                     \
                                                                               \
  if( safe_sprintf( str, length, format, value->data_member ) < 0 )            \
    return str;                                                                \
                                                                               \
  return str;                                                                  \
}
// todo throw string printing exception at above if check

#define VALUE_TO_STRING_FUNCTION( name, data_member, default_format )          \
char *                                                                         \
name##ValueToString                                                            \
( const Value *value )                                                         \
{                                                                              \
  char *buffer, *str;                                                          \
  const char *format;                                                          \
  Configuration *configuration;                                                \
  int result;                                                                  \
  size_t buffer_size, required_length;                                         \
                                                                               \
  if( !value )                                                                 \
    return NULL;                                                               \
                                                                               \
  format = value->format ? value->format : default_format;                     \
                                                                               \
  configuration = GetConfiguration();                                          \
  if( !configuration )                                                         \
    return NULL;                                                               \
                                                                               \
  buffer_size = configuration->string->buffer_size;                            \
  buffer = malloc( sizeof( char ) * buffer_size );                             \
  if( !buffer )                                                                \
    return NULL;                                                               \
                                                                               \
  buffer[0] = '\0';                                                            \
  result = safe_sprintf( buffer, buffer_size, format, value->data_member );    \
  if( result < 0 )                                                             \
    return NULL;                                                               \
  buffer[buffer_size-1] = '\0';                                                \
                                                                               \
  required_length = strlen( buffer ) + 1;                                      \
  free( buffer );                                                              \
                                                                               \
  str = malloc( sizeof( char ) * ( required_length ) );                        \
  if( !str )                                                                   \
    return NULL;                                                               \
                                                                               \
  str[0] = '\0';                                                               \
  result = safe_sprintf( str, required_length, format, value->data_member );   \
  if( result < 0 )                                                             \
    return NULL;                                                               \
  str[required_length-1] = '\0';                                               \
                                                                               \
  return str;                                                                  \
}

char *
BooleanArrayValueIntoString
( char *str, const Value *value, size_t length )
{
  return str;
}

ValueList *
BooleanArrayValueToValueList
( const Value *value )
{
  const Boolean **boolean_list;
  unsigned i;
  Value *boolean_value;
  ValueList *list;

  if( !value || !value->v_p )
    return NULL;

  list = NewValueList();
  if( !list )
    return NULL;

  boolean_list = ( const Boolean ** ) value->v_p;

  for( i = 0; i < value->length; i++ ){
    boolean_value = NewValueForBoolean( boolean_list[i] );
    if( !AppendToValueList( list, boolean_value ) )
      return NULL;
  }

  return list;
}

char *
BooleanValueIntoString
( char *str, const Value *value, size_t length )
{
  // todo need to implement
  return str;
}

char *
BooleanValueToString
( const Value *value )
{
  Boolean *boolean;
  char *str;
  const char *description;
  size_t str_length;

  if( !value || !value->v_p )
    return NULL;

  boolean = ( Boolean * ) value->v_p;

  if( boolean->value )
    description = boolean->format->true_description;
  else
    description = boolean->format->false_description;

  str_length = strlen( description );

  str = malloc( sizeof( char ) * ( str_length + 1 ) );
  if( !str )
    return NULL;

  str[0] = '\0';
#ifdef __STUMPLESS_HAVE_CRT_SECURE_FUNCTIONS
  strncpy_s( str, str_length, description, str_length );
#else
  strncpy( str, description, str_length );
#endif
  str[str_length] = '\0';

  return str;
}

ARRAY_VALUE_INTO_STRING_FUNCTION( Char, c_p, "%c" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Char, c_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( Char, c, "%c" )

VALUE_TO_STRING_FUNCTION( Char, c, "%c" )

Value *
CopyValue
( const Value *value )
{
  Value *copy;

  if( !value )
    return NULL;

  copy = malloc( sizeof( Value ) );
  if( !copy )
    return NULL;

  memcpy( copy, value, sizeof( Value ) );

  return copy;
}

void
DestroyValue
( Value *value )
{
  if( !value )
    return;

  free( value );

  return;
}

ARRAY_VALUE_INTO_STRING_FUNCTION( Double, d_p, "%g" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Double, d_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( Double, d, "%g" )

VALUE_TO_STRING_FUNCTION( Double, d, "%g" )

ARRAY_VALUE_INTO_STRING_FUNCTION( Float, f_p, "%g" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Float, f_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( Float, f, "%g" )

VALUE_TO_STRING_FUNCTION( Float, f, "%g" )

ARRAY_VALUE_INTO_STRING_FUNCTION( Int, i_p, "%i" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Int, i_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( Int, i, "%i" )

VALUE_TO_STRING_FUNCTION( Int, i, "%i" )

ARRAY_VALUE_INTO_STRING_FUNCTION( Long, l_p, "%li" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Long, l_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( Long, l, "%li" )

VALUE_TO_STRING_FUNCTION( Long, l, "%li" )

ARRAY_VALUE_INTO_STRING_FUNCTION( LongDouble, l_d_p, "%Lg" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( LongDouble, l_d_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( LongDouble, l_d, "%Lg" )

VALUE_TO_STRING_FUNCTION( LongDouble, l_d, "%Lg" )

ARRAY_VALUE_INTO_STRING_FUNCTION( LongLong, l_l_p, "%lli" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( LongLong, l_l_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( LongLong, l_l, "%lli" )

VALUE_TO_STRING_FUNCTION( LongLong, l_l, "%lli" )

ARRAY_VALUE_INTO_STRING_FUNCTION( Short, s_p, "%hi" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Short, s_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( Short, s, "%hi" )

VALUE_TO_STRING_FUNCTION( Short, s, "%hi" )

ARRAY_VALUE_INTO_STRING_FUNCTION( SignedChar, s_c_p, "%c" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( SignedChar, s_c_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( SignedChar, s_c, "%c" )

VALUE_TO_STRING_FUNCTION( SignedChar, s_c, "%c" )

char *
StringArrayValueIntoString
( char *str, const Value *value, size_t length )
{
  return str;
}

ValueList *
StringArrayValueToValueList
( const Value *value )
{
  const char **string_list;
  Value *string_value;
  ValueList *list;
  unsigned i;

  if( !value || !value->v_p )
    return NULL;

  list = NewValueList();
  if( !list )
    return NULL;

  string_list = ( const char ** ) value->v_p;

  for( i = 0; i < value->length; i++ ){
    string_value = NewValueForString( string_list[i] );
    if( !AppendToValueList( list, string_value ) )
      return NULL;
  }

  return list;
}

char *
StringValueIntoString
( char *str, const Value *value, size_t length )
{
  safe_strncpy( str, value->c_p, length );
  return str;
}

char *
StringValueToString
( const Value *value )
{
  char *str;
  size_t buffer_size;

  if( !value || !value->c_p )
    return NULL;

  buffer_size = strlen( value->c_p ) + 1;

  str = malloc( sizeof( char ) * buffer_size );
  if( !str )
    return NULL;

  safe_strncpy( str, value->c_p, buffer_size );

  return str;
}

ARRAY_VALUE_INTO_STRING_FUNCTION( UnsignedChar, u_c_p, "%c" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( UnsignedChar, u_c_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( UnsignedChar, u_c, "%c" )

VALUE_TO_STRING_FUNCTION( UnsignedChar, u_c, "%c" )

ARRAY_VALUE_INTO_STRING_FUNCTION( UnsignedInt, u_i_p, "%u" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( UnsignedInt, u_i_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( UnsignedInt, u_i, "%u" )

VALUE_TO_STRING_FUNCTION( UnsignedInt, u_i, "%u" )

ARRAY_VALUE_INTO_STRING_FUNCTION( UnsignedLong, u_l_p, "%lu" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( UnsignedLong, u_l_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( UnsignedLong, u_l, "%lu" )

VALUE_TO_STRING_FUNCTION( UnsignedLong, u_l, "%lu" )

ARRAY_VALUE_INTO_STRING_FUNCTION( UnsignedLongLong, u_l_l_p, "%llu" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( UnsignedLongLong, u_l_l_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( UnsignedLongLong, u_l_l, "%llu" )

VALUE_TO_STRING_FUNCTION( UnsignedLongLong, u_l_l, "%llu" )

ARRAY_VALUE_INTO_STRING_FUNCTION( UnsignedShort, u_s_p, "%hu" )

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( UnsignedShort, u_s_p )

SINGULAR_VALUE_INTO_STRING_FUNCTION( UnsignedShort, u_s, "%hu" )

VALUE_TO_STRING_FUNCTION( UnsignedShort, u_s, "%hu" )

char *
ValueIntoString
( char *str, const Value *value, size_t length )
{
  if( !value )
    return str;

  // todo throw malformed structure exception
  if( !value->profile || !value->profile->into_string )
    return str;

  return value->profile->into_string( str, value, length );
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
  ValueList *list;

  if( !value )
    return NULL;

  list = NewValueList();
  if( !list )
    return NULL;

  if( !AppendToValueList( list, CopyValue( value ) ) )
    return NULL;

  return list;
}

char *
VoidArrayValueIntoString
( char *str, const Value *value, size_t length )
{
  return str;
}

ValueList *
VoidArrayValueToValueList
( const Value *value )
{
  return NULL;
}

char *
VoidValueIntoString
( char *str, const Value *value, size_t length )
{
  return str;
}

char *
VoidValueToString
( const Value *value )
{
  return NULL;
}
