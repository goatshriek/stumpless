#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <boolean.h>
#include <configuration.h>
#include <status_checker.h>
#include <type.h>
#include <value.h>
#include <value_constructor.h>
#include <value_list.h>

#define SINGLE_VALUE_INTO_STREAM( member )                                     \
result = fprintf( stream, format, data->member );

#define ARRAY_INTO_STREAM( array )                                             \
for( i = 0; i < length; i++ ){                                                 \
  result = fprintf( stream, format, data->array[i] );                          \
                                                                               \
  if( result < 0)                                                              \
    break;                                                                     \
}

#define SINGLE_VALUE_INTO_STRING( member )                                     \
result = sprintf( str, format, data->member );

#define ARRAY_INTO_STRING( array )                                             \
str[0] = '\0';                                                                 \
for( i = 0; i < length; i++ ){                                                 \
  result = sprintf( buffer, format, data->array[i] );                          \
                                                                               \
  if( result < 0)                                                              \
    break;                                                                     \
                                                                               \
  buffer[buffer_size - 1] = '\0';                                              \
  strncat( str, buffer, buffer_size - 1 );                                     \
}

StumplessValueList *
StumplessArrayValueToValueList( StumplessValue * value )
{
  if( value == NULL )
    return NULL;
  
  StumplessValueList * list = StumplessNewValueList();
  if( list == NULL )
    return NULL;
  
  StumplessValueData * data = value->data;
  if( data == NULL )
    return list;
  
  StumplessValue * value_i;
  unsigned i;
  unsigned length = value->length;
  switch( value->type ){
    case STUMPLESS_UNSIGNED_SHORT_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromUnsignedShort( data->u_s_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_SHORT_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromShort( data->s_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break; 
    case STUMPLESS_UNSIGNED_INT_POINTER:
      for( i = 0; i < length; i++){
        value_i = StumplessValueFromUnsignedInt( data->u_i_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_INT_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromInt( data->i_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_UNSIGNED_LONG_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromUnsignedLong( data->u_l_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_LONG_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromLong( data->l_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromUnsignedLongLong( data->l_l_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_LONG_LONG_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromLongLong( data->l_l_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_UNSIGNED_CHAR_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromUnsignedChar( data->u_c_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_SIGNED_CHAR_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromSignedChar( data->s_c_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_CHAR_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromChar( data->c_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_FLOAT_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromFloat( data->f_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_DOUBLE_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromDouble( data->d_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    case STUMPLESS_LONG_DOUBLE_POINTER:
      for( i = 0; i < length; i++ ){
        value_i = StumplessValueFromLongDouble( data->l_d_p[i] );
        NULL_ON_FAILURE( StumplessAppendValueToValueList( list, value_i ) )
      }
      break;
    default:
      return NULL;
  }
  
  return list;
}

void
StumplessDestroyValue( StumplessValue * value )
{
  if( value == NULL )
    return;
  
  free( value->data );
  
  free( value );
  
  return;
}

StumplessStatusCode
StumplessValueIntoString( char * str, StumplessValue * value )
{ 
  if( str == NULL || value == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
 
  StumplessValueData * data = value->data;
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  char * temp_str;
  size_t buffer_size = configuration->string->buffer_size;
  char * buffer = malloc( buffer_size );
  if( buffer == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  const char * default_format = StumplessValueTypeDefaultFormat( value->type );
  const char * format = value->format == NULL ? default_format : value->format;
  unsigned length = value->length;
  unsigned i;
  int result;
  
  switch( value->type ){
    case STUMPLESS_UNSIGNED_SHORT:
      SINGLE_VALUE_INTO_STRING( u_s )
      break;
    case STUMPLESS_SHORT:
      SINGLE_VALUE_INTO_STRING( s )
      break;
    case STUMPLESS_UNSIGNED_INT:
      SINGLE_VALUE_INTO_STRING( u_i )
      break;
    case STUMPLESS_INT:
      SINGLE_VALUE_INTO_STRING( i )
      break;
    case STUMPLESS_UNSIGNED_LONG:
      SINGLE_VALUE_INTO_STRING( u_l )
      break;
    case STUMPLESS_LONG:
      SINGLE_VALUE_INTO_STRING( l )
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG:
      SINGLE_VALUE_INTO_STRING( u_l_l )
      break;
    case STUMPLESS_LONG_LONG:
      SINGLE_VALUE_INTO_STRING( l_l )
      break;
    case STUMPLESS_UNSIGNED_CHAR:
      SINGLE_VALUE_INTO_STRING( u_c )
      break;
    case STUMPLESS_CHAR:
      SINGLE_VALUE_INTO_STRING( c )
      break;
    case STUMPLESS_FLOAT:
      SINGLE_VALUE_INTO_STRING( f )
      break;
    case STUMPLESS_DOUBLE:
      SINGLE_VALUE_INTO_STRING( d )
      break;
    case STUMPLESS_LONG_DOUBLE:
      SINGLE_VALUE_INTO_STRING( l_d )
      break;
    case STUMPLESS_UNSIGNED_SHORT_POINTER:
      ARRAY_INTO_STRING( u_s_p )
      break;
    case STUMPLESS_SHORT_POINTER:
      ARRAY_INTO_STRING( s_p )
      break;
    case STUMPLESS_UNSIGNED_INT_POINTER:
      ARRAY_INTO_STRING( u_i_p )
      break;
    case STUMPLESS_INT_POINTER:
      ARRAY_INTO_STRING( i_p )
      break;
    case STUMPLESS_UNSIGNED_LONG_POINTER:
      ARRAY_INTO_STRING( u_l_p )
      break;
    case STUMPLESS_LONG_POINTER:
      ARRAY_INTO_STRING( l_p )
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG_POINTER:
      ARRAY_INTO_STRING( u_l_l_p )
      break;
    case STUMPLESS_LONG_LONG_POINTER:
      ARRAY_INTO_STRING( l_l_p )
      break;
    case STUMPLESS_UNSIGNED_CHAR_POINTER:
      ARRAY_INTO_STRING( u_c_p )
      break;
    case STUMPLESS_CHAR_POINTER:
      ARRAY_INTO_STRING( c_p )
      break;
    case STUMPLESS_FLOAT_POINTER:
      ARRAY_INTO_STRING( f_p )
      break;
    case STUMPLESS_DOUBLE_POINTER:
      ARRAY_INTO_STRING( d_p )
      break;
    case STUMPLESS_LONG_DOUBLE_POINTER:
      ARRAY_INTO_STRING( l_d_p )
      break;
    case STUMPLESS_BOOLEAN:
      temp_str = StumplessBooleanToString( data->boolean );
      if( temp_str != NULL )
        strcpy( str, temp_str );
      return STUMPLESS_SUCCESS;
      break;
    case STUMPLESS_STRING:
      SINGLE_VALUE_INTO_STRING( c_p )
      break;
    case STUMPLESS_VOID_POINTER:
      temp_str = ( char * )data->v_p;
      for( i = 0; i < length; i++ )
        str[i] = temp_str[i];
      str[i] = '\0';
      break;
    default:
      return STUMPLESS_FAILURE;
  }
  
  if( result < 0 )
    return STUMPLESS_STRING_WRITE_FAILURE;
  else
    return STUMPLESS_SUCCESS;
}

unsigned short
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
  if( value == NULL )
    return NULL;
  
  StumplessConfiguration * configuration = StumplessGetConfiguration();
  size_t buffer_size = configuration->string->buffer_size;
  char * str = malloc( sizeof( char ) * buffer_size );
  if( str == NULL )
    return NULL;
  
  NULL_ON_FAILURE( StumplessValueIntoString( str, value ) )
  
  return str;
}

const char *
StumplessValueTypeDefaultFormat( StumplessValueType type )
{
  switch( type ){
    case STUMPLESS_UNSIGNED_SHORT:
    case STUMPLESS_UNSIGNED_SHORT_POINTER:
      return "%hu";
    case STUMPLESS_SHORT:
    case STUMPLESS_SHORT_POINTER:
      return "%hi";
    case STUMPLESS_UNSIGNED_INT:
    case STUMPLESS_UNSIGNED_INT_POINTER:
      return "%u";
    case STUMPLESS_INT:
    case STUMPLESS_INT_POINTER:
      return "%i";
    case STUMPLESS_UNSIGNED_LONG:
    case STUMPLESS_UNSIGNED_LONG_POINTER:
      return "%lu";
    case STUMPLESS_LONG:
    case STUMPLESS_LONG_POINTER:
      return "%li";
    case STUMPLESS_UNSIGNED_LONG_LONG:
    case STUMPLESS_UNSIGNED_LONG_LONG_POINTER:
      return "%llu";
    case STUMPLESS_LONG_LONG:
    case STUMPLESS_LONG_LONG_POINTER:
      return "%lli";
    case STUMPLESS_UNSIGNED_CHAR:
    case STUMPLESS_SIGNED_CHAR:
    case STUMPLESS_CHAR:
    case STUMPLESS_UNSIGNED_CHAR_POINTER:
    case STUMPLESS_SIGNED_CHAR_POINTER:
    case STUMPLESS_CHAR_POINTER:
      return "%c";
    case STUMPLESS_FLOAT:
    case STUMPLESS_DOUBLE:
    case STUMPLESS_FLOAT_POINTER:
    case STUMPLESS_DOUBLE_POINTER:
      return "%g";
    case STUMPLESS_LONG_DOUBLE:
    case STUMPLESS_LONG_DOUBLE_POINTER:
      return "%Lg";
    case STUMPLESS_BOOLEAN:
    case STUMPLESS_STRING:
      return "%s";
    default:
      return NULL;
  }
}

StumplessStatusCode
StumplessWriteValueToStream( FILE * stream, StumplessValue * value )
{
  if( stream == NULL || value == NULL || value->data == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessValueData * data = value->data;
  char * temp_str;
  const char * default_format = StumplessValueTypeDefaultFormat( value->type );
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
