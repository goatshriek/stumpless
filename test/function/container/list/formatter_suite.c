#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/container/list/formatter.h"
#include "private/container/list/iterator/formatter.h"
#include "private/formatter.h"
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
const char * test_record_through( void );
const char * test_front( void );
const char * test_is_empty( void );
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
  RUN_TEST( record_through )
  RUN_TEST( front )
  RUN_TEST( is_empty )
  RUN_TEST( prepend_to )
  RUN_TEST( rbegin )
  RUN_TEST( rend )
  RUN_TEST( size )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

TEST_ADD_SEPARATOR( Formatter )

TEST_APPEND( Formatter )

TEST_APPEND_TO( Formatter )

TEST_BACK( Formatter )

TEST_BEGIN( Formatter )

TEST_CBEGIN( Formatter )

TEST_CEND( Formatter )

TEST_CONSTRUCTOR( Formatter )

TEST_CONTAINS( Formatter )

TEST_COPY( Formatter )

TEST_CRBEGIN( Formatter )

TEST_CREND( Formatter )

TEST_DESTRUCTOR( Formatter )

TEST_END( Formatter )

// todo implement
const char *
test_record_through
( void )
{
  return NULL;
}

TEST_FRONT( Formatter )

TEST_IS_EMPTY( Formatter )

TEST_PREPEND_TO( Formatter )

TEST_RBEGIN( Formatter )

TEST_REND( Formatter )

TEST_SIZE( Formatter )
