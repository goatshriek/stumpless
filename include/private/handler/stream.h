#ifndef __STUMPLESS_PRIVATE_HANDLER_STREAM_H
#define __STUMPLESS_PRIVATE_HANDLER_STREAM_H

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
