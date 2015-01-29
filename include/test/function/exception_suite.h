#ifndef __STUMPLESS_TEST_FUNCTION_EXCEPTION_SUITE_H
#define __STUMPLESS_TEST_FUNCTION_EXCEPTION_SUITE_H

/**
 * @file
 * Functions for testing Exceptions and the related functions.
 */

/**
 * Tests the AddException function.
 *
 * @test A NULL argument must return NULL. A non-NULL Exception must return
 * the Exception added. The Exception must not be found before being added, but
 * after a call to AddException the Exception must be returned by a call to
 * FindExceptionByName.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestAdd
( void );

/**
 * Tests the DestroyException function.
 *
 * @test Calling the function with a NULL argument must not cause a failure.
 * Destroying an Exception that has not been added must not cause a failure.
 * Destroying an Exception that has been added must also remove the Exception
 * from the registered list.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestDestroy
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
TestFindByName
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
