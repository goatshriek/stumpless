#ifndef __STUMPLESS_PRIVATE_LOGGER_LOG_H
#define __STUMPLESS_PRIVATE_LOGGER_LOG_H

/** @file
 *  Functions used to log various elements directly to a Logger.
 */

#include "private/type.h"

/** Logs a single character to a Logger. The Event Uses the default settings of the Logger
 *  provided. This includes the record level and the message.
 *
 *  @param logger the Logger to use
 *  @param character the char to log
 *  @return a Status for the logging operation
 */
Status *
LogChar
( Logger *logger, char character );

Status *
LogCharArray
( Logger *, const char *, unsigned);

Status *
LogDouble
( Logger *, double );

Status *
LogDoubleArray
( Logger *, const double *, unsigned );

Status *
LogFloat
( Logger *, float );

Status *
LogFloatArray
( Logger *, const float *, unsigned );

Status *
LogInt
( Logger *, int );

Status *
LogIntArray
( Logger *, const int *, unsigned );

Status *
LogLoggerStatus
( Logger * );

Status *
LogLong
( Logger *, long );

Status *
LogLongArray
( Logger *, const long *, unsigned );

Status *
LogLongDouble
( Logger *, long double );

Status *
LogLongDoubleArray
( Logger *, const long double *, unsigned );

Status *
LogLongLong
( Logger *, long long );

Status *
LogLongLongArray
( Logger *, const long long *, unsigned );

/** Logs a Record to a Logger. Uses the default settings of the Logger provided.
 *
 *  @param logger the Logger to use
 *  @param record the Record to log
 *  @return a Status of the logging
 */
Status *
LogRecord
( Logger *logger, Record *record );

Status *
LogShort
( Logger *, short );

Status *
LogShortArray
( Logger *, const short *, unsigned );

Status *
LogSignedChar
( Logger *, signed char );

Status *
LogSignedCharArray
( Logger *, const signed char *, unsigned );

/**
 * Sends a single string to the provided Logger.
 *
 * @param logger the Logger to send the string to
 * @param str the string to log
 *
 * @return a Status describing the result of the function.
 */
Status *
LogString
( Logger *logger, const char *str );

Status *
LogStringArray
( Logger *, const char *, unsigned );

Status *
LogUnsignedChar
( Logger *, unsigned char );

Status *
LogUnsignedCharArray
( Logger *, const unsigned char *, unsigned );

Status *
LogUnsignedInt
( Logger *, unsigned int );

Status *
LogUnsignedIntArray
( Logger *, const unsigned int *, unsigned );

Status *
LogUnsignedLong
( Logger *, unsigned long );

Status *
LogUnsignedLongArray
( Logger *, const unsigned long *, unsigned );

Status *
LogUnsignedLongLong
( Logger *, unsigned long long );

Status *
LogUnsignedLongLongArray
( Logger *, const unsigned long long *, unsigned );

Status *
LogUnsignedShort
( Logger *, unsigned short );

Status *
LogUnsignedShortArray
( Logger *, const unsigned short *, unsigned );

Status *
LogVoid
( Logger *, const void *, unsigned );

#endif
