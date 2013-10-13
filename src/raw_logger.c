#include <stdlib.h>

#include "private/output_profile.h"
#include "private/raw_logger.h"
#include "private/status.h"
#include "private/type.h"
#include "private/value_constructor.h"

#define POINTER_RAW_LOGGER_FUNCTION( type_name, type_specifier )               \
Status *                                                                       \
LogRaw##type_name( type_specifier raw )                                        \
{                                                                              \
  if( raw == NULL )                                                            \
    return RaiseAbnormalStatus( "empty argument" );                            \
                                                                               \
  Value * value = ValueFrom##type_name( raw );                                 \
  if( value == NULL )                                                          \
    return RaiseAbnormalStatus( "constructor failure" );                       \
                                                                               \
  Output * output;                                                             \
  output = malloc( sizeof( Output ) );                                         \
  if( output == NULL )                                                         \
    return RaiseAbnormalStatus( "memory allocation failure" );                 \
                                                                               \
  output->data = malloc( sizeof( Type ) );                                     \
  if( output->data == NULL )                                                   \
    return RaiseAbnormalStatus( "memory allocation failure" );                 \
                                                                               \
  output->data->c_p = value->profile->to_string( value );                      \
  output->profile = FindOutputProfileByName( "raw string" );                   \
                                                                               \
  return NULL;                                                                 \
}

#define VALUE_RAW_LOGGER_FUNCTION( type_name, type_specifier )                 \
Status *                                                                       \
LogRaw##type_name( type_specifier raw )                                        \
{                                                                              \
  Value * value = ValueFrom##type_name( raw );                                 \
  if( value == NULL )                                                          \
    return RaiseAbnormalStatus( "constructor failure" );                       \
                                                                               \
  Output * output;                                                             \
  output = malloc( sizeof( Output ) );                                         \
  if( output == NULL )                                                         \
    return RaiseAbnormalStatus( "memory allocation failure" );                 \
                                                                               \
  output->data = malloc( sizeof( Type ) );                                     \
  if( output->data == NULL )                                                   \
    return RaiseAbnormalStatus( "memory allocation failure" );                 \
                                                                               \
  output->data->c_p = value->profile->to_string( value );                      \
  output->profile = FindOutputProfileByName( "raw string" );                   \
                                                                               \
  return NULL;                                                                 \
}

POINTER_RAW_LOGGER_FUNCTION( Boolean, Boolean * )

VALUE_RAW_LOGGER_FUNCTION( Char, char )

VALUE_RAW_LOGGER_FUNCTION( Double, double )

VALUE_RAW_LOGGER_FUNCTION( Float, float )

VALUE_RAW_LOGGER_FUNCTION( Int, int )

VALUE_RAW_LOGGER_FUNCTION( Long, long )

VALUE_RAW_LOGGER_FUNCTION( LongDouble, long double )

VALUE_RAW_LOGGER_FUNCTION( LongLong, long long )

VALUE_RAW_LOGGER_FUNCTION( Short, short )

VALUE_RAW_LOGGER_FUNCTION( SignedChar, signed char )

POINTER_RAW_LOGGER_FUNCTION( String, const char * )

VALUE_RAW_LOGGER_FUNCTION( UnsignedChar, unsigned char )

VALUE_RAW_LOGGER_FUNCTION( UnsignedInt, unsigned )

VALUE_RAW_LOGGER_FUNCTION( UnsignedLong, unsigned long )

VALUE_RAW_LOGGER_FUNCTION( UnsignedLongLong, unsigned long long )

VALUE_RAW_LOGGER_FUNCTION( UnsignedShort, unsigned short )
