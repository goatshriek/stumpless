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
 *  @return a Exception for the logging operation
 */
Exception *
LogChar
( Logger *logger, char character );

Exception *
LogCharArray
( Logger *, const char *, unsigned);

Exception *
LogDouble
( Logger *, double );

Exception *
LogDoubleArray
( Logger *, const double *, unsigned );

Exception *
LogFloat
( Logger *, float );

Exception *
LogFloatArray
( Logger *, const float *, unsigned );

Exception *
LogInt
( Logger *, int );

Exception *
LogIntArray
( Logger *, const int *, unsigned );

Exception *
LogLoggerException
( Logger * );

Exception *
LogLong
( Logger *, long );

Exception *
LogLongArray
( Logger *, const long *, unsigned );

Exception *
LogLongDouble
( Logger *, long double );

Exception *
LogLongDoubleArray
( Logger *, const long double *, unsigned );

Exception *
LogLongLong
( Logger *, long long );

Exception *
LogLongLongArray
( Logger *, const long long *, unsigned );

/** Logs a Record to a Logger. Uses the default settings of the Logger provided.
 *
 *  @param logger the Logger to use
 *  @param record the Record to log
 *  @return a Exception of the logging
 */
Exception *
LogRecord
( Logger *logger, Record *record );

Exception *
LogShort
( Logger *, short );

Exception *
LogShortArray
( Logger *, const short *, unsigned );

Exception *
LogSignedChar
( Logger *, signed char );

Exception *
LogSignedCharArray
( Logger *, const signed char *, unsigned );

/**
 * Sends a single string to the provided Logger.
 *
 * @param logger the Logger to send the string to
 * @param str the string to log
 *
 * @return a Exception describing the result of the function.
 */
Exception *
LogString
( Logger *logger, const char *str );

Exception *
LogStringArray
( Logger *, const char *, unsigned );

Exception *
LogUnsignedChar
( Logger *, unsigned char );

Exception *
LogUnsignedCharArray
( Logger *, const unsigned char *, unsigned );

Exception *
LogUnsignedInt
( Logger *, unsigned int );

Exception *
LogUnsignedIntArray
( Logger *, const unsigned int *, unsigned );

Exception *
LogUnsignedLong
( Logger *, unsigned long );

Exception *
LogUnsignedLongArray
( Logger *, const unsigned long *, unsigned );

Exception *
LogUnsignedLongLong
( Logger *, unsigned long long );

Exception *
LogUnsignedLongLongArray
( Logger *, const unsigned long long *, unsigned );

Exception *
LogUnsignedShort
( Logger *, unsigned short );

Exception *
LogUnsignedShortArray
( Logger *, const unsigned short *, unsigned );

Exception *
LogVoid
( Logger *, const void *, unsigned );

#endif
