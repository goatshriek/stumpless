#include <stdlib.h>
#include <stdio.h>

#include "private/status.h"
#include "private/type.h"

#include "helper.h"

const char * test_to_string( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char * result;
  
  RUN_TEST( to_string )
  
  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_to_string( void )
{
  if( StatusToString( STUMPLESS_SUCCESS ) == NULL )
    return "success code was not properly converted";
  
  if( StatusToString( STUMPLESS_FAILURE ) == NULL )
    return "failure code was not properly converted";
  
  if( StatusToString( STUMPLESS_FILE_FAILURE ) == NULL )
    return "file failure code was not properly converted";
  
  if( StatusToString( STUMPLESS_FILE_READ_FAILURE ) == NULL )
    return "file read failure code was not properly converted";
  
  if( StatusToString( STUMPLESS_FILE_WRITE_FAILURE ) == NULL )
    return "file write failure code was not properly converted";
  
  if( StatusToString( STUMPLESS_FILE_OPEN_FAILURE ) == NULL )
    return "file open failure code was not properly converted";
  
  if( StatusToString( STUMPLESS_FILE_CLOSE_FAILURE ) == NULL )
    return "file close failure code was not properly converted";
  
  if( StatusToString( STUMPLESS_INCORRECT_FILE_SIGNATURE ) == NULL )
    return "incorrect file signature code was not properly converted";
  
  if( StatusToString( STUMPLESS_MEMORY_ALLOCATION_FAILURE ) == NULL )
    return "memory allocation failure code was not properly converted";
  
  if( StatusToString( STUMPLESS_PARSE_FAILURE ) == NULL )
    return "parsing failure code was not properly converted";
  
  return NULL;
}
