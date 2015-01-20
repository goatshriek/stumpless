#ifndef __STUMPLESS_TEST_FUNCTION_EXCEPTION_THROWER_H
#define __STUMPLESS_TEST_FUNCTION_EXCEPTION_THROWER_H

/**
 * @file
 * Tests for the Exception throwing functions.
 */

/**
 * Tests the ThrowMemoryAllocationException function.
 *
 * @test The function must return a non-NULL Exception with a name equal to
 * "memory allocation failure".
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestThrowMemoryAllocationException
( void );

#endif
