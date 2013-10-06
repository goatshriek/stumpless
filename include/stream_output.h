#ifndef __STUMPLESS_STREAM_OUTPUT_H
#define __STUMPLESS_STREAM_OUTPUT_H

#include <stdio.h>

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( BinaryFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) *, FILE * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( CSVFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) *, FILE * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( JSONFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) *, FILE * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( RawStringFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) *, FILE * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( TextFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) *, FILE * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( XMLFormattedOutputIntoStream )
( __STUMPLESS_NAME( FormattedOutput ) *, FILE * );

#endif
