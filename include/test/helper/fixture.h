#ifndef __STUMPLESS_TEST_HELPER_FIXTURE_H
#define __STUMPLESS_TEST_HELPER_FIXTURE_H

/**
 * @file
 * Functions to register data with the global TestLog.
 */

#include "test/type.h"

/**
 * Registers the Adapter called and the Record adapted, and then returns NULL.
 *
 * @param adapter the Adapter to register
 * @param record the Record to register
 *
 * @return NULL
 */
Record *
BadAdaptFunction
( const Adapter *adapter, Record *record ); 

/**
 * Registers the Formatter and Record provided, and then returns NULL.
 *
 * @param formatter the Formatter to register
 * @param record the Record to register
 *
 * @return NULL;
 */
Output *
BadFormatFunction
( const Formatter *formatter, const Record *record );

/**
 * Registers the Formatter and Output provided, and then returns NULL.
 *
 * @param handler the Handler to register
 * @param output the Output to register
 *
 * @return a failure Status 
 */
Status *
BadHandleFunction
( const Handler *handler, const Output *output );

/**
 * Registers the Adapter called and the Record adapted.
 *
 * @param adapter the Adapter to register
 * @param record the Record to register
 *
 * @return record
 */
Record *
TestAdaptFunction
( const Adapter *adapter, Record *record );

/**
 * Registers the Formatter called, the Record formatted, and the Output created,
 * and then formats the Record using the TextFormatter functions.
 *
 * @param formatter the Formatter to register
 * @param record the Record to register
 * 
 * @return the record formatted as text Output
 */
Output *
TestFormatFunction
( const Formatter *formatter, const Record *record );

/**
 * Registers the Handler called, the Output handled, and the message logged. The
 * message is derived by calling the OutputToString function on the output.
 *
 * @param handler the Handler to register
 * @param output the Output to register
 *
 * @return a Status with the result
 */
Status *
TestHandleFunction
( const Handler *handler, const Output *output ); 

#endif
