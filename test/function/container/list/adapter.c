#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/adapter.h"
#include "private/container/list/adapter.h"
#include "private/container/list/iterator/adapter.h"
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
const char * test_prepend_to( void );
const char * test_rbegin( void );
const char * test_rend( void );
const char * test_size( void );
const char * test_value_through( void );

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
  RUN_TEST( prepend_to )
  RUN_TEST( rbegin )
  RUN_TEST( rend )
  RUN_TEST( size )
  RUN_TEST( value_through )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

TEST_ADD_SEPARATOR( Adapter )

TEST_APPEND( Adapter )

TEST_APPEND_TO( Adapter )

TEST_BACK( Adapter )

TEST_BEGIN( Adapter )

TEST_CBEGIN( Adapter )

TEST_CEND( Adapter )

TEST_CONSTRUCTOR( Adapter )

TEST_CONTAINS( Adapter )

TEST_COPY( Adapter )

TEST_CRBEGIN( Adapter )

TEST_CREND( Adapter )

TEST_DESTRUCTOR( Adapter )

TEST_END( Adapter )

TEST_FRONT( Adapter )

TEST_IS_EMPTY( Adapter )

TEST_PREPEND_TO( Adapter )

TEST_RBEGIN( Adapter )

TEST_REND( Adapter )

TEST_SIZE( Adapter )

// todo implement
const char *
test_value_through
( void )
{
  return NULL;
}
