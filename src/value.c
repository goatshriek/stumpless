#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <boolean.h>
#include <configuration.h>
#include <status_checker.h>
#include <string.h>
#include <type.h>
#include <value.h>
#include <value_constructor.h>
#include <value_list.h>

#define ARRAY_VALUE_TO_VALUE_LIST_FUNCTION( name, data_member )                \
StumplessValueList *                                                           \
Stumpless##name##ArrayValueToValueList( StumplessValue * value )               \
{                                                                              \
  if( value == NULL || value->data == NULL                                     \
   || value->data->data_member == NULL )                                       \
    return NULL;                                                               \
                                                                               \
  StumplessValueList * list = StumplessNewValueList();                         \
  if( list == NULL )                                                           \
    return NULL;                                                               \
                                                                               \
  StumplessValueData * data = value->data;                                     \
  StumplessValue * value_i;                                                    \
  unsigned i;                                                                  \
                                                                               \
  for( i = 0; i < value->length; i++ ){                                        \
    value_i = StumplessValueFrom##name( data->data_member[i] );                \
    NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )        \
  }                                                                            \
                                                                               \
  return list;                                                                 \
}

#define VALUE_INTO_STRING_FUNCTION( name, data_member, default_format )        \
StumplessStatusCode                                                            \
Stumpless##name##ValueIntoString( char * str, StumplessValue * value )         \
{                                                                              \
  if( str == NULL || value == NULL || value->data == NULL )                    \
    return STUMPLESS_EMPTY_ARGUMENT;                                           \
                                                                               \
  const char * format = value->format == NULL ? default_format : value->format;\
                                                                               \
  str[0] = '\0';                                                               \
  int result = sprintf( str, format, value->data->data_member );               \
  if( result < 0 )                                                             \
    return STUMPLESS_STRING_WRITE_FAILURE;                                     \
                                                                               \
  return STUMPLESS_SUCCESS;                                                    \
}

// todo this function can be adapted to no longer rely on the buffer, if
// snprintf is available. Create configuration check to handle this case
#define VALUE_TO_STRING_FUNCTION( name, data_member, default_format )          \
char *                                                                         \
Stumpless##name##ValueToString( StumplessValue * value )                       \
{                                                                              \
  if( value == NULL || value->data == NULL )                                   \
    return NULL;                                                               \
                                                                               \
  const char * format = value->format == NULL ? default_format : value->format;\
                                                                               \
  StumplessConfiguration * configuration = StumplessGetConfiguration();        \
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

#define SINGLE_VALUE_INTO_STREAM( member )                                     \
result = fprintf( stream, format, data->member );

#define ARRAY_INTO_STREAM( array )                                             \
for( i = 0; i < length; i++ ){                                                 \
  result = fprintf( stream, format, data->array[i] );                          \
                                                                               \
  if( result < 0)                                                              \
    break;                                                                     \
}

StumplessValueList *
StumplessBooleanArrayValueToValueList( StumplessValue * value )
{
  if( value == NULL || value->data == NULL || value->data->v_p == NULL )
    return NULL;
  
  StumplessValueList * list = StumplessNewValueList();
  if( list == NULL )
    return NULL;
  
  const StumplessBoolean ** boolean_list;
  boolean_list = (const StumplessBoolean **) value->data->v_p;
  StumplessValue * boolean_value;
  
  unsigned i; 
  
  for( i = 0; i < value->length; i++ ){
    boolean_value = StumplessValueFromBoolean( boolean_list[i] );
    NULL_ON_FAILURE( StumplessAppendValueToValueList( list, boolean_value ) )
  }
  
  return list;
}

StumplessStatusCode
StumplessBooleanValueIntoString( char * str, StumplessValue * value )
{
  // todo need to implement
  return STUMPLESS_FAILURE;
}

char *
StumplessBooleanValueToString( StumplessValue * value )
{
  if( value == NULL || value->data == NULL || value->data->v_p == NULL )
    return NULL;
  
  StumplessBoolean * boolean = (StumplessBoolean * ) value->data->v_p;
  
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
StumplessDestroyValue( StumplessValue * value )
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

StumplessValueList *
StumplessGenericValueToValueList( StumplessValue * value )
{
  if( value == NULL )
    return NULL;
  
  StumplessValueList * list = StumplessNewValueList();
  if( list == NULL )
    return NULL;
  
  NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value ) )
  
  return list;
}

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

StumplessValueList *
StumplessStringArrayValueToValueList( StumplessValue * value )
{
  if( value == NULL || value->data == NULL || value->data->v_p == NULL )
    return NULL;
  
  StumplessValueList * list = StumplessNewValueList();
  if( list == NULL )
    return NULL;
  
  const char ** string_list = (const char **) value->data->v_p;
  StumplessValue * string_value;
  
  unsigned i; 
  
  for( i = 0; i < value->length; i++ ){
    string_value = StumplessValueFromString( string_list[i] );
    NULL_ON_FAILURE( StumplessAppendValueToValueList( list, string_value ) )
  }
  
  return list;
}

StumplessStatusCode
StumplessStringValueIntoString( char * str, StumplessValue * value )
{
  return STUMPLESS_FAILURE;
}

char *
StumplessStringValueToString( StumplessValue * value )
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

