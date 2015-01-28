#ifndef __STUMPLESS_LOGGER_LOG_H
#define __STUMPLESS_LOGGER_LOG_H

/** @file
 *  Functions used to log various elements directly to a Logger.
 */

#include <stumpless/type.h>

/** Logs a single character to a Logger. The Event Uses the default settings of the Logger
 *  provided. This includes the record level and the message.
 *
 *  @param logger the Logger to use
 *  @param character the char to log
 *
 *  @return logger
 */
Logger *
LogChar
( Logger *logger, char character );

Logger *
LogCharArray
( Logger *, const char *, unsigned);

Logger *
LogDouble
( Logger *, double );

Logger *
LogDoubleArray
( Logger *, const double *, unsigned );

Logger *
LogFloat
( Logger *, float );

Logger *
LogFloatArray
( Logger *, const float *, unsigned );

Logger *
LogInt
( Logger *, int );

Logger *
LogIntArray
( Logger *, const int *, unsigned );

Logger *
LogLoggerException
( Logger * );

Logger *
LogLong
( Logger *, long );

Logger *
LogLongArray
( Logger *, const long *, unsigned );

Logger *
LogLongDouble
( Logger *, long double );

Logger *
LogLongDoubleArray
( Logger *, const long double *, unsigned );

Logger *
LogLongLong
( Logger *, long long );

Logger *
LogLongLongArray
( Logger *, const long long *, unsigned );

/** Logs a Record to a Logger. Uses the default settings of the Logger provided.
 *
 *  @param logger the Logger to use
 *  @param record the Record to log
 *  @return a Exception of the logging
 */
Logger *
LogRecord
( Logger *logger, Record *record );

Logger *
LogShort
( Logger *, short );

Logger *
LogShortArray
( Logger *, const short *, unsigned );

Logger *
LogSignedChar
( Logger *, signed char );

Logger *
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
Logger *
LogString
( Logger *logger, const char *str );

Logger *
LogStringArray
( Logger *, const char *, unsigned );

Logger *
LogUnsignedChar
( Logger *, unsigned char );

Logger *
LogUnsignedCharArray
( Logger *, const unsigned char *, unsigned );

Logger *
LogUnsignedInt
( Logger *, unsigned int );

Logger *
LogUnsignedIntArray
( Logger *, const unsigned int *, unsigned );

Logger *
LogUnsignedLong
( Logger *, unsigned long );

Logger *
LogUnsignedLongArray
( Logger *, const unsigned long *, unsigned );

Logger *
LogUnsignedLongLong
( Logger *, unsigned long long );

Logger *
LogUnsignedLongLongArray
( Logger *, const unsigned long long *, unsigned );

Logger *
LogUnsignedShort
( Logger *, unsigned short );

Logger *
LogUnsignedShortArray
( Logger *, const unsigned short *, unsigned );

Logger *
LogVoid
( Logger *, const void *, unsigned );

#endif
