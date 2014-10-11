#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "helper.h"
#include "inheritance/list.h"
#include "private/container/list/record_attribute.h"
#include "private/container/list/event_attribute.h"
#include "private/container/list/const_iterator/record_attribute.h"
#include "private/container/list/const_iterator/event_attribute.h"
#include "private/container/list/iterator/record_attribute.h"
#include "private/record_attribute.h"
#include "static/container/list.h"
#include "static/container/list/record_attribute.h"

const char * test_add_separator( void );
const char * test_append( void );
const char * test_append_to( void );
const char * test_back( void );
const char * test_begin( void );
const char * test_cbegin( void );
const char * test_cend( void );
const char * test_constructor( void );
const char * test_contains( void );
const char * test_contains_event_attribute( void );
const char * test_copy( void );
const char * test_crbegin( void );
const char * test_crend( void );
const char * test_destructor( void );
const char * test_end( void );
const char * test_for_event_attribute_list( void );
const char * test_front( void );
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
  RUN_TEST( back )
  RUN_TEST( begin )
  RUN_TEST( cbegin )
  RUN_TEST( cend )
  RUN_TEST( constructor )
  RUN_TEST( contains )
  RUN_TEST( contains_event_attribute )
  RUN_TEST( copy )
  RUN_TEST( crbegin )
  RUN_TEST( crend )
  RUN_TEST( destructor )
  RUN_TEST( end )
  RUN_TEST( for_event_attribute_list )
  RUN_TEST( front )
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

TEST_ADD_SEPARATOR( RecordAttribute )

TEST_APPEND( RecordAttribute )

TEST_APPEND_TO( RecordAttribute )

TEST_BACK( RecordAttribute )

TEST_BEGIN( RecordAttribute )

TEST_CBEGIN( RecordAttribute )

TEST_CEND( RecordAttribute )

TEST_CONSTRUCTOR( RecordAttribute )

TEST_CONTAINS( RecordAttribute )

const char *
test_contains_event_attribute
( void )
{
  if( RecordAttributeListContainsEventAttribute( NULL, NULL ) )
    return "a null list contained a null attribute";

  const EventAttribute *attribute = BuildEventAttribute();
  if( !attribute )
    return "could not build test event attribute";

  if( RecordAttributeListContainsEventAttribute( NULL, attribute ) )
    return "a null list contained a null attribute";

  RecordAttributeList *list = BuildRecordAttributeList();
  if( !list )
    return "could not build test record attribute list";

  if( RecordAttributeListContainsEventAttribute( list, NULL ) )
    return "an record attribute list contained a null event attribute";

  if( RecordAttributeListContainsEventAttribute( list, attribute ) )
    return "an record attribute list contained an event attribute not in it";

  RecordAttribute * record_attribute = list->list->first->value;
  attribute = record_attribute->event_attribute;

  if( !RecordAttributeListContainsEventAttribute( list, attribute ) )
    return "the list did not contain an attribute pulled from it";

  return NULL;
}

TEST_COPY( RecordAttribute )

TEST_CRBEGIN( RecordAttribute )

TEST_CREND( RecordAttribute )

TEST_DESTRUCTOR( RecordAttribute )

TEST_END( RecordAttribute )

const char *
test_for_event_attribute_list
( void )
{
  RecordAttributeList *list = RecordAttributeListForEventAttributeList( NULL );
  if( list )
    return "a null event attribute list returned a non-null record attribute list";

  EventAttributeList *event_attribute_list = BuildEventAttributeList();
  if( !event_attribute_list )
    return "could not build the event attribute list";

  list = RecordAttributeListForEventAttributeList( event_attribute_list );
  if( !list )
    return "a list could not be created from an event attribute list";

  const RecordAttribute *record_attribute;
  const EventAttribute *event_attribute;
  RecordAttributeListConstIterator *record_attributes = CBeginRecordAttributeList( list );
  EventAttributeListConstIterator *event_attributes = CBeginEventAttributeList( event_attribute_list );
  while( RecordAttributeListConstIteratorHasNext( record_attributes ) ){
    record_attribute = NextInRecordAttributeListConstIterator( record_attributes );
    event_attribute = NextInEventAttributeListConstIterator( event_attributes );
    if( record_attribute->event_attribute != event_attribute )
      return "an record attribute did not have the correct event attribute";
  }

  return NULL;
}

TEST_FRONT( RecordAttribute )

TEST_IS_EMPTY( RecordAttribute )

const char *
test_merge
( void )
{
  RecordAttributeList *primary = NULL;
  RecordAttributeList *secondary = NULL;
  RecordAttributeList *merged;

  merged = MergeRecordAttributeLists( primary, secondary );
  FAIL_IF_NOT_NULL( merged, "two null lists were merged into a non-null list" )

  primary = BuildRecordAttributeList();
  FAIL_IF_NULL( primary, "could not build the primary list" )

  merged = MergeRecordAttributeLists( primary, secondary );
  if( merged != primary )
    return "a null secondary did not return the primary";

  merged = MergeRecordAttributeLists( secondary, primary );
  if( merged != primary )
    return "a null primary did not return the secondary";

  secondary = NewRecordAttributeList();
  FAIL_IF_NULL( secondary, "could not build the secondary list" )
  RecordAttribute *attribute = malloc( sizeof( RecordAttribute ) );
  FAIL_IF_NULL( attribute, "could not build the attribute" )
  AppendToRecordAttributeList( secondary, attribute );

  merged = MergeRecordAttributeLists( primary, secondary );
  if( merged != primary )
    return "the primary list was not the modified list";
  FAIL_IF_NULL( merged, "two lists did not merge properly" )

  return NULL;
}

TEST_PREPEND_TO( RecordAttribute )

TEST_RBEGIN( RecordAttribute )

TEST_REND( RecordAttribute )

TEST_SIZE( RecordAttribute )
