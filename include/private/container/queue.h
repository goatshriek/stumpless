#ifndef __STUMPLESS_PRIVATE_CONTAINER_QUEUE_H
#define __STUMPLESS_PRIVATE_CONTAINER_QUEUE_H

/**
 * @file
 * Functions for working with a simple queue data structure.
 */

#include "private/type.h"

/**
 * Creates a copy of the given Queue. If the supplied Queue is NULL, then a
 * NULL is returned.
 *
 * @param queue the Queue to copy
 *
 * @return the copy of the original Queue, or NULL on failure.
 */
Queue *
CopyQueue
( Queue *queue );

/**
 * Destroys a Queue
 *
 * @param queue the Queue to destroy
 */
void
DestroyQueue
( Queue *queue );

/**
 * Creates a new Queue.
 *
 * @return the new Queue, or NULL on failure
 */
Queue *
NewQueue
( void );

/**
 * Gets the front element of the Queue, but does not remove it.
 *
 * @param queue the Queue to get the front element of
 *
 * @return the front element of the Queue
 */
void *
PeekAtQueue
( const Queue *queue );

/**
 * Removes the front element from the Queue and returns it.
 *
 * @param queue the Queue to pull the front value from
 *
 * @return the front value of the Queue, or NULL on failure
 */
void *
PopFromQueue
( Queue *queue );

/**
 * Puts an element at the back of the Queue. If the Queue or value passed are
 * NULL then no action is taken and NULL is returned.
 *
 * @param queue the Queue to push to
 * @param value the value to push to the Queue
 *
 * @return the Queue pushed to, or NULL on failure
 */
Queue *
PushToQueue
( Queue *queue, void *value );

/**
 * Checks a Queue to see if it's empty.
 *
 * @param queue the Queue to check
 *
 * @return a positive value if the Queue is empty, 0 otherwise
 */
unsigned short
QueueIsEmpty
( const Queue *queue );

/**
 * Gets the number of elements in a Queue. If a NULL Queue is provided then the
 * size will be 0.
 *
 * @param queue the Queue to measure
 *
 * @return the number of elements in the Queue
 */
unsigned
QueueSize
( const Queue *queue);

#endif
