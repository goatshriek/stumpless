#ifndef __STUMPLESS_FORMATTED_OUTPUT_H
#define __STUMPLESS_FORMATTED_OUTPUT_H

#include <public_name.h>
#include <type.h>

unsigned short
__STUMPLESS_NAME( BinaryFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * );

char *
__STUMPLESS_NAME( BinaryFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * );

unsigned short
__STUMPLESS_NAME( CSVFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * );

char *
__STUMPLESS_NAME( CSVFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * );

unsigned short
__STUMPLESS_NAME( FormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * );

char *
__STUMPLESS_NAME( FormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * );

unsigned short
__STUMPLESS_NAME( JSONFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * );

char *
__STUMPLESS_NAME( JSONFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * );

unsigned short
__STUMPLESS_NAME( RawStringFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * );

char *
__STUMPLESS_NAME( RawStringFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * );

unsigned short
__STUMPLESS_NAME( TextFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * );

char *
__STUMPLESS_NAME( TextFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * );

unsigned short
__STUMPLESS_NAME( XMLFormattedOutputIsEmpty )
( __STUMPLESS_NAME( FormattedOutput ) * );

char *
__STUMPLESS_NAME( XMLFormattedOutputToString )
( __STUMPLESS_NAME( FormattedOutput ) * );

#endif
