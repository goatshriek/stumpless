#ifndef __STUMPLESS_STREAM_HANDLER_H
#define __STUMPLESS_STREAM_HANDLER_H

#include <stdio.h>

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( BinaryOutputIntoStream )
( __STUMPLESS_NAME( Output ) *, FILE * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( CSVOutputIntoStream )
( __STUMPLESS_NAME( Output ) *, FILE * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( JSONOutputIntoStream )
( __STUMPLESS_NAME( Output ) *, FILE * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( RawStringOutputIntoStream )
( __STUMPLESS_NAME( Output ) *, FILE * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( TextOutputIntoStream )
( __STUMPLESS_NAME( Output ) *, FILE * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( XMLOutputIntoStream )
( __STUMPLESS_NAME( Output ) *, FILE * );

#endif
