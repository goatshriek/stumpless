#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private/boolean.h"
#include "private/configuration.h"
#include "private/status.h"
#include "private/status_checker.h"
#include "private/type.h"
#include "private/value.h"
#include "private/value_constructor.h"
#include "private/value_list.h"

#define ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( name, data_member )                \
ValueList *                                                                    \
name##ArrayValueToValueList( Value * value )                                   \
{                                                                              \
  if( value == NULL || value->data == NULL                                     \
   || value->data->data_member == NULL )                                       \
    return NULL;                                                               \
                                                                               \
  ValueList * list = NewValueList();                                           \
  if( list == NULL )                                                           \
    return NULL;                                                               \
                                                                               \
  Type * data = value->data;                                                   \
  Value * value_i;                                                             \
  unsigned i;                                                                  \
                                                                               \
  for( i = 0; i < value->length; i++ ){                                        \
    value_i = ValueFrom##name( data->data_member[i] );                         \
    NULL_ON_FAILURE( AppendValueToValueList( list, value_i ) )                 \
  }                                                                            \
                                                                               \
  return list;                                                                 \
}

#define VALUE_INTO_STRING_FUNCTION( name, data_member, default_format )        \
Status *                                                                       \
name##ValueIntoString( char * str, Value * value )                             \
{                                                                              \
  if( str == NULL || value == NULL || value->data == NULL )                    \
    return RaiseAbnormalStatus( "empty argument" );                            \
                                                                               \
  const char * format = value->format == NULL ? default_format : value->format;\
                                                                               \
  str[0] = '\0';                                                               \
  int result = sprintf( str, format, value->data->data_member );               \
  if( result < 0 )                                                             \
    return RaiseAbnormalStatus( "string write failure" );                      \
                                                                               \
  return NULL;                                                                 \
}

// todo this function can be adapted to no longer rely on the buffer, if
// snprintf is available. Create configuration check to handle this case
#define VALUE_TO_STRING_FUNCTION( name, data_member, default_format )          \
char *                                                                         \
name##ValueToString( Value * value )                                           \
{                                                                              \
  if( value == NULL || value->data == NULL )                                   \
    return NULL;                                                               \
                                                                               \
  const char * format = value->format == NULL ? default_format : value->format;\
                                                                               \
  Configuration * configuration = GetConfiguration();                          \
  if( configuration == NULL )                                                  \
    return NULL;                                                               \
                                                                               \
  size_t buffer_size = configuration->string->buffer_size;                     \
  size_t buffer_length = buffer_size - 1;                                      \
  char * buffer = malloc( sizeof( char ) * buffer_size );                      \
  if( buffer == NULL )                                                         \
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
  if( str == NULL )                                                            \
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
( Value * value )
{
  if( value == NULL || value->data == NULL || value->data->v_p == NULL )
    return NULL;
  
  ValueList * list = NewValueList();
  if( list == NULL )
    return NULL;
  
  const Boolean ** boolean_list;
  boolean_list = (const Boolean **) value->data->v_p;
  Value * boolean_value;
  
  unsigned i; 
  
  for( i = 0; i < value->length; i++ ){
    boolean_value = ValueFromBoolean( boolean_list[i] );
    NULL_ON_FAILURE( AppendValueToValueList( list, boolean_value ) )
  }
  
  return list;
}

Status *
BooleanValueIntoString
( char * str, Value * value )
{
  // todo need to implement
  return NULL;
}

char *
BooleanValueToString
( Value * value )
{
  if( value == NULL || value->data == NULL || value->data->v_p == NULL )
    return NULL;
  
  Boolean * boolean = (Boolean * ) value->data->v_p;
  
  const char * description;
  if( boolean->value )
    description = boolean->format->true_description;
  else
    description = boolean->format->false_description;
  
  size_t str_length = strlen( description );
  
  char * str = malloc( sizeof( char ) * ( str_length + 1 ) );
  if( str == NULL )
    return NULL;
  
  str[0] = '\0';
  strncpy( str, description, str_length );
  str[str_length] = '\0';
  
  return str;
}

ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( Char, c_p )

VALUE_INTO_STRING_FUNCTION( Char, c, "%c" )

VALUE_TO_STRING_FUNCTION( Char, c, "%c" )

void
DestroyValue
( Value * value )
{
  if( value == NULL )
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
( Value * value )
{
  if( value == NULL || value->data == NULL || value->data->v_p == NULL )
    return NULL;
  
  ValueList * list = NewValueList();
  if( list == NULL )
    return NULL;
  
  const char ** string_list = (const char **) value->data->v_p;
  Value * string_value;
  
  unsigned i; 
  
  for( i = 0; i < value->length; i++ ){
    string_value = ValueFromString( string_list[i] );
    NULL_ON_FAILURE( AppendValueToValueList( list, string_value ) )
  }
  
  return list;
}

Status *
StringValueIntoString
( char * str, Value * value )
{
  // todo need to implement
  return NULL;
}

char *
StringValueToString
( Value * value )
{
  if( value == NULL || value->data == NULL || value->data->c_p == NULL )
    return NULL;
  
  size_t str_length = strlen( value->data->c_p );
  
  char * str = malloc( sizeof( char ) * ( str_length + 1 ) );
  if( str == NULL )
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
( char * str, Value * value )
{
  if( value == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( value->profile == NULL || value->profile->into_string == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  return value->profile->into_string( str, value );
}

char *
ValueToString
( Value * value )
{
  if( value == NULL || value->profile == NULL
   || value->profile->to_string == NULL )
    return NULL;
  
  return value->profile->to_string( value );
}

ValueList *
ValueToValueList
( Value * value )
{
  if( value == NULL )
    return NULL;
  
  ValueList * list = NewValueList();
  if( list == NULL )
    return NULL;
  
  NULL_ON_FAILURE( AppendValueToValueList( list, value ) )
  
  return list;
}
