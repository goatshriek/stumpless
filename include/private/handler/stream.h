#ifndef __STUMPLESS_PRIVATE_HANDLER_STREAM_H
#define __STUMPLESS_PRIVATE_HANDLER_STREAM_H

#include <stdio.h>

#include "private/type.h"

Exception *
BinaryOutputIntoStream
( const Output *, FILE * );

Exception *
CSVOutputIntoStream
( const Output *, FILE * );

Exception *
HandleStreamOutput
( const Handler *handler, const Output * );

Exception *
JSONOutputIntoStream
( const Output *, FILE * );

Exception *
RawStringOutputIntoStream
( const Output *, FILE * );

Exception *
TextOutputIntoStream
( const Output *, FILE * );

Exception *
XMLOutputIntoStream
( const Output *, FILE * );

#endif
