#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_default_entries( void );
const char * test_entry_for_event( void );
const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_default_entries();
  if( result != NULL ){
    printf( "Default Entry Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_entry_for_event();
  if( result != NULL ){
    printf( "Entry For Event Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_to_string();
  if( result != NULL ){
    printf( "To String Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_default_entries( void )
{
  StumplessEntry * debug = StumplessGetDebugEntry();
  if( debug == NULL )
    return "the debug entry was not correctly created";
  if( debug->event == NULL )
    return "the debug entry did not have an event";
  if( debug->event->level == NULL )
    return "the debug entry's event did not have a level";
  if( debug->event->level->name == NULL )
    return "the debug entry's level did not have a name";
  if( strcmp( debug->event->level->name, "debug" ) != 0 )
    return "the debug entry's event did not have the proper level";
  
  StumplessEntry * error = StumplessGetErrorEntry();
  if( error == NULL )
    return "the error entry was not correctly created";
  if( error->event == NULL )
    return "the error entry did not have an event";
  if( error->event->level == NULL )
    return "the error entry's event did not have a level";
  if( error->event->level->name == NULL )
    return "the error entry's level did not have a name";
  if( strcmp( error->event->level->name, "error" ) != 0 )
    return "the error entry's event did not have the proper level";
  
  StumplessEntry * fatal = StumplessGetFatalEntry();
  if( fatal == NULL )
    return "the fatal entry was not correctly created";
  if( fatal->event == NULL )
    return "the fatal entry did not have an event";
  if( fatal->event->level == NULL )
    return "the fatal entry's event did not have a level";
  if( fatal->event->level->name == NULL )
    return "the fatal entry's level did not have a name";
  if( strcmp( fatal->event->level->name, "fatal" ) != 0 )
    return "the fatal entry's event did not have the proper level";
  
  StumplessEntry * info = StumplessGetInfoEntry();
  if( info == NULL )
    return "the info entry was not correctly created";
  if( info->event == NULL )
    return "the info entry did not have an event";
  if( info->event->level == NULL )
    return "the info entry's event did not have a level";
  if( info->event->level->name == NULL )
    return "the info entry's level did not have a name";
  if( strcmp( info->event->level->name, "info" ) != 0 )
    return "the info entry's event did not have the proper level";
  
  StumplessEntry * warning = StumplessGetWarningEntry();
  if( warning == NULL )
    return "the warning entry was not correctly created";
  if( warning->event == NULL )
    return "the warning entry did not have an event";
  if( warning->event->level == NULL )
    return "the warning entry's event did not have a level";
  if( warning->event->level->name == NULL )
    return "the warning entry's level did not have a name";
  if( strcmp( warning->event->level->name, "warning" ) != 0 )
    return "the warning entry's event did not have the proper level";
  
  return NULL;
}

const char *
test_entry_for_event( void )
{
  StumplessEvent * event = malloc( sizeof( StumplessEvent ) );
  if( event == NULL )
    return "memory allocation failure during testing";
  event->name = "testing event";
  event->level = StumplessGetDebugLevel();
  event->attribute_count = 0;
  
  StumplessEntry * entry = StumplessEntryForEvent( event );
  if( entry == NULL )
    return "the entry could not be created";
  if( entry->event != event )
    return "the entry did not have the requested event";
  
  return NULL;
}

const char *
test_to_string( void )
{
  StumplessEntry * entry = NULL;
  char * description = StumplessEntryToString( entry );
  if( description != NULL )
    return "the description was not null for a null pointer";
  
  entry = StumplessGetDebugEntry();
  description = StumplessEntryToString( entry );
  if( description == NULL )
    return "the description was null for a valid entry pointer";
  
  return NULL;
}
