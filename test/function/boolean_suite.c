#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/boolean.h"
#include "private/type.h"

#include "test/function/boolean_suite.h"
#include "test/helper.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( ToString )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestToString
( void )
{
  Boolean *boolean;
  char *str;

  boolean = BuildBoolean();
  if( !boolean )
    return "could not build the test boolean";

  str = BooleanToString( NULL );
  if( str )
    return "the string was not null for a null pointer";

  str = BooleanToString( boolean );
  if( !str )
    return "the string was null for a non-null boolean";
  if( strcmp( str, "true" ) != 0 )
    return "the test boolean value did not yield the correct string output";

  return NULL;
}
