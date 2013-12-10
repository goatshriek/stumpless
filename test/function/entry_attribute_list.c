#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/entry_attribute_list.h"
#include "private/static/entry_attribute_list.h"
#include "private/type.h"

#include "helper.h"

const char * test_appender( void );
const char * test_begin( void );
const char * test_constructor( void );
const char * test_copy( void );
const char * test_destructor( void );
const char * test_is_empty( void );
const char * test_merge_lists( void );
const char * test_next( void );
const char * test_prepender( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( appender )
  RUN_TEST( begin )
  RUN_TEST( constructor )
  RUN_TEST( copy )
  RUN_TEST( destructor )
  RUN_TEST( is_empty )
  RUN_TEST( merge_lists )
  RUN_TEST( next )
  RUN_TEST( prepender )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_appender
( void )
{
  Status * status;
  EntryAttributeList * list = NewEntryAttributeList();
  if( list == NULL )
    return "the list was not created";
  
  EntryAttribute * attribute_1 = BuildEntryAttribute();
  
  EntryAttribute * attribute_2 = BuildEntryAttribute();
  
  EntryAttribute * attribute_3 = BuildEntryAttribute();
  
  EntryAttribute * attribute_4 = BuildEntryAttribute();
  
  status = AppendToEntryAttributeList( list, attribute_1 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToEntryAttributeList( list, attribute_2 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToEntryAttributeList( list, attribute_3 );
  if( status != NULL )
    return "the node was not successfully added";
  
  status = AppendToEntryAttributeList( list, attribute_4 );
  if( status != NULL )
    return "the node was not successfully added";
  
  EntryAttribute * attribute = BeginEntryAttributeList( list );
  FAIL_IF_NULL( attribute, "the list did not have a first node" )
  if( attribute != attribute_1 )
    return "the first attribute was not correct";
  
  return NULL;
}

const char *
test_begin
( void )
{
  EntryAttributeList * list = BuildEntryAttributeList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  EntryAttribute * attribute = BeginEntryAttributeList( list );
  FAIL_IF_NULL( attribute, "a attribute was returned from a newly-constructed list" )
  
  return NULL;
}

const char *
test_constructor
( void )
{
  EntryAttributeList * list = NULL;
  
  list = NewEntryAttributeList();
  
  if( list == NULL )
    return "the list was not created";
  
  EntryAttribute * attribute = BeginEntryAttributeList( list );
  FAIL_IF_NOT_NULL( attribute, "a newly-constructed list already had members" )
  
  return NULL;
}

const char *
test_copy
( void )
{
  EntryAttributeList * list = BuildEntryAttributeList();
  if( list == NULL )
    return "could not build the test list";
  
  EntryAttributeList * copy;
  
  copy = CopyEntryAttributeList( NULL );
  if( copy != NULL )
    return "the copy was not null for a null pointer";
  
  copy = CopyEntryAttributeList( list );
  FAIL_IF_NULL( copy, "the copy was null for a non-null pointer" )
  if( copy == list )
    return "the copy was equal to the original list";
  
  EntryAttribute * original_attribute = BeginEntryAttributeList( list );
  EntryAttribute * copy_attribute = BeginEntryAttributeList( copy );
  while( original_attribute != NULL ){
    if( original_attribute != copy_attribute )
      return "the copy was not an accurate copy of the original";
    original_attribute = NextInEntryAttributeList( list );
    copy_attribute = NextInEntryAttributeList( copy );
  }
  
  return NULL;
}

const char *
test_destructor
( void )
{
  EntryAttributeList * list = NewEntryAttributeList();
  
  if( list == NULL )
    return "the list was not created";
  
  DestroyEntryAttributeList( list );
  
  list = BuildEntryAttributeList();
  if( list == NULL )
     return "could not build the test list";
  
  DestroyEntryAttributeList( list );
  
  return NULL;
}

const char *
test_is_empty
( void )
{
  EntryAttributeList * list = NULL;
  if( !EntryAttributeListIsEmpty( list ) )
    return "a null list pointer was deemed empty";
  
  list = NewEntryAttributeList();
  if( !EntryAttributeListIsEmpty( list ) )
    return "a newly created list pointer was not deemed empty";
  
  list = BuildEntryAttributeList();
  if( list == NULL )
    return "could not build the test list";
  if( EntryAttributeListIsEmpty( list ) )
    return "a full list was deemed empty";
  
  return NULL;
}

const char *
test_merge_lists
( void )
{
  EntryAttributeList * primary = NULL;
  EntryAttributeList * secondary = NULL;
  EntryAttributeList * merged;
  
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
  EntryAttribute * attribute = malloc( sizeof( EntryAttribute ) );
  FAIL_IF_NULL( attribute, "could not build the attribute" )
  AppendToEntryAttributeList( secondary, attribute );
  
  merged = MergeEntryAttributeLists( primary, secondary );
  if( merged != primary )
    return "the primary list was not the modified list";
  FAIL_IF_NULL( merged, "two lists did not merge properly" )
  
  return NULL;
}

const char *
test_next
( void )
{
  EntryAttributeList * list = BuildEntryAttributeList();
  FAIL_IF_NULL( list, "could not build the test list" )
  
  EntryAttribute * attribute = BeginEntryAttributeList( list );
  FAIL_IF_NULL( attribute, "a attribute was not returned from the start call" )
  
  attribute = NextInEntryAttributeList( list );
  FAIL_IF_NULL( attribute, "a attribute was not returned from the next call" )
  
  return NULL;
}

const char *
test_prepender( void )
{
  EntryAttributeList * list = NewEntryAttributeList();
  FAIL_IF_NULL( list, "could not build a new test list" )
  
  EntryAttribute * attribute = BuildEntryAttribute();
  FAIL_IF_NULL( list, "could not build the test attribute" );
  
  Status * status = PrependToEntryAttributeList( NULL, NULL );
  FAIL_IF_NULL( status, "two empty arguments did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "two empty arguments did not generate the appropriate status code" )
  
  status = PrependToEntryAttributeList( list, NULL );
  FAIL_IF_NULL( status, "an empty value did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "an empty value did not generate the appropriate status code" )
  
  status = PrependToEntryAttributeList( NULL, attribute );
  FAIL_IF_NULL( status, "a NULL list did not generate an abnormal status" )
  ASSERT_STRINGS_EQUAL( "empty argument", status->name, "a NULL list did not generate the appropriate status code" )
 
  status = PrependToEntryAttributeList( list, attribute );
  FAIL_IF_NOT_NULL( status, "a value could not be prepended to an empty list" )
  EntryAttribute * retrieved_attribute = BeginEntryAttributeList( list );
  FAIL_IF_NULL( retrieved_attribute, "the list's nodes were invalid" )
  if( retrieved_attribute != attribute )
    return "the attribute was not actually prepended to the list";
  
  list = BuildEntryAttributeList();
  FAIL_IF_NULL( list, "could not build a populated test list" ) 
  attribute = BuildEntryAttribute();
  FAIL_IF_NULL( list, "could not build a test attribute" )
  status = PrependToEntryAttributeList( list, attribute );
  FAIL_IF_NOT_NULL( status, "the attribute was not correctly prepended to a populated list" )
  retrieved_attribute = BeginEntryAttributeList( list );
  FAIL_IF_NULL( retrieved_attribute, "a populated list had its members removed" )
  if( retrieved_attribute != attribute )
    return "the attribute was not actually prepended to a full list";
  
  return NULL;
}
