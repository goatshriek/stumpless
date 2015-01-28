#ifndef __STUMPLESS_PRIVATE_HANDLER_STREAM_H
#define __STUMPLESS_PRIVATE_HANDLER_STREAM_H

#include <stdio.h>

#include "private/type.h"

// todo change stream argument to be first in IntoStream functions

const Output *
BinaryOutputIntoStream
( const Output *, FILE * );

const Output *
CSVOutputIntoStream
( const Output *, FILE * );

const Handler *
HandleStreamOutput
( const Handler *handler, const Output * );

const Output *
JSONOutputIntoStream
( const Output *, FILE * );

const Output *
RawStringOutputIntoStream
( const Output *, FILE * );

const Output *
TextOutputIntoStream
( const Output *, FILE * );

const Output *
XMLOutputIntoStream
( const Output *, FILE * );

#endif
