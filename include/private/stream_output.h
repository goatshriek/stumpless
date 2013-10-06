#ifndef STUMPLESS_PRIVATE_STREAM_OUTPUT_H
#define STUMPLESS_PRIVATE_STREAM_OUTPUT_H

#include <stdio.h>

#include "private/type.h"

Status *
TextOutputToStream
( FILE *, FormattedOutput * );

#endif
