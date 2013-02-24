#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless.h>

const char * test_destructor( void );
const char * test_value_from_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  result = test_destructor();
  if( result != NULL ){
    printf( "Destructor Test Failed: %s\n", result );
    failure_count++;
  }
  
  result = test_value_from_string();
  if( result != NULL ){
    printf( "Value From String Test Failed: %s\n", result );
    failure_count++;
  }
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_destructor( void )
{
  StumplessValue * value = StumplessValueFromString( "testing value" );
  if( value == NULL )
    return "the value could not be created";
  
  StumplessDestroyValue( value );
  
  return NULL;
}

const char *
test_value_from_string( void )
{
  StumplessValue * value = NULL;
  
  value = StumplessValueFromString( NULL );
  if( value != NULL )
    return "a null value was not returned for a null string";
  
  value = StumplessValueFromString( "test string 'n such" );
  if( value == NULL )
    return "a null value was returned for a non-null string";
  if( value->type != STUMPLESS_CHAR_POINTER )
    return "the value did not have a string type";
  if( value->data == NULL )
    return "the value did not have any data";
  if( strcmp( value->data->c_p, "test string 'n such" ) != 0 )
    return "the value string did not match the initial string";
  if( value->length != 20 )
    return "the length of the value did not match the length of the string + 1";
  
  return NULL;
}
