#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "helper.h"

const char * test_from_char( void );
const char * test_from_double( void );
const char * test_from_float( void );
const char * test_from_int( void );
const char * test_from_long( void );
const char * test_from_long_double( void );
const char * test_from_long_long( void );
const char * test_from_short( void );
const char * test_from_string( void );
const char * test_from_unsigned_char( void );
const char * test_from_unsigned_int( void );
const char * test_from_unsigned_long( void );
const char * test_from_unsigned_long_long( void );
const char * test_from_unsigned_short( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( from_char )
  RUN_TEST( from_double )
  RUN_TEST( from_float )
  RUN_TEST( from_int )
  RUN_TEST( from_long )
  RUN_TEST( from_long_double )
  RUN_TEST( from_long_long )
  RUN_TEST( from_short )
  RUN_TEST( from_string )
  RUN_TEST( from_unsigned_char )
  RUN_TEST( from_unsigned_int )
  RUN_TEST( from_unsigned_long )
  RUN_TEST( from_unsigned_long_long )
  RUN_TEST( from_unsigned_short )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_from_char( void )
{
  return NULL;
}

const char *
test_from_double( void )
{
  return NULL;
}

const char *
test_from_float( void )
{
  return NULL;
}

const char *
test_from_int( void )
{
  return NULL;
}

const char *
test_from_long( void )
{
  return NULL;
}

const char *
test_from_long_double( void )
{
  return NULL;
}

const char *
test_from_long_long( void )
{
  return NULL;
}

const char *
test_from_short( void )
{
  return NULL;
}

const char *
test_from_string( void )
{
  StumplessValue * value = NULL;
  
  value = StumplessValueFromString( NULL );
  if( value != NULL )
    return "a null value was not returned for a null string";
  
  value = StumplessValueFromString( "test string 'n such" );
  if( value == NULL )
    return "a null value was returned for a non-null string";
  if( value->type != STUMPLESS_STRING )
    return "the value did not have a string type";
  if( value->data == NULL )
    return "the value did not have any data";
  if( strcmp( value->data->c_p, "test string 'n such" ) != 0 )
    return "the value string did not match the initial string";
  
  return NULL;
}

const char *
test_from_unsigned_char( void )
{
  return NULL;
}

const char *
test_from_unsigned_int( void )
{
  StumplessValue * value = NULL;
  
  value = StumplessValueFromUnsignedInt( 3 );
  if( value == NULL )
    return "the value could not be created";
  if( value->type != STUMPLESS_UNSIGNED_INT )
    return "the created value did not have an unsigned int type";
  if( value->data == NULL || value->data->u_i != 3 )
    return "the value did not contain the correct number";
  
  return NULL;
}

const char *
test_from_unsigned_long( void )
{
  return NULL;
}

const char *
test_from_unsigned_long_long( void )
{
  return NULL;
}

const char *
test_from_unsigned_short( void )
{
  return NULL;
}
