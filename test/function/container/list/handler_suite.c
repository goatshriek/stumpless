#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/container/list/handler.h"
#include "private/container/list/iterator/handler.h"
#include "private/handler.h"
#include "test/helper.h"
#include "test/inheritance/list.h"

const char * test_add_separator( void );
const char * test_append( void );
const char * test_append_to( void );
const char * test_back( void );
const char * test_begin( void );
const char * test_cbegin( void );
const char * test_cend( void );
const char * test_constructor( void );
const char * test_contains( void );
const char * test_copy( void );
const char * test_crbegin( void );
const char * test_crend( void );
const char * test_destructor( void );
const char * test_end( void );
const char * test_front( void );
const char * test_is_empty( void );
const char * test_output_through( void );
const char * test_prepend_to( void );
const char * test_rbegin( void );
const char * test_rend( void );
const char * test_size( void );

int
main
( void )
{
  unsigned failure_count = 0;
  const char *result;

  RUN_TEST( add_separator )
  RUN_TEST( append )
  RUN_TEST( append_to )
  RUN_TEST( back )
  RUN_TEST( begin )
  RUN_TEST( cbegin )
  RUN_TEST( cend )
  RUN_TEST( constructor )
  RUN_TEST( contains )
  RUN_TEST( copy )
  RUN_TEST( crbegin )
  RUN_TEST( crend )
  RUN_TEST( destructor )
  RUN_TEST( end )
  RUN_TEST( front )
  RUN_TEST( is_empty )
  RUN_TEST( output_through )
  RUN_TEST( prepend_to )
  RUN_TEST( rbegin )
  RUN_TEST( rend )
  RUN_TEST( size )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

TEST_ADD_SEPARATOR( Handler )

TEST_APPEND( Handler )

TEST_APPEND_TO( Handler )

TEST_BACK( Handler )

TEST_BEGIN( Handler )

TEST_CBEGIN( Handler )

TEST_CEND( Handler )

TEST_CONSTRUCTOR( Handler )

TEST_CONTAINS( Handler )

TEST_COPY( Handler )

TEST_CRBEGIN( Handler )

TEST_CREND( Handler )

TEST_DESTRUCTOR( Handler )

TEST_END( Handler )

TEST_FRONT( Handler )

TEST_IS_EMPTY( Handler )

const char *
test_output_through
( void )
{
  HandlerList *list = BuildHandlerList();
  if( !list )
    return "could not build the test list";

  Exception *e = OutputThroughHandlerList( list, NULL );
  if( !e )
    return "a null output did not generate an abnormal status";
  ASSERT_STRINGS_EQUAL( "empty argument", e->name, "a null output did not generate an empty argument error" )

  Output *output = BuildTextOutput();
  if( !output )
    return "could not build the test output";
  e = OutputThroughHandlerList( list, output );
  if( e )
    return "a full output could not pass through the handler list";

  return NULL;
}

TEST_PREPEND_TO( Handler )

TEST_RBEGIN( Handler )

TEST_REND( Handler )

TEST_SIZE( Handler )
