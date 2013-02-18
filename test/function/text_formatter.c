#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_event_attribute_value_formatter( void );
const char * test_event_formatter( void );
const char * test_level_formatter( void );

StumplessEvent * GetTestEvent( void );
StumplessEventAttribute * GetTestEventAttributeUnsignedShort( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_event_attribute_value_formatter();
  if( result != NULL ){
    printf( "Event Attribute Value Formatter Test Failed: %s\n", result );
    failure_count++;
  }
  
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
test_event_attribute_value_formatter( void )
{
  StumplessEventAttribute * attribute = NULL;
  StumplessFormattedOutput * output;
  
  output = StumplessEventAttributeValueAsText( attribute );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  attribute = GetTestEventAttributeUnsignedShort();
  output = StumplessEventAttributeValueAsText( attribute );
  if( output == NULL )
    return "the output was null for a valid attribute pointer";
  if( output->format != STUMPLESS_TEXT )
    return "the output was not formatted as text";
  if( output->payload == NULL )
    return "the output did not have a payload";
  if( output->payload->str == NULL )
    return "the payload did not have any string output";
  if( strchr( output->payload->str, '3' ) == NULL )
    return "the output did not contain the default value";
  
  return NULL;
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

StumplessEvent *
GetTestEvent( void )
{
  // todo need to implement
  return NULL;
}

StumplessEventAttribute *
GetTestEventAttributeUnsignedShort( void )
{
  StumplessEventAttribute * attribute;
  
  attribute = malloc( sizeof( StumplessEventAttribute ) );
  if( attribute  == NULL )
    return NULL;
  
  attribute->default_value = malloc( sizeof( StumplessEventAttributeValue ) );
  if( attribute->default_value == NULL )
    return NULL;
  
  attribute->type = STUMPLESS_UNSIGNED_SHORT;
  attribute->default_value->u_s = 3;
  
  return attribute;
}
