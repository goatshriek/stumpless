#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless/event.h>
#include <stumpless/record.h>

#include "test/function/record_suite.h"
#include "test/helper.h"
#include "test/type.h"

int
main
( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( AlertRecord )
  //TEST( CriticalRecord )
  //TEST( DebugRecord )
  //TEST( EmergencyRecord )
  //TEST( ErrorRecord )
  //TEST( InformationalRecord )
  //TEST( MergeRecords )
  //TEST( NoticeRecord )
  TEST( RecordForEvent )
  TEST( RecordToString )
  //TEST( WarningRecord )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestAlertRecord
( void )
{
  Record *record;

  record = NewAlertRecord( "test message" );
  if( !record )
    return "the alert record was not correctly created";
  if( record->event != FindEventByName( "alert" ) )
    return "the alert record did not have the correct event";

  return NULL;
}

const char *
TestMergeRecords
( void )
{
  Record *merged, *primary, *secondary;

  merged = MergeRecords( NULL, NULL );
  FAIL_IF_NOT_NULL( merged, "an record was created out of two null records" )

  primary = BuildEmptyRecord();
  FAIL_IF_NULL( primary, "an empty record could not be built" )
  primary->event = NULL;
  primary->attributes = BuildDictionaryOfRecordAttributes();
  FAIL_IF_NULL( primary->attributes, "the primary attribute list could not be built" )

  merged = MergeRecords( primary, NULL );
  if( merged != primary )
    return "a null secondary did not return the primary as the merged record";
  merged = MergeRecords( NULL, primary );
  if( merged != primary )
    return "a null primary did not return the secondary as the merged record";

  secondary = BuildEmptyRecord();
  FAIL_IF_NULL( secondary, "an empty record could not be built" )
  secondary->event = BuildEvent();
  FAIL_IF_NULL( secondary->event, "the test event could not be created" )
  secondary->attributes = NULL;

  merged = MergeRecords( primary, secondary );
  FAIL_IF_NULL( merged, "the two records could not be merged" )
  if( merged != primary )
    return "changes were not made to the primary";

  if( merged->event != secondary->event )
    return "the secondary event did not replace the NULL event of the primary";
  if( merged->attributes != primary->attributes )
    return "the primary attribute list did not replace the NULL list of the secondary";

  return NULL;
}

const char *
TestRecordForEvent
( void )
{
  Event *event;
  Record *record;

  event = BuildEvent();
  if( !event )
    return "could not build test Event";

  record = RecordForEvent( event );
  if( !record )
    return "the record could not be created";
  if( record->event != event )
    return "the record did not have the requested event";

  record = RecordForEvent( event );
  if( !record )
    return "a record could not be created for an event with attributes";
  if( record->event != event )
    return "the record did not have the requested event with attributes";
  if( !record->attributes )
    return "the record did not have an attribute list although the event did";

  event->attributes = NULL;
  record = RecordForEvent( event );
  if( !record )
    return "a record could not be created for an event without attributes";
  if( record->event != event )
    return "the record did not have the requested event without attributes";
  if( record->attributes )
    return "the record had an attribute list although the event did not";

  return NULL;
}

const char *
TestRecordToString
( void )
{
  char *message;
  Record *record;

  message = RecordToString( NULL );
  if( message )
    return "the message was not null for a null pointer";

  record = NewDebugRecord( "debug record message" );
  if( !record )
    return "could not build a test Record";
  message = RecordToString( record );
  if( !message )
    return "the message was null for a valid record pointer";

  return NULL;
}
