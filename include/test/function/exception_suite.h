#ifndef __STUMPLESS_TEST_FUNCTION_EXCEPTION_SUITE_H
#define __STUMPLESS_TEST_FUNCTION_EXCEPTION_SUITE_H

/**
 * @file
 * Functions for testing Exceptions and the related functions.
 */


/**
 * Tests the DestroyException function.
 *
 * @test Calling the function with a NULL argument must not cause a failure.
 * Destroying an Exception must not cause a failure.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestDestroy
( void );

/**
 * Tests the ExceptionToString function.
 *
 * @test A NULL argument must return NULL. A valid Exception must return a
 * non-NULL string containing the name of the Exception.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestToString
( void );

#endif
