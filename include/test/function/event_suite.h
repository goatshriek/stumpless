#ifndef __STUMPLESS_TEST_FUNCTION_EVENT_H
#define __STUMPLESS_TEST_FUNCTION_EVENT_H

/**
 * @file
 * Functions for testing Events and the related functions.
 */

/**
 * Tests the alert Event.
 *
 * @test The alert Event must have the appropriate name and that the
 * Level is set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestAlertEvent
( void );

/**
 * Tests the critical Event.
 *
 * @test The critical Event must have the appropriate name and that the
 * Level is set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestCriticalEvent
( void );

/**
 * Tests the debug Event.
 *
 * @test The debug Event must have the appropriate name and that the
 * Level is set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestDebugEvent
( void );

/**
 * Tests the emergency Event.
 *
 * @test The emergency Event must have the appropriate name and that
 * the Level is set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestEmergencyEvent
( void );

/**
 * Tests the error Event.
 *
 * @test The error Event must have the appropriate name and that the
 * Level is set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestErrorEvent
( void );

/**
 * Tests the EventToString function.
 *
 * @test The provided string must be non-NULL and contain the name of the Event.
 * A NULL argument must return a NULL description. 
 *
 * @todo Make sure the other elements of the Event are present in the string
 * in addition to the name.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestEventToString
( void );

/**
 * Tests the informational Event.
 *
 * @test The informational Event must have the appropriate name and
 * that the Level is set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestInformationalEvent
( void );

/**
 * Tests the notice Event.
 *
 * @test The notice Event must have the appropriate name and that the
 * Level is set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestNoticeEvent
( void );

/**
 * Tests the warning Event.
 *
 * @test The warning Event must have the appropriate name and that
 * the Level is set appropriately.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestWarningEvent
( void );

#endif
