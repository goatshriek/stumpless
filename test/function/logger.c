#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/adapter_list.h"
#include "private/formatter_list.h"
#include "private/logger.h"
#include "private/type.h"

#include "helper.h"

const char * test_append_adapter( void );
const char * test_append_formatter( void );
const char * test_append_handler( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( append_adapter )
  RUN_TEST( append_formatter )
  RUN_TEST( append_handler )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_append_adapter
( void )
{
  Logger * logger = malloc( sizeof( logger ) );
  if( logger == NULL )
    return "could not build the test logger";
  logger->adapters = NULL;
  
  Adapter * first_adapter = malloc( sizeof( Adapter ) );
  if( first_adapter == NULL )
    return "could not build the first test adapter";
  
  Status * status = AppendAdapterToLogger( logger, first_adapter );
  FAIL_IF_NOT_NULL( status, "could not add an adapter to a NULL adapter list" )
  FAIL_IF_NULL( logger->adapters, "the adapter list was not created" )
  if( BeginAdapterList( logger->adapters ) != first_adapter )
    return "the adapter was not correctly added to the logger's list";
  
  status = AppendAdapterToLogger( logger, first_adapter );
  FAIL_IF_NULL( status, "a duplicate adapter was added to the logger" )
  ASSERT_STRINGS_EQUAL( "duplicate", status->name, "the duplicate adapter was not detected correctly" )
  
  Adapter * second_adapter = malloc( sizeof( Adapter ) );
  if( second_adapter == NULL )
    return "could not build the second test adapter";
  
  status = AppendAdapterToLogger( logger, second_adapter );
  FAIL_IF_NOT_NULL( status, "the second adapter was not correctly added" )
  if( BeginAdapterList( logger->adapters ) != first_adapter )
    return "the adapters were not in the added order";
  if( NextInAdapterList( logger->adapters ) != second_adapter )
    return "the second adapter was not added to the list correctly";
  FAIL_IF_NOT_NULL( NextInAdapterList( logger->adapters ), "more adapters were present in the logger" )
  
  return NULL;
}

const char *
test_append_formatter
( void )
{
  Logger * logger = malloc( sizeof( logger ) );
  if( logger == NULL )
    return "could not build the test logger";
  logger->formatters = NULL;
  
  Formatter * first_formatter = malloc( sizeof( Formatter ) );
  if( first_formatter == NULL )
    return "could not build the first test formatter";
  
  Status * status = AppendFormatterToLogger( logger, first_formatter );
  FAIL_IF_NOT_NULL( status, "could not add an formatter to a NULL formatter list" )
  FAIL_IF_NULL( logger->formatters, "the formatter list was not created" )
  if( BeginFormatterList( logger->formatters ) != first_formatter )
    return "the formatter was not correctly added to the logger's list";
  
  status = AppendFormatterToLogger( logger, first_formatter );
  FAIL_IF_NULL( status, "a duplicate formatter was added to the logger" )
  ASSERT_STRINGS_EQUAL( "duplicate", status->name, "the duplicate formatter was not detected correctly" )
  
  Formatter * second_formatter = malloc( sizeof( Formatter ) );
  if( second_formatter == NULL )
    return "could not build the second test formatter";
  
  status = AppendFormatterToLogger( logger, second_formatter );
  FAIL_IF_NOT_NULL( status, "the second formatter was not correctly added" )
  if( BeginFormatterList( logger->formatters ) != first_formatter )
    return "the formatters were not in the added order";
  if( NextInFormatterList( logger->formatters ) != second_formatter )
    return "the second formatter was not added to the list correctly";
  FAIL_IF_NOT_NULL( NextInFormatterList( logger->formatters ), "more formatters were present in the logger" )
  
  return NULL;
}

const char *
test_append_handler
( void )
{
  return NULL;
}
