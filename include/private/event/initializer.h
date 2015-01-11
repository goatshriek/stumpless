#ifndef __STUMPLESS_PRIVATE_EVENT_INITIALIZER_H
#define __STUMPLESS_PRIVATE_EVENT_INITIALIZER_H

/** @file
 *  Functions to initialize default Events.
 */

#include "private/type.h"

/**
 * @private
 * Initializes the Event of the given name. Initialization consists of the
 * creation of the Event struct and its addition to the list of Events. Only
 * Events provided by the library can be initialized this way; custom Events
 * need to be manualy created and added to the list of events. If the Event
 * has already been Initialized, it will not be recreated.
 *
 * @param name the name of the Event to initialize
 * @return a Exception of the initialization operation
 */
Exception *
InitializeEventByName
( const char *name );

/**
 * @private
 * Creates the Event for alert Level messages
 *
 * @return the Event for alert Level messages
 */
Event *
NewAlertEvent
( void );

/**
 * @private
 * Creates the Event for logging a char.
 *
 * @return the Event for logging a char
 */
Event *
NewCharEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of chars.
 *
 * @return the Event for logging an array of chars
 */
Event *
NewCharArrayEvent
( void );

/**
 * @private
 * Creates the Event for critical Level messages
 *
 * @return the Event for critical Level messages
 */
Event *
NewCriticalEvent
( void );

/**
 * @private
 * Creates the Event for debug Level messages
 *
 * @return the Event for debug Level messages
 */
Event *
NewDebugEvent
( void );

/**
 * @private
 * Creates the Event for logging a double.
 *
 * @return the Event for logging a double
 */
Event *
NewDoubleEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of doubles.
 *
 * @return the Event for logging an array of doubles
 */
Event *
NewDoubleArrayEvent
( void );

/**
 * @private
 * Creates the Event for emergency Level messages
 *
 * @return the Event for emergency Level messages
 */
Event *
NewEmergencyEvent
( void );

/**
 * @private
 * Creates the Event for error Level messages
 *
 * @return the Event for error Level messages
 */
Event *
NewErrorEvent
( void );

/**
 * @private
 * Creates the Event for logging a float.
 *
 * @return the Event for logging a float
 */
Event *
NewFloatEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of floats.
 *
 * @return the Event for logging an array of floats
 */
Event *
NewFloatArrayEvent
( void );

/**
 * @private
 * Creates the Event for informational Level messages.
 *
 * @return the Event for informational Level messages
 */
Event *
NewInformationalEvent
( void );

/**
 * @private
 * Creates the Event for logging an int.
 *
 * @return the Event for logging an int
 */
Event *
NewIntEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of ints.
 *
 * @return the Event for logging an array of ints
 */
Event *
NewIntArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging a long.
 *
 * @return the Event for logging a long
 */
Event *
NewLongEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of longs.
 *
 * @return the Event for logging an array of longs
 */
Event *
NewLongArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging a long double.
 *
 * @return the Event for logging a long double
 */
Event *
NewLongDoubleEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of long doubles.
 *
 * @return the Event for logging an array of long doubles
 */
Event *
NewLongDoubleArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging a long long.
 *
 * @return the Event for logging a long long
 */
Event *
NewLongLongEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of long longs.
 *
 * @return the Event for logging an array of long longs
 */
Event *
NewLongLongArrayEvent
( void );

/**
 * @private
 * Creates the Event for notice Level messages.
 *
 * @return the Event for notice Level messages
 */
Event *
NewNoticeEvent
( void );

/**
 * @private
 * Creates the Event for logging a short.
 *
 * @return the Event for logging a short
 */
Event *
NewShortEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of shorts.
 *
 * @return the Event for logging an array of shorts
 */
Event *
NewShortArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging a signed char.
 *
 * @return the Event for logging a signed char
 */
Event *
NewSignedCharEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of signed chars.
 *
 * @return the Event for logging an array of signed chars
 */
Event *
NewSignedCharArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging a string.
 *
 * @return the Event for logging a string
 */
Event *
NewStringEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of strings.
 *
 * @return the Event for logging an array of strings
 */
Event *
NewStringArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging an unsigned char.
 *
 * @return the Event for logging an unsigned char
 */
Event *
NewUnsignedCharEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of unsigned chars.
 *
 * @return the Event for logging an array of unsigned chars
 */
Event *
NewUnsignedCharArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging an unsigned int.
 *
 * @return the Event for logging an unsigned int
 */
Event *
NewUnsignedIntEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of unsigned ints.
 *
 * @return the Event for logging an array of unsigned ints
 */
Event *
NewUnsignedIntArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging an unsigned long.
 *
 * @return the Event for logging an unsigned long
 */
Event *
NewUnsignedLongEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of unsigned longs.
 *
 * @return the Event for logging an array of unsigned longs
 */
Event *
NewUnsignedLongArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging an unsigned long long.
 *
 * @return the Event for logging an unsigned long long
 */
Event *
NewUnsignedLongLongEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of unsigned long longs.
 *
 * @return the Event for logging an array of unsigned long longs
 */
Event *
NewUnsignedLongLongArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging an unsigned short.
 *
 * @return the Event for logging an unsigned short
 */
Event *
NewUnsignedShortEvent
( void );

/**
 * @private
 * Creates the Event for logging an array of unsigned shorts.
 *
 * @return the Event for logging an array of unsigned shorts
 */
Event *
NewUnsignedShortArrayEvent
( void );

/**
 * @private
 * Creates the Event for logging a void type.
 *
 * @return the Event for logging a void type
 */
Event *
NewVoidEvent
( void );

/**
 * @private
 * Creates the Event for warning Level messages.
 *
 * @return the Event for warning Level messages
 */
Event *
NewWarningEvent
( void );

#endif
