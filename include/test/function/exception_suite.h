#ifndef __STUMPLESS_TEST_FUNCTION_EXCEPTION_SUITE_H
#define __STUMPLESS_TEST_FUNCTION_EXCEPTION_SUITE_H

/**
 * @file
 * Functions for testing Exceptions and the related functions.
 */


/**
 * Tests the CatchException function.
 *
 * @test Calling the function with NULL must not cause any problems. Calling
 * the function on an Exception not thrown by the library must not cause any
 * problems.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestCatch
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


/**
 * Tests the GetUncaughtException function.
 *
 * @test If no Exception has been thrown yet, NULL must be returned. After an
 * Exception has been thrown, it must be returned. After a second Exception has
 * been thrown, the first must still be returned. After the first Exception has
 * been caught, the second Exception must be returned. If an Exception is caught
 * by its handler, it must not be returned by this function. If all Exceptions
 * have been caught, NULL must be returned.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestGetUncaught
( void );


#endif
