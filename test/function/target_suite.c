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
  Target *copy, *target;

  if( CopyTarget( NULL ) )
    return "a NULL Target returned a non-NULL Target";

  target = BuildTarget();
  if( !target )
    return "could not build a test Target";

  copy = CopyTarget( target );
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
  Target *target;

  DestroyTarget( NULL );

  target = BuildTarget();
  if( !target )
    return "could not build a test Target";

  DestroyTarget( target );

  return NULL;
}

const char *
TestLogRecord
( void )
{
  Exception *e;
  Record *record;
  Target *target;

  e = LogToTarget( NULL, NULL );
  if( e )
    return "two null arguments generated an Exception";

  target = BuildTarget();
  if( !target )
    return "could not build a test target";

  e = LogToTarget( target, NULL );
  if( e )
    return "a NULL Record generated an Exception";

  record = BuildRecord();
  if( !record )
    return "could not build a test record";

  e = LogToTarget( NULL, record );
  if( e )
    return "a NULL Target generated an Exception";

  e = LogToTarget( target, record );
  if( e )
    return "an abnormal e was returned";

  return NULL;
}
