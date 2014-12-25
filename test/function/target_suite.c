#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stumpless/target.h>

#include "test/function/target_suite.h"
#include "test/helper.h"
#include "test/type.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( Copy )
  TEST( Destroy )
  TEST( LogRecord )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestCopy
( void )
{
  if( CopyTarget( NULL ) )
    return "a NULL Target returned a non-NULL Target";

  Target *target = BuildTarget();
  if( !target )
    return "could not build a test Target";

  Target *copy = CopyTarget( target );
  if( !copy )
    return "a valid Target did not return a copy";

  if( copy == target )
    return "the copy was not a genuine copy";

  if( copy->formatter != target->formatter )
    return "the copy did not have the same Formatter as the original";
  if( copy->handler != target->handler )
    return "the copy did not have the same Handler as the original";

  return NULL;
}

const char *
TestDestroy
( void )
{
  DestroyTarget( NULL );

  Target *target = BuildTarget();
  if( !target )
    return "could not build a test Target";

  DestroyTarget( target );

  return NULL;
}

const char *
TestLogRecord
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
