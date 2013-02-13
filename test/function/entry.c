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
  if( strcmp( debug->event->level, "debug" ) != 0 )
    return "the debug entry's event did not have the proper level";
  
  StumplessEntry * error = StumplessGetErrorEntry();
  if( error == NULL )
    return "the error entry was not correctly created";
  if( error->event == NULL )
    return "the error entry did not have an event";
  if( error->event->level == NULL )
    return "the error entry's event did not have a level";
  if( strcmp( error->event->level, "error" ) != 0 )
    return "the error entry's event did not have the proper level";
  
  StumplessEntry * fatal = StumplessGetFatalEntry();
  if( fatal == NULL )
    return "the fatal entry was not correctly created";
  if( fatal->event == NULL )
    return "the fatal entry did not have an event";
  if( fatal->event->level == NULL )
    return "the fatal entry's event did not have a level";
  if( strcmp( fatal->event->level, "fatal" ) != 0 )
    return "the fatal entry's event did not have the proper level";
  
  StumplessEntry * info = StumplessGetInfoEntry();
  if( info == NULL )
    return "the info entry was not correctly created";
  if( info->event == NULL )
    return "the info entry did not have an event";
  if( info->event->level == NULL )
    return "the info entry's event did not have a level";
  if( strcmp( info->event->level, "info" ) != 0 )
    return "the info entry's event did not have the proper level";
  
  StumplessEntry * warning = StumplessGetWarningEntry();
  if( warning == NULL )
    return "the warning entry was not correctly created";
  if( warning->event == NULL )
    return "the warning entry did not have an event";
  if( warning->event->level == NULL )
    return "the warning entry's event did not have a level";
  if( strcmp( warning->event->level, "warning" ) != 0 )
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
  return NULL;
}
