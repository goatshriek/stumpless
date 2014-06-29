#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helper.h"

#include "inheritance/list.h"

#include "private/event_attribute.h"

#include "private/container/list/event_attribute.h"

#include "private/container/list/iterator/event_attribute.h"

const char * test_add_separator( void );
const char * test_append( void );
const char * test_append_to( void );
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

TEST_ADD_SEPARATOR( EventAttribute )

TEST_APPEND( EventAttribute )

TEST_APPEND_TO( EventAttribute )

TEST_BEGIN( EventAttribute )

TEST_CBEGIN( EventAttribute )

TEST_CEND( EventAttribute )

TEST_CONSTRUCTOR( EventAttribute )

TEST_CONTAINS( EventAttribute )

TEST_COPY( EventAttribute )

TEST_CRBEGIN( EventAttribute )

TEST_CREND( EventAttribute )

TEST_DESTRUCTOR( EventAttribute )

TEST_END( EventAttribute )

TEST_IS_EMPTY( EventAttribute )

TEST_PREPEND_TO( EventAttribute )

TEST_RBEGIN( EventAttribute )

TEST_REND( EventAttribute )

TEST_SIZE( EventAttribute )
