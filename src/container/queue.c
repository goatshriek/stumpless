#include <stdlib.h>
#include <string.h>

#include "private/container/queue.h"
#include "private/type.h"
#include "static/container/queue.h"

Queue *
CopyQueue
( const Queue *original )
{
  if( !original )
    return NULL;

  Queue *copy = malloc( sizeof( Queue ) );
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
  if( !queue || !queue->elements || queue->front == queue->back )
    return NULL;

  return queue->elements[ queue->front ];
}

void *
PopFromQueue
( Queue *queue )
{
  if( !queue || !queue->elements || queue->front == queue->back )
    return NULL;

  void *value = queue->elements[ queue->front ];

  queue->front = (queue->front + 1) % queue->capacity;

  return value;
}

Queue *
PushToQueue
( Queue *queue, void *element )
{
  if( !queue || !element || !queue->elements )
    return NULL;

  unsigned new_back = (queue->back + 1) % queue->capacity;
  if( new_back == queue->front )
    return NULL;

  queue->elements[ queue->back ] = element;
  queue->back = new_back;

  return queue;
}

unsigned short
QueueIsEmpty
( const Queue *queue )
{
  return queue == NULL || queue->front == queue->back;
}

unsigned
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
