#include <stdlib.h>
#include <string.h>

#include "private/container/queue.h"
#include "private/type.h"
#include "static/container/queue.h"

Queue *
CopyQueue
( const Queue *original )
{
  Queue *copy;

  if( !original )
    return NULL;

  copy = malloc( sizeof( Queue ) );
  if( !copy )
    return NULL;

  copy->elements = malloc( sizeof( void * ) * original->capacity );
  if( !copy->elements )
    return NULL;

  memcpy( copy->elements, original->elements, original->capacity );

  copy->back = original->back;
  copy->capacity = original->capacity;
  copy->front = original->front;

  return copy;
}

void
DestroyQueue
( Queue *queue )
{
  if( !queue )
    return;

  free( queue->elements );
  free( queue );

  return;
}

Queue *
NewQueue
( void )
{
  Queue *queue = malloc( sizeof( Queue ) );
  if( !queue )
    return NULL;

  queue->front = queue->back = 0;
  queue->capacity = 100;

  queue->elements = malloc( sizeof( void * ) * queue->capacity );
  if( !queue->elements )
    return NULL;

  return queue;
}

void *
PeekAtQueue
( const Queue *queue )
{
  if( QueueIsEmpty( queue ) )
    return NULL;
  else
    return queue->elements[ queue->front ];
}

void *
PopFromQueue
( Queue *queue )
{
  void *value;

  if( !queue || !queue->elements || queue->front == queue->back )
    return NULL;

  value = queue->elements[ queue->front ];

  queue->front = (queue->front + 1) % queue->capacity;

  return value;
}

Queue *
PushToQueue
( Queue *queue, void *element )
{
  unsigned new_back;

  if( !queue || !element )
    return NULL;

  new_back = (queue->back + 1) % queue->capacity;
  if( new_back == queue->front )
    return NULL;

  queue->elements[ queue->back ] = element;
  queue->back = new_back;

  return queue;
}

size_t
QueueContains
( const Queue *queue, const void *value )
{
  size_t count = 0, current;

  if( QueueIsEmpty( queue ) )
    return 0;

  current = queue->front;
  while( current != queue->back ){
    if( queue->elements[current] == value )
      count++;

    current = ( current + 1 ) % queue->capacity;
  }

  return count;
}

unsigned short
QueueIsEmpty
( const Queue *queue )
{
  return queue == NULL || queue->front == queue->back;
}

size_t
QueueSize
( const Queue *queue )
{
  if( !queue )
    return 0;
  if( queue->back >= queue->front )
    return queue->back - queue->front;
  else
    return queue->back + queue->capacity - queue->front;
}

void *
RemoveFromQueue
( Queue *queue, void *value )
{
  size_t current;

  if( QueueIsEmpty( queue ) )
    return NULL;

  current = queue->front;
  while( current != queue->back ){
    if( queue->elements[current] == value ){
      queue->back = queue->back == 0 ? queue->capacity - 1 : queue->back - 1;

      while( current != queue->back ){
        queue->elements[current] = queue->elements[( current + 1 ) % queue->capacity];
        current = (current + 1 ) % queue->capacity;
      }

      return value;
    }

    current = ( current + 1 ) % queue->capacity;
  }

  return NULL;
}
