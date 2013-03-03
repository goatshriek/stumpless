#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_event_formatter( void );
const char * test_level_formatter( void );
const char * test_value_formatter( void );

StumplessEvent * GetTestEvent( void );
StumplessValue * GetTestValueUnsignedShort( void );

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
  
  result = test_value_formatter();
  if( result != NULL ){
    printf( "Event Attribute Value Formatter Test Failed: %s\n", result );
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
  
  level->name = NULL;
  output = StumplessLevelAsText( level );
  
  return NULL;
}

const char *
test_value_formatter( void )
{
  StumplessValue * value = NULL;
  StumplessFormattedOutput * output;
  
  output = StumplessValueAsText( value );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  value = GetTestValueUnsignedShort();
  output = StumplessValueAsText( value );
  if( output == NULL )
    return "the output was null for a valid value";
  if( output->format != STUMPLESS_TEXT )
    return "the output did not have the correct type";
  
  return NULL;
}

StumplessEvent *
GetTestEvent( void )
{
  // todo need to implement
  return NULL;
}

StumplessValue *
GetTestValueUnsignedShort( void )
{
  StumplessValue * value;
  
  value = malloc( sizeof( StumplessValue ) );
  if( value == NULL )
    return NULL;
  
  value->type = STUMPLESS_UNSIGNED_SHORT;
  value->data = malloc( sizeof( StumplessValueData ) );
  if( value->data == NULL )
    return NULL;
  
  value->data->u_s = 3;
  value->length = 0;
  
  return value;
}
