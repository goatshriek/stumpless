#ifndef __STUMPLESS_OUTPUT_H
#define __STUMPLESS_OUTPUT_H

#include <public_name.h>
#include <type.h>

unsigned short
__STUMPLESS_NAME( BinaryOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * );

char *
__STUMPLESS_NAME( BinaryOutputToString )
( __STUMPLESS_NAME( Output ) * );

unsigned short
__STUMPLESS_NAME( CSVOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * );

char *
__STUMPLESS_NAME( CSVOutputToString )
( __STUMPLESS_NAME( Output ) * );

unsigned short
__STUMPLESS_NAME( OutputIsEmpty )
( __STUMPLESS_NAME( Output ) * );

char *
__STUMPLESS_NAME( OutputToString )
( __STUMPLESS_NAME( Output ) * );

unsigned short
__STUMPLESS_NAME( JSONOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * );

char *
__STUMPLESS_NAME( JSONOutputToString )
( __STUMPLESS_NAME( Output ) * );

unsigned short
__STUMPLESS_NAME( RawStringOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * );

char *
__STUMPLESS_NAME( RawStringOutputToString )
( __STUMPLESS_NAME( Output ) * );

unsigned short
__STUMPLESS_NAME( TextOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * );

char *
__STUMPLESS_NAME( TextOutputToString )
( __STUMPLESS_NAME( Output ) * );

unsigned short
__STUMPLESS_NAME( XMLOutputIsEmpty )
( __STUMPLESS_NAME( Output ) * );

char *
__STUMPLESS_NAME( XMLOutputToString )
( __STUMPLESS_NAME( Output ) * );

#endif
