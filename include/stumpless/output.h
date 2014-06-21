#ifndef __STUMPLESS_OUTPUT_H
#define __STUMPLESS_OUTPUT_H

#include <stumpless/type.h>

unsigned short
BinaryOutputIsEmpty
( Output * );

char *
BinaryOutputToString
( Output * );

unsigned short
CSVOutputIsEmpty
( Output * );

char *
CSVOutputToString
( Output * );

unsigned short
OutputIsEmpty
( Output * );

char *
OutputToString
( Output * );

unsigned short
JSONOutputIsEmpty
( Output * );

char *
JSONOutputToString
( Output * );

unsigned short
RawStringOutputIsEmpty
( Output * );

char *
RawStringOutputToString
( Output * );

unsigned short
TextOutputIsEmpty
( Output * );

char *
TextOutputToString
( Output * );

unsigned short
XMLOutputIsEmpty
( Output * );

char *
XMLOutputToString
( Output * );

#endif
