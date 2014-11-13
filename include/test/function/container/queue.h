#ifndef __STUMPLESS_TEST_FUNCTION_CONTAINER_QUEUE_H
#define __STUMPLESS_TEST_FUNCTION_CONTAINER_QUEUE_H

/**
 * @file
 * Tests for the Queue data structure.
 */

#include "test/type.h"

/**
 * Tests the CopyQueue function.
 *
 * @test a NULL Queue must return NULL. The copied Queue must point at the same
 * elements as the original. The copied Queue must be a different value than the
 * original.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestCopy
( void );

/**
 * Tests the DestroyQueue function.
 *
 * @test a NULL Queue must not cause an error. A populated Queue must not cause
 * an error.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestDestroy
( void );

/**
 * Tests the QueueIsEmpty function.
 *
 * @test a NULL Queue must return a positive value. A Queue with no elements
 * must return a positive value. A filled Queue must return 0.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestIsEmpty
( void );

/**
 * Tests the NewQueue function.
 *
 * @test Calling the constructor must return a non-NULL value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestNew
( void );

/**
 * Tests the PeekAtQueue function.
 *
 * @test Peeking at a NULL Queue must return NULL. Peeking at an empty Queue
 * must return NULL. Peeking at a filled Queue must return the correct value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestPeek
( void );

/**
 * Tests the PopFromQueue function.
 *
 * @test Popping from a NULL Queue must return NULL. Popping from an empty Queue
 * must return NULL. Popping from a filled Queue must return the correct value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestPop
( void );

/**
 * Tests the PushToQueue function.
 *
 * @test Pushing to a NULL Queue must return NULL. Pushing to an empty Queue
 * must result in the element being the only one in the Queue. Pushing to a
 * populated Queue must put the element at the back, and leave the front element
 * unchanged.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestPush
( void );

/**
 * Tests the QueueSize function.
 *
 * @test A NULL Queue must return 0. A populated Queue must return an accurate
 * count of the values.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestSize
( void );

#endif
