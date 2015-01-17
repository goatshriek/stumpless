#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/container/list/filter.h"
#include "private/container/list/iterator/filter.h"
#include "private/filter.h"
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
const char * test_output_through( void );
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
  RUN_TEST( record_through )
  RUN_TEST( front )
  RUN_TEST( is_empty )
  RUN_TEST( output_through )
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

TEST_ADD_SEPARATOR( Filter )

TEST_APPEND( Filter )

TEST_APPEND_TO( Filter )

TEST_BACK( Filter )

TEST_BEGIN( Filter )

TEST_CBEGIN( Filter )

TEST_CEND( Filter )

TEST_CONSTRUCTOR( Filter )

TEST_CONTAINS( Filter )

TEST_COPY( Filter )

TEST_CRBEGIN( Filter )

TEST_CREND( Filter )

TEST_DESTRUCTOR( Filter )

TEST_END( Filter )

const char *
test_record_through
( void )
{
  Event *event;
  FilterList *list;
  Record *record;
  unsigned accepted;

  list = BuildFilterList();
  FAIL_IF_NULL( list, "could not build the test list" )

  record = BuildEmptyRecord();
  FAIL_IF_NULL( record, "the test record could not be built" )

  accepted = RecordThroughFilterList( NULL, NULL );
  if( !accepted )
    return "a null list did not accept its input";

  accepted = RecordThroughFilterList( list, NULL );
  if( accepted )
    return "a null record made it through the filter list";

  accepted = RecordThroughFilterList( list, record );
  if( accepted )
    return "an empty record made it through the filter list";

  record = BuildRecord();
  accepted = RecordThroughFilterList( list, record );
  if( !accepted )
    return "a full record was not accepted by the list";

  event = BuildEvent();
  if( !event )
    return "could not build test Event";
  event->level = NULL;

  record->event = event;
  accepted = RecordThroughFilterList( list, record );
  if( accepted )
    return "an record without a level made it through the list";

  return NULL;
}

TEST_FRONT( Filter )

TEST_IS_EMPTY( Filter )

// todo implement
const char *
test_output_through
( void )
{
  return NULL;
}

TEST_PREPEND_TO( Filter )

TEST_RBEGIN( Filter )

TEST_REND( Filter )

TEST_SIZE( Filter )

// todo implement
const char *
test_value_through
( void )
{
  return NULL;
}
