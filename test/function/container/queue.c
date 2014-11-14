#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test/function/container/queue.h"
#include "test/helper.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( Copy )
  TEST( Destructor )
  TEST( IsEmpty )
  TEST( New )
  TEST( Peek )
  TEST( Pop )
  TEST( Push )
  TEST( Size )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestCopy
( void )
{
  Queue *copy = CopyQueue( NULL );
  if( copy )
    return "a NULL Queue returned a non-NULL copy";

  Queue *original = BuildQueue();
  if( !original )
    return "could not create test Queue";

  copy = CopyQueue( original );
  if( !copy )
    return "could not copy the original Queue";

  if( PopFromQueue( copy ) != PopFromQueue( original ) )
    return "the original and the copy did not have the same first value";

  if( PopFromQueue( copy ) != PopFromQueue( original ) )
    return "the original and the copy did not have the same second value";

  if( PopFromQueue( copy ) != PopFromQueue( original ) )
    return "the original and the copy did not have the same third value";

  return NULL;
}

const char *
TestDestructor
( void )
{
  DestroyQueue( NULL );

  Queue *queue = BuildQueue();
  if( !queue )
    return "could not build a test Queue";

  DestroyQueue( queue );

  return NULL;
}

const char *
TestIsEmpty
( void )
{
  if( !QueueIsEmpty( NULL ) )
    return "a NULL Queue was not empty";

  Queue *queue = NewQueue();
  if( !queue )
    return "could not build a new Queue";

  if( !QueueIsEmpty( queue ) )
    return "a new Queue was not empty";

  queue = BuildQueue();
  if( !queue )
    return "could not build a test Queue";

  if( QueueIsEmpty( queue) )
    return "a populated Queue was claimed empty";

  return NULL;
}

const char *
TestNew
( void )
{
  Queue *queue = NewQueue();
  if( !queue )
    return "could not create a new Queue";

  return NULL;
}

const char *
TestPeek
( void )
{
  if( PeekAtQueue( NULL ) )
    return "a NULL Queue had a first value";

  Queue *queue = NewQueue();
  if( !queue )
    return "could not build a test Queue";

  if( PeekAtQueue( queue ) )
    return "an empty Queue had a first value";

  queue = BuildQueue();
  if( !queue )
    return "could not build a test Queue";

  const char *result = PeekAtQueue( queue );
  if( !result )
    return "a populated Queue did not have a first value";
  ASSERT_STRINGS_EQUAL( "first element", result, "the first value in the Queue was not returned" )

  return NULL;
}

const char *
TestPop
( void )
{
  if( PopFromQueue( NULL ) )
    return "a NULL Queue returned an element";

  Queue *queue = NewQueue();
  if( !queue )
    return "could not build a new Queue";
  if( PopFromQueue( queue ) )
    return "a new Queue returned an element";

  queue = BuildQueue();
  if( !queue )
    return "could not build a test Queue";
  const char *result = PopFromQueue( queue );
  if( !result )
    return "a populated Queue did not return a first element";
  ASSERT_STRINGS_EQUAL( "first element", result, "the first element returned was not the first in the Queue" )
  result = PopFromQueue( queue );
  if( !result )
    return "a populated Queue did not return a second element";
  ASSERT_STRINGS_EQUAL( "second element", result, "the second element returned was not the second in the Queue" )

  return NULL;
}

const char *
TestPush
( void )
{
  if( PushToQueue( NULL, NULL ) )
    return "a NULL Queue could be pushed to with a NULL element";

  Queue *queue = NewQueue();
  if( !queue )
    return "could not build a new Queue";

  if( PushToQueue( queue, NULL ) )
    return "a Queue accepted a NULL element push";

  const char *element = "first new element";
  if( PushToQueue( NULL, element ) )
    return "an element could be pushed to a new Queue";

  if( PushToQueue( queue, element ) != queue )
    return "a first element could not be properly pushed";
  if( PeekAtQueue( queue ) != element )
    return "an empty Queue did not have the correct element after a push";

  element = "second element";
  if( PushToQueue( queue, element ) != queue )
    return "a second element could not be properly pushed";
  if( PeekAtQueue( queue ) == element )
    return "a second element was pushed to the front instead of the back";

  return NULL;
}

const char *
TestSize
( void )
{
  if( QueueSize( NULL ) != 0 )
    return "a NULL Queue did not have a size of 0";

  Queue *queue = BuildQueue();
  if( !queue )
    return "could not build a test Queue";

  if( QueueSize( queue ) != 3 )
    return "a populated Queue did not return the correct size";

  return NULL;
}
