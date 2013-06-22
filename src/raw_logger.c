#include <stdlib.h>

#include <configuration.h>
#include <raw_logger.h>
#include <status_checker.h>
#include <type.h>
#include <value_constructor.h>

#define RAW_LOGGER_FUNCTION( type_name, type_specifier )                       \
StumplessStatusCode                                                            \
StumplessLogRaw##type_name( type_specifier raw )                               \
{                                                                              \
  StumplessValue * value = StumplessValueFrom##type_name( raw );               \
  if( value == NULL )                                                          \
    return STUMPLESS_FAILURE;                                                  \
                                                                               \
  StumplessFormattedOutput * output;                                           \
  output = malloc( sizeof( StumplessFormattedOutput ) );                       \
  if( output == NULL )                                                         \
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;                                \
                                                                               \
  output->data = malloc( sizeof( StumplessType ) );                            \
  if( output->data == NULL )                                                   \
    return STUMPLESS_MEMORY_ALLOCATION_FAILURE;                                \
                                                                               \
  output->data->c_p = value->profile->to_string( value );                      \
  output->profile = StumplessFindOutputProfileByName( "raw string" );          \
                                                                               \
  return STUMPLESS_FAILURE;                                                    \
}

RAW_LOGGER_FUNCTION( Char, char )

RAW_LOGGER_FUNCTION( Double, double )

RAW_LOGGER_FUNCTION( Float, float )

RAW_LOGGER_FUNCTION( Int, int )

RAW_LOGGER_FUNCTION( Long, long )

RAW_LOGGER_FUNCTION( LongDouble, long double )

RAW_LOGGER_FUNCTION( LongLong, long long )

RAW_LOGGER_FUNCTION( Short, short )

RAW_LOGGER_FUNCTION( SignedChar, signed char )

RAW_LOGGER_FUNCTION( UnsignedChar, unsigned char )

RAW_LOGGER_FUNCTION( UnsignedInt, unsigned )

RAW_LOGGER_FUNCTION( UnsignedLong, unsigned long )

RAW_LOGGER_FUNCTION( UnsignedLongLong, unsigned long long )

RAW_LOGGER_FUNCTION( UnsignedShort, unsigned short )
