#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/type.h"
#include "private/value/constructor.h"
#include "test/helper.h"

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
  Boolean * boolean = BuildBoolean();
  FAIL_IF_NULL( boolean, "could not build the test boolean" )
  
  Value * value = NewValueForBoolean( NULL );
  FAIL_IF_NOT_NULL( value, "a null boolean did not generate a null value" )
  
  value = NewValueForBoolean( boolean );
  FAIL_IF_NULL( value, "a non-null boolean generated a null value" )
  if( strcmp( value->profile->name, "boolean" ) != 0 )
    return "the created value did not have the correct type";
  
  return NULL;
}

const char *
test_from_char( void )
{
  Value * value = NewValueForChar( CHAR_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "char" ) != 0 )
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
  
  Value * value = NewValueForDouble( test_value );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "double" ) != 0 )
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
  
  Value * value = NewValueForFloat( test_value );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "float" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->f != test_value )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_int( void )
{
  Value * value = NewValueForInt( INT_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "int" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->i != INT_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_long( void )
{
  Value * value = NewValueForLong( LONG_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "long" ) != 0 )
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
  
  Value * value = NewValueForLongDouble( test_value );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "long double" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->l_d != test_value )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_long_long( void )
{
  Value * value = NewValueForLongLong( LLONG_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "long long" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->l_l != LLONG_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_short( void )
{
  Value * value = NewValueForShort( SHRT_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "short" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->s != SHRT_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_signed_char( void )
{
  Value * value = NewValueForSignedChar( SCHAR_MAX );
  FAIL_IF_NULL( value, "the value could not be built" );
  if( strcmp( value->profile->name, "signed char" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" );
  if( value->data->s_c != SCHAR_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_string( void )
{
  Value * value = NULL;
  
  value = NewValueForString( NULL );
  if( value != NULL )
    return "a null value was not returned for a null string";
  
  value = NewValueForString( "test string 'n such" );
  if( value == NULL )
    return "a null value was returned for a non-null string";
  if( strcmp( value->profile->name, "string" ) != 0 )
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
  Value * value = NewValueForUnsignedChar( UCHAR_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "unsigned char" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_c != UCHAR_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_unsigned_int( void )
{
  Value * value = NULL;
  
  value = NewValueForUnsignedInt( UINT_MAX );
  if( value == NULL )
    return "the value could not be created";
  if( strcmp( value->profile->name, "unsigned int" ) != 0 )
    return "the created value did not have an unsigned int type";
  if( value->data == NULL || value->data->u_i != UINT_MAX )
    return "the value did not contain the correct number";
  
  return NULL;
}

const char *
test_from_unsigned_long( void )
{
  Value * value = NewValueForUnsignedLong( ULONG_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "unsigned long" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_l != ULONG_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_unsigned_long_long( void )
{
  Value * value = NewValueForUnsignedLongLong( ULLONG_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "unsigned long long" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_l_l != ULLONG_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}

const char *
test_from_unsigned_short( void )
{
  Value * value = NewValueForUnsignedShort( USHRT_MAX );
  FAIL_IF_NULL( value, "the value could not be built" )
  if( strcmp( value->profile->name, "unsigned short" ) != 0 )
    return "the value did not have the correct type";
  FAIL_IF_NULL( value->data, "the value did not have any data" )
  if( value->data->u_s != USHRT_MAX )
    return "the value did not have the correct data";
  
  return NULL;
}
