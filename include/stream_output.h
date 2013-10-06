#ifndef __STUMPLESS_STREAM_OUTPUT_H
#define __STUMPLESS_STREAM_OUTPUT_H

#include <stdio.h>

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( TextOutputToStream )
( FILE *, __STUMPLESS_NAME( FormattedOutput ) * );

#endif