StumplessStatusCode
StumplessValueIntoString( char * str, StumplessValue * value )
{
  if( value == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  if( value->profile == NULL || value->profile->into_string == NULL )
    return STUMPLESS_MALFORMED_STRUCTURE;
  
  return value->profile->into_string( str, value );
}

unsigned short  // todo remove this function
StumplessValueIsArray( StumplessValue * value )
{
  switch( value->type ){
    case STUMPLESS_UNSIGNED_SHORT_POINTER:
    case STUMPLESS_SHORT_POINTER:
    case STUMPLESS_UNSIGNED_INT_POINTER:
    case STUMPLESS_INT_POINTER:
    case STUMPLESS_UNSIGNED_LONG_POINTER:
    case STUMPLESS_LONG_POINTER:
    case STUMPLESS_UNSIGNED_LONG_LONG_POINTER:
    case STUMPLESS_LONG_LONG_POINTER:
    case STUMPLESS_UNSIGNED_CHAR_POINTER:
    case STUMPLESS_SIGNED_CHAR_POINTER:
    case STUMPLESS_CHAR_POINTER:
    case STUMPLESS_FLOAT_POINTER:
    case STUMPLESS_DOUBLE_POINTER:
    case STUMPLESS_LONG_DOUBLE_POINTER:
    case STUMPLESS_STRING_POINTER:
      return 1;
    default:
      return 0;
  }
}

char *
StumplessValueToString( StumplessValue * value )
{
  if( value == NULL || value->profile == NULL
   || value->profile->to_string == NULL )
    return NULL;
  
  return value->profile->to_string( value );
}

StumplessStatusCode // todo remove this function
StumplessWriteValueToStream( FILE * stream, StumplessValue * value )
{
  if( stream == NULL || value == NULL || value->data == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessValueData * data = value->data;
  char * temp_str;
  //const char * default_format = StumplessValueTypeDefaultFormat( value->type );
  const char * default_format = "%i";
  const char * format = value->format == NULL ? default_format : value->format;
  unsigned length = value->length;
  unsigned i;
  int result;
  
  switch( value->type ){
    case STUMPLESS_UNSIGNED_SHORT:
      SINGLE_VALUE_INTO_STREAM( u_s )
      break;
    case STUMPLESS_SHORT:
      SINGLE_VALUE_INTO_STREAM( s )
      break;
    case STUMPLESS_UNSIGNED_INT:
      SINGLE_VALUE_INTO_STREAM( u_i )
      break;
    case STUMPLESS_INT:
      SINGLE_VALUE_INTO_STREAM( i )
      break;
    case STUMPLESS_UNSIGNED_LONG:
      SINGLE_VALUE_INTO_STREAM( u_l )
      break;
    case STUMPLESS_LONG:
      SINGLE_VALUE_INTO_STREAM( l )
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG:
      SINGLE_VALUE_INTO_STREAM( u_l_l )
      break;
    case STUMPLESS_LONG_LONG:
      SINGLE_VALUE_INTO_STREAM( l_l )
      break;
    case STUMPLESS_UNSIGNED_CHAR:
      SINGLE_VALUE_INTO_STREAM( u_c )
      break;
    case STUMPLESS_CHAR:
      SINGLE_VALUE_INTO_STREAM( c )
      break;
    case STUMPLESS_FLOAT:
      SINGLE_VALUE_INTO_STREAM( f )
      break;
    case STUMPLESS_DOUBLE:
      SINGLE_VALUE_INTO_STREAM( d )
      break;
    case STUMPLESS_LONG_DOUBLE:
      SINGLE_VALUE_INTO_STREAM( l_d )
      break;
    case STUMPLESS_UNSIGNED_SHORT_POINTER:
      ARRAY_INTO_STREAM( u_s_p )
      break;
    case STUMPLESS_SHORT_POINTER:
      ARRAY_INTO_STREAM( s_p )
      break;
    case STUMPLESS_UNSIGNED_INT_POINTER:
      ARRAY_INTO_STREAM( u_i_p )
      break;
    case STUMPLESS_INT_POINTER:
      ARRAY_INTO_STREAM( i_p )
      break;
    case STUMPLESS_UNSIGNED_LONG_POINTER:
      ARRAY_INTO_STREAM( u_l_p )
      break;
    case STUMPLESS_LONG_POINTER:
      ARRAY_INTO_STREAM( l_p )
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG_POINTER:
      ARRAY_INTO_STREAM( u_l_l_p )
      break;
    case STUMPLESS_LONG_LONG_POINTER:
      ARRAY_INTO_STREAM( l_l_p )
      break;
    case STUMPLESS_UNSIGNED_CHAR_POINTER:
      ARRAY_INTO_STREAM( u_c_p )
      break;
    case STUMPLESS_CHAR_POINTER:
      ARRAY_INTO_STREAM( c_p )
      break;
    case STUMPLESS_FLOAT_POINTER:
      ARRAY_INTO_STREAM( f_p )
      break;
    case STUMPLESS_DOUBLE_POINTER:
      ARRAY_INTO_STREAM( d_p )
      break;
    case STUMPLESS_LONG_DOUBLE_POINTER:
      ARRAY_INTO_STREAM( l_d_p )
      break;
    case STUMPLESS_BOOLEAN:
      temp_str = StumplessBooleanToString( data->boolean );
      result = fprintf( stream, "%s", temp_str );
      break;
    case STUMPLESS_STRING:
      SINGLE_VALUE_INTO_STREAM( c_p )
      break;
    case STUMPLESS_VOID_POINTER:
      result = fwrite( data->v_p, value->length, 1, stream );
      if( result < 1 )
        return STUMPLESS_FILE_WRITE_FAILURE;
      else
        return STUMPLESS_SUCCESS;
      break;
    default:
      return STUMPLESS_FAILURE;
  }
  
  if( result < 0 )
    return STUMPLESS_FILE_WRITE_FAILURE;
  else
    return STUMPLESS_SUCCESS;
}
