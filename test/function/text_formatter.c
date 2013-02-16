#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_event_formatter( void );
const char * test_level_formatter( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_event_formatter();
  if( result != NULL ){
    printf( "Event Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_level_formatter();
  if( result != NULL ){
    printf( "Level Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_event_formatter( void )
{
  StumplessEvent * event = NULL;
  StumplessFormattedOutput * output;

  output = StumplessEventAsText( event );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  event = StumplessGetDebugEvent();
  output = StumplessEventAsText( event );
  if( output == NULL )
    return "the output was null for a valid event pointer";
  
  if( output->format != STUMPLESS_TEXT )
    return "the output did not have a text format";
  
  if( output->payload == NULL )
    return "the output payload was not properly created";
  
  if( output->payload->str == NULL )
    return "the payload did not have an output string";
  
  return NULL;
}

const char *
test_level_formatter( void )
{
  StumplessLevel * level = NULL;
  StumplessFormattedOutput * output;
  
  output = StumplessLevelAsText( level );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  level = StumplessGetInfoLevel();
  output = StumplessLevelAsText( level );
  if( output == NULL )
    return "the output was null for a valid level pointer";
  
  if( output->format != STUMPLESS_TEXT )
    return "the output did not have a text format";
  
  if( output->payload == NULL )
    return "the output payload was not properly created";
  
  if( output->payload->str == NULL )
    return "the payload did not have an output string";
  
  level->name = NULL;
  output = StumplessLevelAsText( level );
  if( output == NULL || output->payload == NULL
      || output->payload->str == NULL )
    return "the output was not properly created for a level with no name";
  if( strchr( output->payload->str, ':' ) != NULL )
    return "a colon was detected in the output for a level without a name";
  
  return NULL;
}
