#include <stdlib.h>
#include <stdio.h>

#include "private/exception/thrower.h"
#include "private/type.h"
#include "test/function/exception/thrower_suite.h"
#include "test/helper.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( ThrowMemoryAllocationException )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestThrowMemoryAllocationException
( void )
{
  Exception *e;

  e = ThrowMemoryAllocationException();
  if( !e )
    return "an Exception was not created";

  ASSERT_STRINGS_EQUAL( "memory allocation failure", e->name, "the correct Exception was not returned from initialization" )

  return NULL;
}
