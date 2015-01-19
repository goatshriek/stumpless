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
 * Tests the GetLastFailureException function.
 *
 * @test Calling the RaiseException function with a failure Exception must
 * return the correct Exception. The result of the GetLastFailureException
 * function must match the last failure Exception raised.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestGetLastFailure
( void );

/**
 * Tests the GetLastInformationalException function.
 *
 * @test Calling the RaiseException function with an informational Exception
 * must return the correct Exception. The result of the
 * GetLastInformationalException function must match the last informational
 * Exception raised.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestGetLastInformational
( void );

/**
 * Tests the GetLastWarningException function.
 *
 * @test Calling the RaiseException function with a warning Exception must
 * return the correct Exception. The result of the GetLastWarningException
 * function must match the last warning Exception raised.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestGetLastWarning
( void );

/**
 * Tests the RaiseException function.
 *
 * @test Calling the RaiseException function with a NULL argument must return
 * NULL. Calling the RaiseException function with the name of an Exception that
 * has not been added must return NULL. Calling the RaiseException function with
 * the name of an added Exception must return the correct Exception..
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestRaise
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
