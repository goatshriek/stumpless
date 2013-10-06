#ifndef STUMPLESS_PRIVATE_STREAM_OUTPUT_H
#define STUMPLESS_PRIVATE_STREAM_OUTPUT_H

#include <stdio.h>

#include "private/type.h"

Status *
BinaryFormattedOutputIntoStream
( FormattedOutput *, FILE * );

Status *
CSVFormattedOutputIntoStream
( FormattedOutput *, FILE * );

Status *
JSONFormattedOutputIntoStream
( FormattedOutput *, FILE * );

Status *
RawStringFormattedOutputIntoStream
( FormattedOutput *, FILE * );

Status *
TextFormattedOutputIntoStream
( FormattedOutput *, FILE * );

Status *
XMLFormattedOutputIntoStream
( FormattedOutput *, FILE * );

#endif
