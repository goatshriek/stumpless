#ifndef __STUMPLESS_PRIVATE_HANDLER_STREAM_H
#define __STUMPLESS_PRIVATE_HANDLER_STREAM_H

#include <stdio.h>

#include "private/type.h"

// todo change stream argument to be first in IntoStream functions

FILE *
BinaryOutputIntoStream
( FILE *, const Output * );

FILE *
CSVOutputIntoStream
( FILE *, const Output * );

const Handler *
HandleStreamOutput
( const Handler *handler, const Output * );

FILE *
JSONOutputIntoStream
( FILE *, const Output * );

FILE *
RawStringOutputIntoStream
( FILE *, const Output * );

FILE *
TextOutputIntoStream
( FILE *, const Output * );

FILE *
XMLOutputIntoStream
( FILE *, const Output * );

#endif
