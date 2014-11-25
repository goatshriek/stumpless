#ifndef __STUMPLESS_TEST_FUNCTION_TARGET_H
#define __STUMPLESS_TEST_FUNCTION_TARGET_H

/**
 * @file
 * Functions for testing Targets and related functions.
 */

/**
 * Tests the CopyTarget function.
 *
 * @test A NULL Target must return a NULL copy. The copy must not be equal to
 * the Target. The Formatter and Handler in the Target must be equal to those in
 * the original Target.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestCopy
( void );

/**
 * Tests the DestroyTarget function.
 *
 * @test A NULL Target must not cause an error. A valid Target must not cause an
 * error.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestDestroy
( void );

/**
 * Tests the LogToTarget function.
 *
 * @test A NULL Target, Record, or both will return an empty argument Status. A
 * valid Target and Status must return a NULL Status.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestLogRecord
( void );

#endif
