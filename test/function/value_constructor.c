#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

#include "helper.h"

const char * test_from_boolean( void );
const char * test_from_char( void );
const char * test_from_double( void );
const char * test_from_float( void );
const char * test_from_int( void );
const char * test_from_long( void );
const char * test_from_long_double( void );
const char * test_from_long_long( void );
const char * test_from_short( void );
const char * test_from_signed_char( void );
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
  
  RUN_TEST( from_boolean )
  RUN_TEST( from_char )
  RUN_TEST( from_double )
  RUN_TEST( from_float )
  RUN_TEST( from_int )
  RUN_TEST( from_long )
  RUN_TEST( from_long_double )
  RUN_TEST( from_long_long )
  RUN_TEST( from_short )
  RUN_TEST( from_signed_char )
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
test_from_boolean( void )
{
  StumplessBoolean * boolean = StumplessBuildBoolean();
  FAIL_IF_NULL( boolean, "could not build the test boolean" )
  
  StumplessValue * value = StumplessValueFromBoolean( NULL );
  FAIL_IF_NOT_NULL( value, "a null boolean did not generate a null value" )
  
  value = StumplessValueFromBoolean( boolean );
  FAIL_IF_NULL( value, "a non-null boolean generated a null value" )
  if( strcmp( value->profile->name, "Boolean" ) != 0 )
    return "the created value did not have the correct type";
  
  return "need to implement";
}

const char *
test_from_char( void )
{
  StumplessValue * value = StumplessValueFromChar( CHAR_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "Char" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->c != CHAR_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_double( void )
{
  double test_value = 3.456;
  
  StumplessValue * value = StumplessValueFromDouble( test_value );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "Double" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->d != test_value )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_float( void )
{
  float test_value = 789.64;
  
  StumplessValue * value = StumplessValueFromFloat( test_value );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "Float" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->f != test_value )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_int( void )
{
  StumplessValue * value = StumplessValueFromInt( INT_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_INT )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->i != INT_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_long( void )
{
  StumplessValue * value = StumplessValueFromLong( LONG_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_LONG )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->l != LONG_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_long_double( void )
{
  long double test_value = 5.23e34;
  
  StumplessValue * value = StumplessValueFromLongDouble( test_value );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_LONG_DOUBLE )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->l_d != test_value )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_long_long( void )
{
  StumplessValue * value = StumplessValueFromLongLong( LLONG_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_LONG_LONG )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->l_l != LLONG_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_short( void )
{
  StumplessValue * value = StumplessValueFromShort( SHRT_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_SHORT )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->s != SHRT_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_signed_char( void )
{
  StumplessValue * value = StumplessValueFromSignedChar( SCHAR_MAX );
  FAIL_IF_NULL( value, "the value could not be built" );
  if( value->type != STUMPLESS_SIGNED_CHAR )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" );
  if( value->data->s_c != SCHAR_MAX )
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
  StumplessValue * value = StumplessValueFromUnsignedChar( UCHAR_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_UNSIGNED_CHAR )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_c != UCHAR_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_unsigned_int( void )
{
  StumplessValue * value = NULL;
  
  value = StumplessValueFromUnsignedInt( UINT_MAX );
  if( value == NULL )
    return "the value could not be created";
  if( value->type != STUMPLESS_UNSIGNED_INT )
    return "the created value did not have an unsigned int type";
  if( value->data == NULL || value->data->u_i != UINT_MAX )
    return "the value did not contain the correct number";
  
  return NULL;
}

const char *
test_from_unsigned_long( void )
{
  StumplessValue * value = StumplessValueFromUnsignedLong( ULONG_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_UNSIGNED_LONG )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_l != ULONG_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_unsigned_long_long( void )
{
  StumplessValue * value = StumplessValueFromUnsignedLongLong( ULLONG_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_UNSIGNED_LONG_LONG )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_l_l != ULLONG_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_unsigned_short( void )
{
  StumplessValue * value = StumplessValueFromUnsignedShort( USHRT_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( value->type != STUMPLESS_UNSIGNED_SHORT )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_s != USHRT_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}
