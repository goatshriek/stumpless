#ifndef __STUMPLESS_TEST_FUNCTION_LEVEL_H
#define __STUMPLESS_TEST_FUNCTION_LEVEL_H

/**
 * @file
 * Functions for testing Levels and the related functions.
 */

/**
 * Tests the alert Level.
 *
 * @test The alert Level must have the appropriate name and the numerical
 * values must be set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestAlertLevel
( void );

/**
 * Tests the critical Level.
 *
 * @test The critical Level must have the appropriate name and the numerical
 * values must be set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestCriticalLevel
( void );

/**
 * Tests the debug Level.
 *
 * @test The debug Level must have the appropriate name and the numerical
 * values must be set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestDebugLevel
( void );

/**
 * Tests the emergency Level.
 *
 * @test The emergency Level must have the appropriate name and the numerical
 * values must be set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestEmergencyLevel
( void );

/**
 * Tests the error Level.
 *
 * @test The error Level must have the appropriate name and the numerical
 * values must be set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestErrorLevel
( void );

/**
 * Tests the informational Level.
 *
 * @test The informational Level must have the appropriate name and the
 * numerical values must be set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestInformationalLevel
( void );

/**
 * Tests the LevelToString function.
 *
 * @test The provided string must be non-NULL and contain the name of the Level.
 * A NULL argument must return a NULL description. 
 *
 * @todo Make sure the other elements of the Level are present in the string
 * in addition to the name.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestLevelToString
( void );

/**
 * Tests the notice Level.
 *
 * @test The notice Level must have the appropriate name and the numerical
 * values must be set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestNoticeLevel
( void );

/**
 * Tests the warning Level.
 *
 * @test The warning Level must have the appropriate name and the numerical
 * values must be set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestWarningLevel
( void );

#endif
