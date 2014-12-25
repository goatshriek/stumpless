#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless/logger.h>

#include "private/container/list/adapter.h"
#include "private/container/list/formatter.h"
#include "private/container/list/iterator/adapter.h"
#include "private/container/list/iterator/formatter.h"
#include "private/status.h"
#include "private/type.h"
#include "test/helper.h"

const char * test_append_adapter( void );
const char * test_append_formatter( void );
const char * test_append_handler( void );
const char * test_constructor( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;

  RUN_TEST( append_adapter )
  RUN_TEST( append_formatter )
  RUN_TEST( append_handler )
  //RUN_TEST( constructor ) // todo implement multiprocessing destructor

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_append_adapter
( void )
{
  Logger *logger = malloc( sizeof( logger ) );
  if( !logger )
    return "could not build the test logger";
  logger->targets = NULL;

  Adapter *first_adapter = malloc( sizeof( Adapter ) );
  if( !first_adapter )
    return "could not build the first test adapter";

  /*
  Status * status = AppendAdapterToLogger( logger, first_adapter );
  FAIL_IF_NOT_NULL( status, "could not add an adapter to a NULL adapter list" )
  FAIL_IF_NULL( logger->adapters, "the adapter list was not created" )
  AdapterListIterator * adapters = BeginAdapterList( logger->adapters );
  if( NextInAdapterListIterator( adapters ) != first_adapter )
    return "the adapter was not correctly added to the logger's list";
  DestroyAdapterListIterator( adapters );

  status = AppendAdapterToLogger( logger, first_adapter );
  FAIL_IF_NULL( status, "a duplicate adapter was added to the logger" )
  ASSERT_STRINGS_EQUAL( "duplicate", status->name, "the duplicate adapter was not detected correctly" )

  Adapter * second_adapter = malloc( sizeof( Adapter ) );
  if( !second_adapter )
    return "could not build the second test adapter";

  status = AppendAdapterToLogger( logger, second_adapter );
  FAIL_IF_NOT_NULL( status, "the second adapter was not correctly added" )
  adapters = BeginAdapterList( logger->adapters );
  if( NextInAdapterListIterator( adapters ) != first_adapter )
    return "the adapters were not in the added order";
  if( NextInAdapterListIterator( adapters ) != second_adapter )
    return "the second adapter was not added to the list correctly";
  FAIL_IF_NOT_NULL( NextInAdapterListIterator( adapters ), "more adapters were present in the logger" )
  DestroyAdapterListIterator( adapters );
  */

  return NULL;
}

const char *
test_append_formatter
( void )
{
  Logger * logger = malloc( sizeof( logger ) );
  if( !logger )
    return "could not build the test logger";
  logger->targets = NULL;

  Formatter * first_formatter = malloc( sizeof( Formatter ) );
  if( !first_formatter )
    return "could not build the first test formatter";

  /*
  Status * status = AppendFormatterToLogger( logger, first_formatter );
  FAIL_IF_NOT_NULL( status, "could not add an formatter to a NULL formatter list" )
  FAIL_IF_NULL( logger->formatters, "the formatter list was not created" )
  FormatterListIterator * formatters = BeginFormatterList( logger->formatters );
  if( NextInFormatterListIterator( formatters ) != first_formatter )
    return "the formatter was not correctly added to the logger's list";
  DestroyFormatterListIterator( formatters );

  status = AppendFormatterToLogger( logger, first_formatter );
  FAIL_IF_NULL( status, "a duplicate formatter was added to the logger" )
  ASSERT_STRINGS_EQUAL( "duplicate", status->name, "the duplicate formatter was not detected correctly" )

  Formatter * second_formatter = malloc( sizeof( Formatter ) );
  if( !second_formatter )
    return "could not build the second test formatter";

  status = AppendFormatterToLogger( logger, second_formatter );
  FAIL_IF_NOT_NULL( status, "the second formatter was not correctly added" )
  formatters = BeginFormatterList( logger->formatters );
  if( NextInFormatterListIterator( formatters ) != first_formatter )
    return "the formatters were not in the added order";
  if( NextInFormatterListIterator( formatters ) != second_formatter )
    return "the second formatter was not added to the list correctly";
  FAIL_IF_NOT_NULL( NextInFormatterListIterator( formatters ), "more formatters were present in the logger" )
  DestroyFormatterListIterator( formatters );
  */

  return NULL;
}

const char *
test_append_handler
( void )
{
  return NULL;
}

const char *
test_constructor
( void )
{
  Logger *logger = NewLogger( NULL );
  if( logger )
    return "a logger with no name was created";

  logger = NewLogger( "constructor test logger" );
  if( !logger ){
    return "a new logger could not be created";
  }

  ASSERT_STRINGS_EQUAL( logger->name, "constructor test logger",
                        "the new logger did not have the correct name" )

  return NULL;
}
