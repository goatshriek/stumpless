#ifndef STUMPLESS_PRIVATE_OUTPUT_H
#define STUMPLESS_PRIVATE_OUTPUT_H

#include "private/type.h"

unsigned short
BinaryOutputIsEmpty
( const Output * );

char *
BinaryOutputToString
( const Output * );

unsigned short
CSVOutputIsEmpty
( const Output * );

char *
CSVOutputToString
( const Output * );

unsigned short
OutputIsEmpty
( const Output * );

char *
OutputToString
( const Output * );

unsigned short
JSONOutputIsEmpty
( const Output * );

char *
JSONOutputToString
( const Output * );

unsigned short
RawStringOutputIsEmpty
( const Output * );

char *
RawStringOutputToString
( const Output * );

unsigned short
TextOutputIsEmpty
( const Output * );

char *
TextOutputToString
( const Output * );

unsigned short
XMLOutputIsEmpty
( const Output * );

char *
XMLOutputToString
( const Output * );

#endif
