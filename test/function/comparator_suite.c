#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/comparator.h"
#include "private/type.h"

#include "test/helper.h"

const char * test_destructor( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  RUN_TEST( destructor )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_destructor( void )
{
  DestroyComparator( NULL );

  Comparator *comparator = BuildComparator();
  if( !comparator )
    return "could not build test comparator";

  DestroyComparator( NULL );

  return NULL;
}
