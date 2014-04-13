#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helper.h"

#include "inheritance/list.h"

#include "private/entry_attribute.h"

#include "private/list/entry_attribute.h"

#include "private/list/iterator/entry_attribute.h"

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
const char * test_merge( void );
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
  RUN_TEST( merge )
  RUN_TEST( prepend_to )
  RUN_TEST( rbegin )
  RUN_TEST( rend )
  RUN_TEST( size )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

TEST_ADD_SEPARATOR( EntryAttribute )

TEST_APPEND( EntryAttribute )

TEST_APPEND_TO( EntryAttribute )

TEST_BEGIN( EntryAttribute )

TEST_CBEGIN( EntryAttribute )

TEST_CEND( EntryAttribute )

TEST_CONSTRUCTOR( EntryAttribute )

TEST_CONTAINS( EntryAttribute )

TEST_COPY( EntryAttribute )

TEST_CRBEGIN( EntryAttribute )

TEST_CREND( EntryAttribute )

TEST_DESTRUCTOR( EntryAttribute )

TEST_END( EntryAttribute )

TEST_IS_EMPTY( EntryAttribute )

const char *
test_merge
( void )
{
  EntryAttributeList *primary = NULL;
  EntryAttributeList *secondary = NULL;
  EntryAttributeList *merged;
  
  merged = MergeEntryAttributeLists( primary, secondary );
  FAIL_IF_NOT_NULL( merged, "two null lists were merged into a non-null list" )
  
  primary = BuildEntryAttributeList();
  FAIL_IF_NULL( primary, "could not build the primary list" )
  
  merged = MergeEntryAttributeLists( primary, secondary );
  if( merged != primary )
    return "a null secondary did not return the primary";
  
  merged = MergeEntryAttributeLists( secondary, primary );
  if( merged != primary )
    return "a null primary did not return the secondary";
  
  secondary = NewEntryAttributeList();
  FAIL_IF_NULL( secondary, "could not build the secondary list" )
  EntryAttribute *attribute = malloc( sizeof( EntryAttribute ) );
  FAIL_IF_NULL( attribute, "could not build the attribute" )
  AppendToEntryAttributeList( secondary, attribute );
  
  merged = MergeEntryAttributeLists( primary, secondary );
  if( merged != primary )
    return "the primary list was not the modified list";
  FAIL_IF_NULL( merged, "two lists did not merge properly" )
  
  return NULL;
}

TEST_PREPEND_TO( EntryAttribute )

TEST_RBEGIN( EntryAttribute )

TEST_REND( EntryAttribute )

TEST_SIZE( EntryAttribute )
