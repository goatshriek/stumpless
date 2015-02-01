#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "private/container/queue.h"
#include "test/function/container/queue_suite.h"
#include "test/helper.h"

int
main( void )
{
  unsigned failure_count = 0;
  const char *result;

  TEST( Contains )
  TEST( Copy )
  TEST( Destroy )
  TEST( IsEmpty )
  TEST( New )
  TEST( Peek )
  TEST( Pop )
  TEST( Push )
  TEST( Remove )
  TEST( Size )

  if( failure_count > 0 )
    return EXIT_FAILURE;
  else
    return EXIT_SUCCESS;
}

const char *
TestContains
( void )
{
  Queue *queue;
  void *value = "this value does not exist in the Queue";

  if( QueueContains( NULL, NULL ) )
    return "a NULL Queue did not return 0";

  if( QueueContains( NULL, value ) )
    return "a NULL Queue contained a value";

  queue = BuildQueue();
  if( !queue)
    return "could not build a test Queue";

  if( QueueContains( queue, NULL ) )
    return "a Queue contained a NULL value";

  if( QueueContains( queue, value ) )
    return "a Queue contained a value not in it";

  value = PeekAtQueue( queue );
  if( QueueContains( queue, value ) != 1 )
    return "a Queue did not contain a value pulled from it";

  PushToQueue( queue, value );
  if( QueueContains( queue, value ) != 2 )
    return "the correct count of a value existing twice was not returned";

  return NULL;
}

const char *
TestCopy
( void )
{
  Queue *copy, *original;

  copy = CopyQueue( NULL );
  if( copy )
    return "a NULL Queue returned a non-NULL copy";

  original = BuildQueue();
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
TestDestroy
( void )
{
  Queue *queue;

  DestroyQueue( NULL );

  queue = BuildQueue();
  if( !queue )
    return "could not build a test Queue";

  DestroyQueue( queue );

  return NULL;
}

const char *
TestIsEmpty
( void )
{
  Queue *queue;

  if( !QueueIsEmpty( NULL ) )
    return "a NULL Queue was not empty";

  queue = NewQueue();
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
  Queue *queue;

  queue = NewQueue();
  if( !queue )
    return "could not create a new Queue";

  return NULL;
}

const char *
TestPeek
( void )
{
  const char *result;
  Queue *queue;

  if( PeekAtQueue( NULL ) )
    return "a NULL Queue had a first value";

  queue = NewQueue();
  if( !queue )
    return "could not build a test Queue";

  if( PeekAtQueue( queue ) )
    return "an empty Queue had a first value";

  queue = BuildQueue();
  if( !queue )
    return "could not build a test Queue";

  result = PeekAtQueue( queue );
  if( !result )
    return "a populated Queue did not have a first value";
  ASSERT_STRINGS_EQUAL( "first element", result, "the first value in the Queue was not returned" )

  return NULL;
}

const char *
TestPop
( void )
{
  const char *result;
  Queue *queue;

  if( PopFromQueue( NULL ) )
    return "a NULL Queue returned an element";

  queue = NewQueue();
  if( !queue )
    return "could not build a new Queue";
  if( PopFromQueue( queue ) )
    return "a new Queue returned an element";

  queue = BuildQueue();
  if( !queue )
    return "could not build a test Queue";
  result = PopFromQueue( queue );
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
  const char *value;
  Queue *queue;

  if( PushToQueue( NULL, NULL ) )
    return "a NULL Queue could be pushed to with a NULL element";

  if( PushToQueue( NULL, "first new element" ) )
    return "an element could be pushed to a new Queue";

  queue = NewQueue();
  if( !queue )
    return "could not build a new Queue";

  if( PushToQueue( queue, NULL ) )
    return "a Queue accepted a NULL element push";

  if( PushToQueue( queue, "first new element" ) != queue )
    return "a first element could not be properly pushed";
  value = PeekAtQueue( queue );
  if( !value )
    return "could not get a value from the queue after the first push";
  ASSERT_STRINGS_EQUAL( "first new element", value, "an empty Queue did not have the correct element after a push" )

  if( PushToQueue( queue, "second element" ) != queue )
    return "a second element could not be properly pushed";
  value = PeekAtQueue( queue );
  if( !value )
    return "could not get a value from the queue after the second push";
  ASSERT_STRINGS_EQUAL( "first new element", value, "a second element was pushed to the front instead of the back" )

  return NULL;
}

const char *
TestRemove
( void )
{
  Queue *queue;
  void *value = "this value not in the Queue";

  if( RemoveFromQueue( NULL, NULL ) )
    return "a NULL Queue and value did not return NULL";

  if( RemoveFromQueue( NULL, value ) )
    return "a NULL Queue did not return NULL";

  queue = BuildQueue();
  if( !queue )
    return "could not build a test Queue";

  if( RemoveFromQueue( queue, NULL ) )
    return "a NULL value did not return NULL";

  if( RemoveFromQueue( queue, value ) )
    return "a non-existent value was removed from the Queue";

  value = PeekAtQueue( queue );
  if( RemoveFromQueue( queue, value ) != value )
    return "a value could not be removed from the Queue";

  value = PeekAtQueue( queue );
  PushToQueue( queue, value );

  if( RemoveFromQueue( queue, value ) != value )
    return "a value in the Queue twice could not be removed";

  if( !QueueContains( queue, value ) )
    return "both occurrences were removed from the Queue";

  if( PeekAtQueue( queue) == value )
    return "the first value was not the one removed from the Queue";

  DestroyQueue( queue );

  queue = NewQueue();

  PushToQueue( queue, value );
  if( RemoveFromQueue( queue, value ) != value )
    return "the only value in a Queue was not removed";
  if( !QueueIsEmpty( queue ) )
    return "removing the last element did not set the Queue to empty";


  return NULL;
}

const char *
TestSize
( void )
{
  Queue *queue;

  if( QueueSize( NULL ) != 0 )
    return "a NULL Queue did not have a size of 0";

  queue = BuildQueue();
  if( !queue )
    return "could not build a test Queue";

  if( QueueSize( queue ) != 3 )
    return "a populated Queue did not return the correct size";

  return NULL;
}
