#ifndef __STUMPLESS_STREAM_HANDLER_H
#define __STUMPLESS_STREAM_HANDLER_H

#include <stdio.h>

#include <stumpless/type.h>

Status *
BinaryOutputIntoStream
( Output *, FILE * );

Status *
CSVOutputIntoStream
( Output *, FILE * );

Status *
JSONOutputIntoStream
( Output *, FILE * );

Status *
RawStringOutputIntoStream
( Output *, FILE * );

Status *
TextOutputIntoStream
( Output *, FILE * );

Status *
XMLOutputIntoStream
( Output *, FILE * );

#endif
