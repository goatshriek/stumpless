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
  StumplessValue * value = StumplessValueFromChar( 'c' );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_CHAR )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->c != 'c' )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_double( void )
{
  StumplessValue * value = StumplessValueFromDouble( 3.456 );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_DOUBLE )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->d != 3.456 )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_float( void )
{
  StumplessValue * value = StumplessValueFromFloat( 789.6 );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_FLOAT )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->f != 789.6 )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_int( void )
{
  StumplessValue * value = StumplessValueFromInt( 1234 );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_INT )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->i != 1234 )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_long( void )
{
  StumplessValue * value = StumplessValueFromLong( 123456789L );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_LONG )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->l != 123456789L )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_long_double( void )
{
  StumplessValue * value = StumplessValueFromLongDouble( 5.23e34 );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_LONG_DOUBLE )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->l_d != 5.23e34 )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_long_long( void )
{
  StumplessValue * value = StumplessValueFromLongLong( 1234567890987654321LL );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_LONG_LONG )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->c != 1234567890987654321LL )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_short( void )
{
  StumplessValue * value = StumplessValueFromShort( 127 );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_SHORT )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->s != 127 )
    return "the value did not have the correct data";
  
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
  StumplessValue * value = StumplessValueFromUnsignedChar( 156U );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_UNSIGNED_CHAR )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_c != 156U )
    return "the value did not have the correct data";
  
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
  StumplessValue * value = StumplessValueFromUnsignedLong( 123456789UL );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_UNSIGNED_LONG )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_l != 123456789UL )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_unsigned_long_long( void )
{
  StumplessValue * value = StumplessValueFromUnsignedLongLong( 1234567890987654321ULL );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_UNSIGNED_LONG_LONG )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_l_l != 1234567890987654321ULL )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_unsigned_short( void )
{
  StumplessValue * value = StumplessValueFromUnsignedShort( 250U );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_UNSIGNED_SHORT )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_s != 250U )
    return "the value did not have the correct data";
  
  return NULL;
}
