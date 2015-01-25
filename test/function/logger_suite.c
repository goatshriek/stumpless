#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless/exception.h>
#include <stumpless/logger.h>

#include "private/container/list/adapter.h"
#include "private/container/list/formatter.h"
#include "private/container/list/iterator/adapter.h"
#include "private/container/list/iterator/formatter.h"
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
  Adapter *first_adapter;
  Logger *logger;

  logger = malloc( sizeof( logger ) );
  if( !logger )
    return "could not build the test logger";
  logger->targets = NULL;

  first_adapter = malloc( sizeof( Adapter ) );
  if( !first_adapter )
    return "could not build the first test adapter";

  return NULL;
}

const char *
test_append_formatter
( void )
{
  Formatter *first_formatter;
  Logger *logger;

  logger = malloc( sizeof( logger ) );
  if( !logger )
    return "could not build the test logger";
  logger->targets = NULL;

  first_formatter = malloc( sizeof( Formatter ) );
  if( !first_formatter )
    return "could not build the first test formatter";

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
  Logger *logger;

  logger = NewLogger( NULL );
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
