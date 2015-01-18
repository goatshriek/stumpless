#ifndef __STUMPLESS_TEST_FUNCTION_EXCEPTION_SUITE_H
#define __STUMPLESS_TEST_FUNCTION_EXCEPTION_SUITE_H

/**
 * @file
 * Functions for testing Exceptions and the related functions.
 */

/**
 * Tests the AddException function.
 *
 * @test A non-NULL Exception must return the Exception added.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestAddException
( void );

/**
 * Tests the FindExceptionByName function.
 *
 * @test After an Exception is added, it must be returned by a call to the
 * function with the same name.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestFindExceptionByName
( void );

/**
 * Tests the RaiseException function.
 *
 * @test Calling the RaiseException function with the name of an added Exception
 * must return the correct Exception. The last Exception must be set after a
 * call to the function.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestRaise
( void );

/**
 * Tests the ExceptionToString function.
 *
 * @test A NULL argument must return NULL.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestToString
( void );

#endif
