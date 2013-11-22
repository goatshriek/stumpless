#include <stdio.h>
#include <stdlib.h>

#include "private/adapter.h"
#include "private/type.h"

#include "helper.h"

const char * test_add_adapter( void );
const char * test_find_adapter_by_name( void );
const char * test_get_option( void );
const char * test_set_option( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result = NULL;
  
  RUN_TEST( add_adapter )
  RUN_TEST( find_adapter_by_name )
  RUN_TEST( get_option )
  RUN_TEST( set_option )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_add_adapter
( void )
{
  Adapter * adapter = BuildAdapter();
  FAIL_IF_NULL( adapter, "the test adapter could not be built" )
  
  Status * status = AddAdapter( adapter );
  FAIL_IF_NOT_NULL( status, "the new adapter could not be added" )
  
  Adapter * found = FindAdapterByName( adapter->name );
  if( found != adapter )
    return "the value was not added in such a way that it could be retrieved";
  
  return NULL;
}

const char *
test_find_adapter_by_name
( void )
{
  Adapter * adapter = FindAdapterByName( "context" );
  FAIL_IF_NULL( adapter, "the intended adapter could not be retrieved" )
  ASSERT_STRINGS_EQUAL( "context", adapter->name, "the correct adapter was not returned" )
  
  return NULL;
}

const char *
test_get_option
( void )
{
  Adapter * adapter = BuildAdapter();
  FAIL_IF_NULL( adapter, "the test adapter could not be built" )
  
  const char * value = GetAdapterOption( NULL, NULL );
  FAIL_IF_NOT_NULL( value, "two NULL arguments returned a value" )
  
  value = GetAdapterOption( NULL, "whatever" );
  FAIL_IF_NOT_NULL( value, "a NULL adapter returned a value" )
  
  value = GetAdapterOption( adapter, NULL );
  FAIL_IF_NOT_NULL( value, "a NULL option name returned a value" )
  
  value = GetAdapterOption( adapter, "non-existent option" );
  FAIL_IF_NOT_NULL( value, "a non-existent option returned a value" )
  
  value = GetAdapterOption( adapter, "first" );
  FAIL_IF_NULL( value, "the returned value was NULL for an existent option" )
  ASSERT_STRINGS_EQUAL( "1st", value, "the value returned for the option was not correct" )
  
  return NULL;
}

const char *
test_set_option
( void )
{
  Adapter * adapter = BuildAdapter();
  FAIL_IF_NULL( adapter, "the test adapter could not be built" )
  
  const char * option = "test option";
  void * value = "target value";
  
  Status * status = SetAdapterOption( NULL, NULL, NULL );
  FAIL_IF_NULL( status, "three NULL arguments did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetAdapterOption( NULL, NULL, value );
  FAIL_IF_NULL( status, "only a value did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetAdapterOption( NULL, option, value );
  FAIL_IF_NULL( status, "a NULL adapter did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetAdapterOption( NULL, option, NULL );
  FAIL_IF_NULL( status, "only an option did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetAdapterOption( adapter, NULL, value );
  FAIL_IF_NULL( status, "an empty option did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetAdapterOption( adapter, NULL, NULL );
  FAIL_IF_NULL( status, "only a adapter did not raise an error" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )
  
  status = SetAdapterOption( adapter, option, value );
  FAIL_IF_NOT_NULL( status, "could not set an option" )
  
  return NULL;
}
