#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/record.h"
#include "private/level.h"
#include "private/type.h"

#include "helper.h"

const char * test_default_entries( void );
const char * test_for_event( void );
const char * test_merge_entries( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( default_entries )
  RUN_TEST( for_event )
  RUN_TEST( merge_entries )
  RUN_TEST( to_string )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_default_entries( void )
{
  Record * debug = GetDebugRecord();
  if( debug == NULL )
    return "the debug record was not correctly created";
  if( debug->event == NULL )
    return "the debug record did not have an event";
  if( debug->event->level == NULL )
    return "the debug record's event did not have a level";
  if( debug->event->level->name == NULL )
    return "the debug record's level did not have a name";
  if( strcmp( debug->event->level->name, "debug" ) != 0 )
    return "the debug record's event did not have the proper level";
  
  Record * error = GetErrorRecord();
  if( error == NULL )
    return "the error record was not correctly created";
  if( error->event == NULL )
    return "the error record did not have an event";
  if( error->event->level == NULL )
    return "the error record's event did not have a level";
  if( error->event->level->name == NULL )
    return "the error record's level did not have a name";
  if( strcmp( error->event->level->name, "error" ) != 0 )
    return "the error record's event did not have the proper level";
  
  Record * fatal = GetFatalRecord();
  if( fatal == NULL )
    return "the fatal record was not correctly created";
  if( fatal->event == NULL )
    return "the fatal record did not have an event";
  if( fatal->event->level == NULL )
    return "the fatal record's event did not have a level";
  if( fatal->event->level->name == NULL )
    return "the fatal record's level did not have a name";
  if( strcmp( fatal->event->level->name, "fatal" ) != 0 )
    return "the fatal record's event did not have the proper level";
  
  Record * info = GetInfoRecord();
  if( info == NULL )
    return "the info record was not correctly created";
  if( info->event == NULL )
    return "the info record did not have an event";
  if( info->event->level == NULL )
    return "the info record's event did not have a level";
  if( info->event->level->name == NULL )
    return "the info record's level did not have a name";
  if( strcmp( info->event->level->name, "info" ) != 0 )
    return "the info record's event did not have the proper level";
  
  Record * warning = GetWarningRecord();
  if( warning == NULL )
    return "the warning record was not correctly created";
  if( warning->event == NULL )
    return "the warning record did not have an event";
  if( warning->event->level == NULL )
    return "the warning record's event did not have a level";
  if( warning->event->level->name == NULL )
    return "the warning record's level did not have a name";
  if( strcmp( warning->event->level->name, "warning" ) != 0 )
    return "the warning record's event did not have the proper level";
  
  return NULL;
}

const char *
test_for_event
( void )
{
  Event * event = malloc( sizeof( Event ) );
  if( !event )
    return "memory allocation failure during testing";
  event->name = "testing event";
  event->level = GetDebugLevel();
  event->attributes = NULL;
  
  Record * record = RecordForEvent( event );
  if( !record )
    return "the record could not be created";
  if( record->event != event )
    return "the record did not have the requested event";
  
  event = BuildEvent();
  if( !event )
    return "could not build a test event";

  record = RecordForEvent( event );
  if( !record )
    return "an record could not be created for an event with attributes";
  if( record->event != event )
    return "the record did not have the requested event with attributes";
  if( !record->attributes )
    return "the record did not have an attribute list although the event did";

  return NULL;
}

const char *
test_merge_entries
( void )
{
  Record * primary = NULL;
  Record * secondary = NULL;
  Record * merged;
  
  merged = MergeRecords( primary, secondary );
  FAIL_IF_NOT_NULL( merged, "an record was created out of two null entries" )
  
  primary = BuildEmptyRecord();
  FAIL_IF_NULL( primary, "an empty record could not be built" )
  primary->message = "primary message";
  primary->event = NULL;
  primary->attributes = BuildRecordAttributeList();
  FAIL_IF_NULL( primary->attributes, "the primary attribute list could not be built" )
  
  merged = MergeRecords( primary, secondary );
  if( merged != primary )
    return "a null secondary did not return the primary as the merged record";
  merged = MergeRecords( secondary, primary );
  if( merged != primary )
    return "a null primary did not return the secondary as the merged record";
  
  secondary = BuildEmptyRecord();
  FAIL_IF_NULL( secondary, "an empty record could not be built" )
  secondary->message = "secondary message";
  secondary->event = BuildEvent();
  FAIL_IF_NULL( secondary->event, "the test event could not be created" )
  secondary->attributes = NULL;
  
  merged = MergeRecords( primary, secondary );
  FAIL_IF_NULL( merged, "the two entries could not be merged" )
  if( merged != primary )
    return "changes were not made to the primary";
  
  ASSERT_STRINGS_EQUAL( primary->message, merged->message, "the message was not inherited from the primary record" )
  if( merged->event != secondary->event )
    return "the secondary event did not replace the NULL event of the primary";
  if( merged->attributes != primary->attributes )
    return "the primary attribute list did not replace the NULL list of the secondary";
  
  return NULL;
}

const char *
test_to_string( void )
{
  Record * record = NULL;
  char * message = RecordToString( record );
  if( message != NULL )
    return "the message was not null for a null pointer";
  
  record = GetDebugRecord();
  message = RecordToString( record );
  if( message == NULL )
    return "the message was null for a valid record pointer";
  
  return NULL;
}
