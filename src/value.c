#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <configuration.h>
#include <types.h>
#include <value.h>

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
StumplessValueFromString( char * str )
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
  char * cast_data;
  size_t buffer_size = stumpless_configuration->string->buffer_size;
  char * buffer = malloc( buffer_size );
  if( buffer == NULL )
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
  size_t remaining_buffer = buffer_size - 1;
  size_t buffer_str_length;
  
  const char * format = value->format;
  unsigned length = value->length;
  unsigned i;
  int result;
  
  switch( value->type ){
    case STUMPLESS_UNSIGNED_SHORT:
      if( format == NULL )
        result = sprintf( str, "%i", data->u_s );
      else
        result = sprintf( str, format, data->u_s );
      break;
    case STUMPLESS_SHORT:
      if( format == NULL )
        result = sprintf( str, "%i", data->s );
      else
        result = sprintf( str, format, data->s );
      break;
    case STUMPLESS_UNSIGNED_INT:
      if( format == NULL )
        result = sprintf( str, "%i", data->u_i );
      else
        result = sprintf( str, format, data->u_i );
      break;
    case STUMPLESS_INT:
      if( format == NULL )
        result = sprintf( str, "%i", data->i );
      else
        result = sprintf( str, format, data->i );
      break;
    case STUMPLESS_UNSIGNED_LONG:
      if( format == NULL )
        result = sprintf( str, "%li", data->u_l );
      else
        result = sprintf( str, format, data->u_l );
      break;
    case STUMPLESS_LONG:
      if( format == NULL )
        result = sprintf( str, "%li", data->l );
      else
        result = sprintf( str, format, data->l );
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG:
      if( format == NULL )
        result = sprintf( str, "%lli", data->u_l_l );
      else
        result = sprintf( str, format, data->u_l_l );
      break;
    case STUMPLESS_LONG_LONG:
      if( format == NULL )
        result = sprintf( str, "%lli", data->l_l );
      else
        result = sprintf( str, format, data->l_l );
      break;
    case STUMPLESS_UNSIGNED_CHAR:
      if( format == NULL )
        result = sprintf( str, "%c", data->u_c );
      else
        result = sprintf( str, format, data->u_c );
      break;
    case STUMPLESS_CHAR:
      if( format == NULL )
        result = sprintf( str, "%c", data->c );
      else
        result = sprintf( str, format, data->c );
      break;
    case STUMPLESS_FLOAT:
      if( format == NULL )
        result = sprintf( str, "%g", data->f );
      else
        result = sprintf( str, format, data->f );
      break;
    case STUMPLESS_DOUBLE:
      if( format == NULL )
        result = sprintf( str, "%g", data->d );
      else
        result = sprintf( str, format, data->d );
      break;
    case STUMPLESS_LONG_DOUBLE:
      if( format == NULL )
        result = sprintf( str, "%Lg", data->l_d );
      else
        result = sprintf( str, format, data->l_d );
      break;
    case STUMPLESS_UNSIGNED_SHORT_POINTER:
      break;
    case STUMPLESS_SHORT_POINTER:
      break;
    case STUMPLESS_UNSIGNED_INT_POINTER:
      break;
    case STUMPLESS_INT_POINTER:
      str[0] = '\0';
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = sprintf( buffer, "%i", data->i_p[i] );
        else
          result = sprintf( buffer, format, data->i_p[i] );
        
        if( result < 0)
          break;
        
        buffer[buffer_size - 1] = '\0';
        buffer_str_length = strlen( buffer );
        if( buffer_str_length > remaining_buffer )
          return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
        
        strncat( str, buffer, remaining_buffer );
        remaining_buffer -= buffer_str_length;
      }
      break;
    case STUMPLESS_UNSIGNED_LONG_POINTER:
      break;
    case STUMPLESS_LONG_POINTER:
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG_POINTER:
      break;
    case STUMPLESS_LONG_LONG_POINTER:
      break;
    case STUMPLESS_UNSIGNED_CHAR_POINTER:
      break;
    case STUMPLESS_CHAR_POINTER:
      break;
    case STUMPLESS_FLOAT_POINTER:
      break;
    case STUMPLESS_DOUBLE_POINTER:
      break;
    case STUMPLESS_LONG_DOUBLE_POINTER:
      break;
    case STUMPLESS_STRING:
      if( format == NULL )
        result = sprintf( str, "%s", data->c_p );
      else
        result = sprintf( str, format, data->c_p );
      break;
    case STUMPLESS_VOID_POINTER:
      cast_data = ( char * )data->v_p;
      str[0] = '\0';
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = sprintf( buffer, "%c", cast_data[i] );
        else
          result = sprintf( buffer, format, cast_data[i] );
        
        if( result < 0)
          break;
        
        buffer[buffer_size - 1] = '\0';
        buffer_str_length = strlen( buffer );
        if( buffer_str_length > remaining_buffer )
          return STUMPLESS_MEMORY_ALLOCATION_FAILURE;
        
        strncat( str, buffer, remaining_buffer );
        remaining_buffer -= buffer_str_length;
      }
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
  const char * format = value->format;
  unsigned length = value->length;
  unsigned i;
  int result;
  
  switch( value->type ){
    case STUMPLESS_UNSIGNED_SHORT:
      if( format == NULL )
        result = fprintf( stream, "%i", data->u_s );
      else
        result = fprintf( stream, format, data->u_s );
      break;
    case STUMPLESS_SHORT:
      if( format == NULL )
        result = fprintf( stream, "%i", data->s );
      else
        result = fprintf( stream, format, data->s );
      break;
    case STUMPLESS_UNSIGNED_INT:
      if( format == NULL )
        result = fprintf( stream, "%i", data->u_i );
      else
        result = fprintf( stream, format, data->u_i );
      break;
    case STUMPLESS_INT:
      if( format == NULL )
        result = fprintf( stream, "%i", data->i );
      else
        result = fprintf( stream, format, data->i );
      break;
    case STUMPLESS_UNSIGNED_LONG:
      if( format == NULL )
        result = fprintf( stream, "%li", data->u_l );
      else
        result = fprintf( stream, format, data->u_l );
      break;
    case STUMPLESS_LONG:
      if( format == NULL )
        result = fprintf( stream, "%li", data->l );
      else
        result = fprintf( stream, format, data->l );
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG:
      if( format == NULL )
        result = fprintf( stream, "%lli", data->u_l_l );
      else
        result = fprintf( stream, format, data->u_l_l );
      break;
    case STUMPLESS_LONG_LONG:
      if( format == NULL )
        result = fprintf( stream, "%lli", data->l_l );
      else
        result = fprintf( stream, format, data->l_l );
      break;
    case STUMPLESS_UNSIGNED_CHAR:
      if( format == NULL )
        result = fprintf( stream, "%c", data->u_c );
      else
        result = fprintf( stream, format, data->u_c );
      break;
    case STUMPLESS_CHAR:
      if( format == NULL )
        result = fprintf( stream, "%c", data->c );
      else
        result = fprintf( stream, format, data->c );
      break;
    case STUMPLESS_FLOAT:
      if( format == NULL )
        result = fprintf( stream, "%g", data->f );
      else
        result = fprintf( stream, format, data->f );
      break;
    case STUMPLESS_DOUBLE:
      if( format == NULL )
        result = fprintf( stream, "%g", data->d );
      else
        result = fprintf( stream, format, data->d );
      break;
    case STUMPLESS_LONG_DOUBLE:
      if( format == NULL )
        result = fprintf( stream, "%Lg", data->l_d );
      else
        result = fprintf( stream, format, data->l_d );
      break;
    case STUMPLESS_UNSIGNED_SHORT_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%i", data->u_s_p[i] );
        else
          result = fprintf( stream, format, data->u_s_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_SHORT_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%i", data->s_p[i] );
        else
          result = fprintf( stream, format, data->s_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_UNSIGNED_INT_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%i", data->u_i_p[i] );
        else
          result = fprintf( stream, format, data->u_i_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_INT_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%i", data->i_p[i] );
        else
          result = fprintf( stream, format, data->i_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_UNSIGNED_LONG_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%li", data->u_l_p[i] );
        else
          result = fprintf( stream, format, data->u_l_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_LONG_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%li", data->l_p[i] );
        else
          result = fprintf( stream, format, data->l_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_UNSIGNED_LONG_LONG_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%lli", data->u_l_l_p[i] );
        else
          result = fprintf( stream, format, data->u_l_l_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_LONG_LONG_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%lli", data->l_l_p[i] );
        else
          result = fprintf( stream, format, data->l_l_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_UNSIGNED_CHAR_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%c", data->u_c_p[i] );
        else
          result = fprintf( stream, format, data->u_c_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_CHAR_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%c", data->c_p[i] );
        else
          result = fprintf( stream, format, data->c_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_FLOAT_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%g", data->f_p[i] );
        else
          result = fprintf( stream, format, data->f_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_DOUBLE_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%g", data->d_p[i] );
        else
          result = fprintf( stream, format, data->d_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_LONG_DOUBLE_POINTER:
      for( i = 0; i < length; i++ ){
        if( format == NULL )
          result = fprintf( stream, "%Lg", data->l_d_p[i] );
        else
          result = fprintf( stream, format, data->l_d_p[i] );
        
        if( result < 0)
          break;
      }
      break;
    case STUMPLESS_STRING:
      if( format == NULL )
        result = fprintf( stream, "%s", data->c_p );
      else
        result = fprintf( stream, format, data->c_p );
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
