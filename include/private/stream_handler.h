#ifndef STUMPLESS_PRIVATE_STREAM_HANDLER_H
#define STUMPLESS_PRIVATE_STREAM_HANDLER_H

#include <stdio.h>

#include "private/type.h"

Status *
BinaryOutputIntoStream
( const Output *, FILE * );

Status *
CSVOutputIntoStream
( const Output *, FILE * );

Status *
HandleStreamOutput
( const Output *, Dictionary * );

Status *
JSONOutputIntoStream
( const Output *, FILE * );

Status *
RawStringOutputIntoStream
( const Output *, FILE * );

Status *
TextOutputIntoStream
( const Output *, FILE * );

Status *
XMLOutputIntoStream
( const Output *, FILE * );

#endif
