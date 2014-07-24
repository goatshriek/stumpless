#ifndef __STUMPLESS_PRIVATE_LOGGER_SENDER_H
#define __STUMPLESS_PRIVATE_LOGGER_SENDER_H

#include "private/type.h"

Status *
SendChar
( Logger *, char );

Status *
SendCharArray
( Logger *, const char *, unsigned);

Status *
SendDouble
( Logger *, double );

Status *
SendDoubleArray
( Logger *, const double *, unsigned );

Status *
SendFloat
( Logger *, float );

Status *
SendFloatArray
( Logger *, const float *, unsigned );

Status *
SendInt
( Logger *, int );

Status *
SendIntArray
( Logger *, const int *, unsigned );

Status *
SendLong
( Logger *, long );

Status *
SendLongArray
( Logger *, const long *, unsigned );

Status *
SendLongDouble
( Logger *, long double );

Status *
SendLongDoubleArray
( Logger *, const long double *, unsigned );

Status *
SendLongLong
( Logger *, long long );

Status *
SendLongLongArray
( Logger *, const long long *, unsigned );

Status *
SendShort
( Logger *, short );

Status *
SendShortArray
( Logger *, const short *, unsigned );

Status *
SendSignedChar
( Logger *, signed char );

Status *
SendSignedCharArray
( Logger *, const signed char *, unsigned );

Status *
SendString
( Logger *, const char * );

Status *
SendUnsignedChar
( Logger *, unsigned char );

Status *
SendUnsignedCharArray
( Logger *, const unsigned char *, unsigned );

Status *
SendUnsignedInt
( Logger *, unsigned int );

Status *
SendUnsignedIntArray
( Logger *, const unsigned int *, unsigned );

Status *
SendUnsignedLong
( Logger *, unsigned long );

Status *
SendUnsignedLongArray
( Logger *, const unsigned long *, unsigned );

Status *
SendUnsignedLongLong
( Logger *, unsigned long long );

Status *
SendUnsignedLongLongArray
( Logger *, const unsigned long long *, unsigned );

Status *
SendUnsignedShort
( Logger *, unsigned short );

Status *
SendUnsignedShortArray
( Logger *, const unsigned short *, unsigned );

Status *
SendValue
( Logger *, Value * );

Status *
SendVoid
( Logger *, const void *, unsigned, const char * );

#endif
