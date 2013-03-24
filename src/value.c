#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <boolean.h>
#include <configuration.h>
#include <types.h>
#include <value.h>

#define SINGLE_VALUE_INTO_STREAM( single_value, default_format )               \
if( format == NULL )                                                           \
  result = fprintf( stream, default_format, single_value );                    \
else                                                                           \
  result = fprintf( stream, format, single_value );

#define ARRAY_INTO_STREAM( array, default_format )                             \
for( i = 0; i < length; i++ ){                                                 \
  if( format == NULL )                                                         \
    result = fprintf( stream, default_format, array[i] );                      \
  else                                                                         \
    result = fprintf( stream, format, array[i] );                              \
                                                                               \
  if( result < 0)                                                              \
    break;                                                                     \
}

#define SINGLE_VALUE_INTO_STRING( single_value, default_format )               \
if( format == NULL )                                                           \
  result = sprintf( str, default_format, single_value );                       \
else                                                                           \
  result = sprintf( str, format, single_value );

#define ARRAY_INTO_STRING( array, default_format )                             \
str[0] = '\0';                                                                 \
for( i = 0; i < length; i++ ){                                                 \
  if( format == NULL )                                                         \
    result = sprintf( buffer, default_format, array[i] );                      \
  else                                                                         \
    result = sprintf( buffer, format, array[i] );                              \
                                                                               \
  if( result < 0)                                                              \
    break;                                                                     \
                                                                               \
  buffer[buffer_size - 1] = '\0';                                              \
  strncat( str, buffer, buffer_size - 1 );                                     \
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

StumplessValue *
StumplessValueFromString( const char * str )
{
  if( str == NULL )
    return NULL;
  
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
 
  value->format = "%s"; 
  value->type = STUMPLESS_STRING;
  value->data->c_p = str;
  
  return value;
}

StumplessValue *
StumplessValueFromUnsignedInt( unsigned num )
{
  StumplessValue * value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  value->format = "%d";
  value->type = STUMPLESS_UNSIGNED_INT;
  value->data->u_i = num;
  
  return value;
}

StumplessStatusCode
StumplessValueIntoString( char * str, StumplessValue * value )
{ 
  if( str == NULL || value == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
 
  StumplessStatusCode status;
  
  if( stumpless_configuration == NULL ){
    status = StumplessInitializeConfiguration(); 
    if( status != STUMPLESS_SUCCESS )
      return status;
  }
   
  StumplessValueData * data = value->data;
  char * temp_str;
  size_t buffer_size = stumpless_configuration->string->buffer_size;
  char * buffer = malloc( buffer_size );
  if( buffer == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  
  const char * format = value->format;
  unsigned length = value->length;
  unsigned i;
  int result;
  
  switch( value->type ){
    case STUMPLESS_UNSIGNED_SHORT:
      SINGLE_VALUE_INTO_STRING( data->u_s, "%i" )
      break;
    case STUMPLESS_SHORT:
      SINGLE_VALUE_INTO_STRING( data->s, "%i" )
      break;
    case STUMPLESS_UNSIGNED_INT:
      SINGLE_VALUE_INTO_STRING( data->u_i, "%i" )
      break;
    case STUMPLESS_INT:
      SINGLE_VALUE_INTO_STRING( data->i, "%i" )
      break;
    case STUMPLESS_UNSIGNED_LONG:
      SINGLE_VALUE_INTO_STRING( data->u_l, "%li" )
      break;
    case STUMPLESS_LONG:
      SINGLE_VALUE_INTO_STRING( data->l, "%li" )
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG:
      SINGLE_VALUE_INTO_STRING( data->u_l_l, "%lli" )
      break;
    case STUMPLESS_LONG_LONG:
      SINGLE_VALUE_INTO_STRING( data->l_l, "%lli" )
      break;
    case STUMPLESS_UNSIGNED_CHAR:
      SINGLE_VALUE_INTO_STRING( data->u_c, "%c" )
      break;
    case STUMPLESS_CHAR:
      SINGLE_VALUE_INTO_STRING( data->c, "%c" )
      break;
    case STUMPLESS_FLOAT:
      SINGLE_VALUE_INTO_STRING( data->f, "%g" )
      break;
    case STUMPLESS_DOUBLE:
      SINGLE_VALUE_INTO_STRING( data->d, "%g" )
      break;
    case STUMPLESS_LONG_DOUBLE:
      SINGLE_VALUE_INTO_STRING( data->l_d, "%Lg" )
      break;
    case STUMPLESS_UNSIGNED_SHORT_POINTER:
      ARRAY_INTO_STRING( data->u_s_p, "%i" )
      break;
    case STUMPLESS_SHORT_POINTER:
      ARRAY_INTO_STRING( data->s_p, "%i" )
      break;
    case STUMPLESS_UNSIGNED_INT_POINTER:
      ARRAY_INTO_STRING( data->u_i_p, "%i" )
      break;
    case STUMPLESS_INT_POINTER:
      ARRAY_INTO_STRING( data->i_p, "%i" )
      break;
    case STUMPLESS_UNSIGNED_LONG_POINTER:
      ARRAY_INTO_STRING( data->u_l_p, "%li" )
      break;
    case STUMPLESS_LONG_POINTER:
      ARRAY_INTO_STRING( data->l_p, "%li" )
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG_POINTER:
      ARRAY_INTO_STRING( data->u_l_l_p, "%lli" )
      break;
    case STUMPLESS_LONG_LONG_POINTER:
      ARRAY_INTO_STRING( data->l_l_p, "%lli" )
      break;
    case STUMPLESS_UNSIGNED_CHAR_POINTER:
      ARRAY_INTO_STRING( data->u_c_p, "%c" )
      break;
    case STUMPLESS_CHAR_POINTER:
      ARRAY_INTO_STRING( data->c_p, "%c" )
      break;
    case STUMPLESS_FLOAT_POINTER:
      ARRAY_INTO_STRING( data->f_p, "%g" )
      break;
    case STUMPLESS_DOUBLE_POINTER:
      ARRAY_INTO_STRING( data->d_p, "%g" )
      break;
    case STUMPLESS_LONG_DOUBLE_POINTER:
      ARRAY_INTO_STRING( data->l_d_p, "%Lg" )
      break;
    case STUMPLESS_BOOLEAN:
      temp_str = StumplessBooleanToString( data->boolean );
      if( temp_str != NULL )
        strcpy( str, temp_str );
      return STUMPLESS_SUCCESS;
      break;
    case STUMPLESS_STRING:
      SINGLE_VALUE_INTO_STRING( data->c_p, "%s" )
      break;
    case STUMPLESS_VOID_POINTER:
      temp_str = ( char * )data->v_p;
      ARRAY_INTO_STRING( temp_str, "%c" )
      break;
    default:
      return STUMPLESS_FAILURE;
  }
  
  if( result < 0 )
    return STUMPLESS_STRING_WRITE_FAILURE;
  else
    return STUMPLESS_SUCCESS;
}

char *
StumplessValueToString( StumplessValue * value )
{
  if( value == NULL )
    return NULL;
  
  StumplessStatusCode status;
  
  if( stumpless_configuration == NULL ){
    status = StumplessInitializeConfiguration();
    if( status != STUMPLESS_SUCCESS )
      return NULL;
  }
  
  size_t buffer_size = stumpless_configuration->string->buffer_size;
  char * str = malloc( sizeof( char ) * buffer_size );
  if( str == NULL )
    return NULL;
  
  status = StumplessValueIntoString( str, value );
  if( status != STUMPLESS_SUCCESS )
    return NULL;
  else
    return str;
}

StumplessStatusCode
StumplessWriteValueToStream( FILE * stream, StumplessValue * value )
{
  if( stream == NULL || value == NULL || value->data == NULL )
    return STUMPLESS_EMPTY_ARGUMENT;
  
  StumplessValueData * data = value->data;
  char * temp_str;
  const char * format = value->format;
  unsigned length = value->length;
  unsigned i;
  int result;
  
  switch( value->type ){
    case STUMPLESS_UNSIGNED_SHORT:
      SINGLE_VALUE_INTO_STREAM( data->u_s, "%i" )
      break;
    case STUMPLESS_SHORT:
      SINGLE_VALUE_INTO_STREAM( data->s, "%i" )
      break;
    case STUMPLESS_UNSIGNED_INT:
      SINGLE_VALUE_INTO_STREAM( data->u_i, "%i" )
      break;
    case STUMPLESS_INT:
      SINGLE_VALUE_INTO_STREAM( data->i, "%i" )
      break;
    case STUMPLESS_UNSIGNED_LONG:
      SINGLE_VALUE_INTO_STREAM( data->u_l, "%li" )
      break;
    case STUMPLESS_LONG:
      SINGLE_VALUE_INTO_STREAM( data->l, "%li" )
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG:
      SINGLE_VALUE_INTO_STREAM( data->u_l_l, "%lli" )
      break;
    case STUMPLESS_LONG_LONG:
      SINGLE_VALUE_INTO_STREAM( data->l_l, "%lli" )
      break;
    case STUMPLESS_UNSIGNED_CHAR:
      SINGLE_VALUE_INTO_STREAM( data->u_c, "%c" )
      break;
    case STUMPLESS_CHAR:
      SINGLE_VALUE_INTO_STREAM( data->c, "%c" )
      break;
    case STUMPLESS_FLOAT:
      SINGLE_VALUE_INTO_STREAM( data->f, "%g" )
      break;
    case STUMPLESS_DOUBLE:
      SINGLE_VALUE_INTO_STREAM( data->d, "%g" )
      break;
    case STUMPLESS_LONG_DOUBLE:
      SINGLE_VALUE_INTO_STREAM( data->l_d, "%Lg" )
      break;
    case STUMPLESS_UNSIGNED_SHORT_POINTER:
      ARRAY_INTO_STREAM( data->u_s_p, "%i" )
      break;
    case STUMPLESS_SHORT_POINTER:
      ARRAY_INTO_STREAM( data->s_p, "%i" )
      break;
    case STUMPLESS_UNSIGNED_INT_POINTER:
      ARRAY_INTO_STREAM( data->u_i_p, "%i" )
      break;
    case STUMPLESS_INT_POINTER:
      ARRAY_INTO_STREAM( data->i_p, "%i" )
      break;
    case STUMPLESS_UNSIGNED_LONG_POINTER:
      ARRAY_INTO_STREAM( data->u_l_p, "%li" )
      break;
    case STUMPLESS_LONG_POINTER:
      ARRAY_INTO_STREAM( data->l_p, "%li" )
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG_POINTER:
      ARRAY_INTO_STREAM( data->u_l_l_p, "%lli" )
      break;
    case STUMPLESS_LONG_LONG_POINTER:
      ARRAY_INTO_STREAM( data->l_l_p, "%lli" )
      break;
    case STUMPLESS_UNSIGNED_CHAR_POINTER:
      ARRAY_INTO_STREAM( data->u_c_p, "%c" )
      break;
    case STUMPLESS_CHAR_POINTER:
      ARRAY_INTO_STREAM( data->c_p, "%c" )
      break;
    case STUMPLESS_FLOAT_POINTER:
      ARRAY_INTO_STREAM( data->f_p, "%g" )
      break;
    case STUMPLESS_DOUBLE_POINTER:
      ARRAY_INTO_STREAM( data->d_p, "%g" )
      break;
    case STUMPLESS_LONG_DOUBLE_POINTER:
      ARRAY_INTO_STREAM( data->l_d_p, "%Lg" )
      break;
    case STUMPLESS_BOOLEAN:
      temp_str = StumplessBooleanToString( data->boolean );
      result = fprintf( stream, "%s", temp_str );
      break;
    case STUMPLESS_STRING:
      SINGLE_VALUE_INTO_STREAM( data->c_p, "%s" )
      break;
    case STUMPLESS_VOID_POINTER:
      result = fwrite( value->data->v_p, value->length, 1, stream );
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
