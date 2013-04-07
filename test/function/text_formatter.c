#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_event_formatter( void );
const char * test_level_formatter( void );
const char * test_value_formatter( void );

StumplessEvent * GetTestEvent( void );
StumplessEventAttribute ** GetTestEventAttributeList( void );
StumplessLevel * GetTestLevel( void );
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
  char * str;

  output = StumplessEventAsText( event );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  event = malloc( sizeof( StumplessEvent ) );
  if( event == NULL )
    return "the test event could not be created";
  
  event->name = NULL;
  event->level = NULL;
  event->attributes = NULL;
  event->attribute_count = 0;
  
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "" ) != 0 )
    return "an empty event did not generate an empy string";
  
  // creating the values to give the event for each test
  const char * name = "Test Event";
  StumplessLevel * level = GetTestLevel();
  if( level == NULL )
    return "the test level could not be created";
  StumplessEventAttribute ** list = GetTestEventAttributeList();
  if( list == NULL )
    return "the test event attribute list could not be created";
  
  event->name = name;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, name ) != 0 )
    return "an event with only a name was not formatted correctly";
  
  event->level = level;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "Test Event (Test Level: level 42)" ) != 0 )
    return "an event without a list was not formatted correctly";
  
  event->name = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "Test Level: level 42 event" ) != 0 )
    return "an event with only a level was not formatted correctly";
  
  event->attributes = list;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  // todo see if the formatting here can be fixed with a backslash
  if( strcmp( str, "Test Level: level 42 event: attr_0: val_0, attribute: val_1, attr_2" ) != 0 )
    return "an event without a name was not formatted correctly";
  
  event->name = name;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "Test Event (Test Level: level 42): attr_0: val_0, attribute: val_1, attr_2" ) != 0 )
    return "an event with all components was not formatted correctly";
  
  event->level = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "Test Event: attr_0: val_0, attribute: val_1, attr_2" ) != 0 )
    return "an event without a level was not formatted correctly";
  
  event->name = NULL;
  str = StumplessFormattedOutputToString( StumplessEventAsText( event ) );
  if( str == NULL )
    return "the output was not created";
  if( strcmp( str, "event: attr_0: val_0, attribute: val_1, attr_2" ) != 0 )
    return "an event with only a list was not formatted correctly";
  
  return NULL;
}

const char *
test_level_formatter( void )
{
  StumplessLevel * level = NULL;
  StumplessFormattedOutput * output;
  char * string_output;
  
  output = StumplessLevelAsText( level );
  if( output != NULL )
    return "the output was not null for a null pointer";
  
  level = malloc( sizeof( StumplessLevel ) );
  if( level == NULL )
    return "the test level could not be created";
  
  level->value = 30;
  level->name = NULL;
  output = StumplessLevelAsText( level );
  string_output = StumplessFormattedOutputToString( output );
  if( strcmp( string_output, "level 30" ) != 0 )
    return "the output was not correct for a level with no name";
  
  level->value = 67;
  level->name = "Test Level";
  output = StumplessLevelAsText( level );
  string_output = StumplessFormattedOutputToString( output );
  if( strcmp( string_output, "Test Level: level 67" ) != 0 )
    return "the output was not correct for a level with a name";
  
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

StumplessEventAttribute **
GetTestEventAttributeList( void )
{
  StumplessEventAttribute ** list;
  
  StumplessEventAttribute * attr_0 = malloc( sizeof( StumplessEventAttribute ));
  StumplessEventAttribute * attr_1 = malloc( sizeof( StumplessEventAttribute ));
  StumplessEventAttribute * attr_2 = malloc( sizeof( StumplessEventAttribute ));
  list = malloc( sizeof( StumplessEventAttribute * ) * 3 );
  if( attr_0 == NULL || attr_1 == NULL || attr_2 == NULL || list )
    return NULL;
  
  attr_0->name = "attr_0 name";
  attr_0->default_value = StumplessValueFromString( "val_0" );
  
  attr_1->name = NULL;
  attr_1->default_value = StumplessValueFromString( "val_1" );
  
  attr_2->name = "attr_2 name";
  attr_2->default_value = NULL;
  
  list[0] = attr_0;
  list[1] = attr_1;
  list[2] = attr_2;
  
  return list;
}

StumplessLevel *
GetTestLevel( void )
{
  StumplessLevel * level = malloc( sizeof( StumplessLevel ) );
  if( level == NULL )
    return NULL;
  
  level->value = 42;
  level->name = "Test Level";
  return level;
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
