#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_to_string( void );

StumplessBoolean * GetTestBoolean( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
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
test_to_string( void )
{
  StumplessBoolean * boolean = GetTestBoolean();
  if( boolean == NULL )
    return "the test boolean value could not be created";
  
  char * str = StumplessBooleanToString( boolean );
  if( strcmp( str, "true" ) != 0 )
    return "the test boolean value did not yield the correct string output";
  
  return NULL;
}

StumplessBoolean *
GetTestBoolean( void )
{
  StumplessBoolean * boolean = malloc( sizeof( StumplessBoolean ) );
  if( boolean == NULL )
    return NULL;
  
  boolean->format = malloc( sizeof( StumplessBooleanFormat ) );
  if( boolean->format == NULL )
    return NULL;
  
  boolean->value = 1;
  boolean->format->true_message = "true";
  boolean->format->false_message = "false";
  
  return boolean;
}
