#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless/target.h>

#include "private/type.h"

#include "test/helper.h"

const char * test_log( void );

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  RUN_TEST( log )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
test_log
( void )
{
  Status *status = LogToTarget( NULL, NULL );
  if( !status )
    return "two null arguments did not raise an abnormal status";
  ASSERT_STRINGS_EQUAL( status->name, "empty argument", "an empty argument status was not returned for two empty arguments" )

  Target *target = BuildTarget();
  if( !target )
    return "could not build a test target";

  status = LogToTarget( target, NULL );
  if( !status )
    return "a null record did not raise an abnormal status";
  ASSERT_STRINGS_EQUAL( status->name, "empty argument", "an empty argument status was not returned for an empty record" )

  Record *record = BuildRecord();
  if( !record )
    return "could not build a test record";

  status = LogToTarget( NULL, record );
  if( !status )
    return "a null target did not raise an abnormal status";
  ASSERT_STRINGS_EQUAL( status->name, "empty argument", "an empty argument status was not returned for an empty target" )

  status = LogToTarget( target, record );
  if( status )
    return "an abnormal status was returned";

  return NULL;
}
