#ifndef __STUMPLESS_STREAM_OUTPUT_H
#define __STUMPLESS_STREAM_OUTPUT_H

#include <stdio.h>

#include <public_name.h>
#include <type.h>

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
