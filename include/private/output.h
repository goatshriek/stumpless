#ifndef __STUMPLESS_PRIVATE_OUTPUT_H
#define __STUMPLESS_PRIVATE_OUTPUT_H

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

/**
 * Destroys the provided Output. A NULL Output is ignored.
 *
 * @param output the Output to be destroyed
 */
void
DestroyOutput
( Output *output );

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
