#include <stdio.h>
#include <stdlib.h>

#include "private/adapter.h"
#include "test/function/adapter.h"
#include "test/helper.h"
#include "test/type.h"

int
main( void )
{
  const char *result = NULL;
  unsigned failure_count = 0;

  TEST( Adapt )
  TEST( AddAdapter )
  TEST( FindAdapterByName )
  TEST( GetOption )
  TEST( SetOption )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestAdapt
( void )
{
  Adapter *adapter;
  Record *record, *result;

  result = AdaptRecord( NULL, NULL );
  if( result )
    return "two NULL arguments did not return a NULL";

  adapter = BuildAdapter();
  if( !adapter )
    return "could not build test Adapter";

  result = AdaptRecord( adapter, NULL );
  if( result )
    return "a NULL Record did not return a NULL";

  record = BuildRecord();
  if( !record )
    return "could not build test Record";

  result = AdaptRecord( adapter, record );
  if( result != record )
    return "the Record could not be adapted";

  if( TestLogGetLastAdapter() != adapter )
    return "the Adapter was not actually run";

  if( TestLogGetLastAdaptedRecord() != record )
    return "the Record was not adapted";

  return NULL;
}

const char *
TestAddAdapter
( void )
{
  Adapter *adapter, *found;
  Status *status;

  adapter = BuildAdapter();
  if( !adapter )
    return "the test adapter could not be built";

  status = AddAdapter( adapter );
  if( status )
    return "the new adapter could not be added";

  found = FindAdapterByName( adapter->name );
  if( found != adapter )
    return "the value was not added in such a way that it could be retrieved";

  return NULL;
}

const char *
TestFindAdapterByName
( void )
{
  Adapter *adapter;

  adapter = FindAdapterByName( "context" );
  if( !adapter )
    return "the intended adapter could not be retrieved";

  ASSERT_STRINGS_EQUAL( "context", adapter->name, "the correct adapter was not returned" )

  return NULL;
}

const char *
TestGetOption
( void )
{
  Adapter *adapter;
  const char *value;

  value = GetAdapterOption( NULL, NULL );
  if( value )
    return "two NULL arguments returned a value";

  value = GetAdapterOption( NULL, "whatever" );
  if( value )
    return "a NULL adapter returned a value";

  adapter = BuildAdapter();
  if( !adapter )
    return "the test adapter could not be built";

  value = GetAdapterOption( adapter, NULL );
  if( value )
    return "a NULL option name returned a value";

  value = GetAdapterOption( adapter, "non-existent option" );
  if( value )
    return "a non-existent option returned a value";

  value = GetAdapterOption( adapter, "first" );
  if( !value )
    return "the returned value was NULL for an existent option";

  ASSERT_STRINGS_EQUAL( "1st", value, "the value returned for the option was not correct" )

  return NULL;
}

const char *
TestSetOption
( void )
{
  Adapter *adapter;
  const char *option;
  Status *status;
  void *value;

  status = SetAdapterOption( NULL, NULL, NULL );
  if( !status )
    return "three NULL arguments did not raise an error";
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )

  value = "target value";
  status = SetAdapterOption( NULL, NULL, value );
  if( !status )
    return "only a value did not raise an error";
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )

  option = "test option";
  status = SetAdapterOption( NULL, option, value );
  if( !status )
    return "a NULL adapter did not raise an error";
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )

  status = SetAdapterOption( NULL, option, NULL );
  if( !status )
    return "only an option did not raise an error";
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )

  adapter = BuildAdapter();
  if( !adapter )
    return "the test adapter could not be built";
  status = SetAdapterOption( adapter, NULL, value );
  if( !status )
    return "an empty option did not raise an error";
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )

  status = SetAdapterOption( adapter, NULL, NULL );
  if( !status )
    return "only a adapter did not raise an error";
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "the error raised by empty argument was not correct" )

  status = SetAdapterOption( adapter, option, value );
  if( status )
    return "could not set an option";

  return NULL;
}
