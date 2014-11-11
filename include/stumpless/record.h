#ifndef __STUMPLESS_RECORD_H
#define __STUMPLESS_RECORD_H

/**
 * @file
 * Functions for creating and working with Records
 */

#include <stumpless/type.h>

/**
 * Merges the attributes of the two records together into the primary Record,
 * and returns the primary Record. If one of the Records is set to NULL, then
 * the non-NULL Record is returned.
 *
 * @param primary the Record to merge into
 * @param secondary the Record to merge with primary
 *
 * @return the Record the attributes have been merged into
 */
Record *
MergeRecords
( Record *primary, Record *secondary );

/**
 * Creates a Record of alert level with the provided message. The Record will
 * have no attributes set. The time for the record will be set to the time of
 * the call.
 *
 * @param message the message of the Record
 *
 * @return a Record with the specified message and level
 */
Record *
NewAlertRecord
( const char *message );

/**
 * Creates a Record of critical level with the provided message. The Record will
 * have no attributes set. The time for the record will be set to the time of
 * the call.
 *
 * @param message the message of the Record
 *
 * @return a Record with the specified message and level
 */
Record *
NewCriticalRecord
( const char *message );

/**
 * Creates a Record of debug level with the provided message. The Record will
 * have no attributes set. The time for the record will be set to the time of
 * the call.
 *
 * @param message the message of the Record
 *
 * @return a Record with the specified message and level
 */
Record *
NewDebugRecord
( const char *message );

/**
 * Creates a Record of emergency level with the provided message. The Record
 * will have no attributes set. The time for the record will be set to the time
 * of the call.
 *
 * @param message the message of the Record
 *
 * @return a Record with the specified message and level
 */
Record *
NewEmergencyRecord
( const char *message );

/**
 * Creates a Record of error level with the provided message. The Record will
 * have no attributes set. The time for the record will be set to the time of
 * the call.
 *
 * @param message the message of the Record
 *
 * @return a Record with the specified message and level
 */
Record *
NewErrorRecord
( const char *message );

/**
 * Creates a Record of informational level with the provided message. The Record
 * will have no attributes set. The time for the record will be set to the time
 * of the call.
 *
 * @param message the message of the Record
 *
 * @return a Record with the specified message and level
 */
Record *
NewInformationalRecord
( const char *message );

/**
 * Creates a Record of notice level with the provided message. The Record will
 * have no attributes set. The time for the record will be set to the time of
 * the call.
 *
 * @param message the message of the Record
 *
 * @return a Record with the specified message and level
 */
Record *
NewNoticeRecord
( const char *message );

/**
 * Creates a Record of warning level with the provided message. The Record will
 * have no attributes set. The time for the record will be set to the time of
 * the call.
 *
 * @param message the message of the Record
 *
 * @return a Record with the specified message and level
 */
Record *
NewWarningRecord
( const char *message );

/**
 * Creates a Record with the specified Event. The time is also set to the
 * current time (if the time header is available).
 *
 * @param event the Event to assign to the new Record
 *
 * @return a new Record with the specified Event
 */
Record *
RecordForEvent
( Event *event );

/**
 * Creates a string that represents the specified Record. The format of the
 * string is identical to that of the TextFormatter format for a Record.
 *
 * @param record the record to get a string representation of
 *
 * @return a pointer to a NULL-terminated string containing the representation
 */
char *
RecordToString
( const Record *record );

/**
 * Sets the RecordAttribute with the provided name to the given value. If the
 * RecoardAttribute does not yet exist for the supplied Record, it is created
 * and set to the supplied value.
 *
 * @param record the Record to set the attribute of
 * @param name the name of the RecordAttribute
 * @param value the Value to set the attribute to
 *
 * @return the Record provided, or NULL on failure
 */
Record *
SetRecordAttribute
( Record *record, const char *name, Value *value );

#endif
