#ifndef __STUMPLESS_TEST_FUNCTION_RECORD_H
#define __STUMPLESS_TEST_FUNCTION_RECORD_H

/**
 * @file
 * Functions for testing Records and the related functions.
 */

/**
 * Tests the alert Record.
 *
 * @test The alert Record must have the appropriate Event. The time must also be
 * a non-zero value.
 *
 * @todo check to see if the supplied message is present in the Record.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestAlertRecord
( void );

/**
 * Tests the critical Record.
 *
 * @test The critical Record must have the appropriate Event. The time must also
 * be a non-zero value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestCriticalRecord
( void );

/**
 * Tests the debug Record.
 *
 * @test The debug Record must have the appropriate Event. The time must also be
 * a non-zero value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestDebugRecord
( void );

/**
 * Tests the emergency Record.
 *
 * @test The emergency Record must have the appropriate Event. The time must
 * also be a non-zero value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestEmergencyRecord
( void );

/**
 * Tests the error Record.
 *
 * @test The error Record must have the appropriate Event. The time must also be
 * a non-zero value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestErrorRecord
( void );

/**
 * Tests the informational Record.
 *
 * @test The informational Record must have the appropriate Event. The time must
 * also be a non-zero value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestInformationalRecord
( void );

/**
 * Tests the MergeRecords function.
 *
 * @test The first Record is returned with a NULL second Record, and vice versa.
 * Two NULL Records result in a NULL return. If the primary Record's Event is
 * NULL, the Event of the secondary is used if non-NULL.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestMergeRecords
( void );

/**
 * Tests the notice Record.
 *
 * @test The notice Record must have the appropriate Event. The time must also
 * be a non-zero value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestNoticeRecord
( void );

/**
 * Tests the RecordForEvent function.
 *
 * @test The Record returned must have the supplied Event. The Record must also
 * have an attribute list if the Event had one.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestRecordForEvent
( void );

/**
 * Tests the RecordToString function.
 *
 * @test The provided string must be non-NULL. A NULL argument must return a
 * NULL description. 
 *
 * @todo Make sure the elements of the Record are present in the string.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestRecordToString
( void );

/**
 * Tests the warning Record.
 *
 * @test The warning Record must have the appropriate Event. The time must also
 * be a non-zero value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestWarningRecord
( void );

#endif
