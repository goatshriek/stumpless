#ifndef STUMPLESS_PRIVATE_STREAM_HANDLER_H
#define STUMPLESS_PRIVATE_STREAM_HANDLER_H

#include <stdio.h>

#include "private/type.h"

Status *
BinaryOutputIntoStream
( Output *, FILE * );

Status *
CSVOutputIntoStream
( Output *, FILE * );

Status *
HandleStreamOutput
( Output *, Dictionary * );

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
