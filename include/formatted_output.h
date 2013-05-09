#ifndef STUMPLESS_FORMATTED_OUTPUT_H
#define STUMPLESS_FORMATTED_OUTPUT_H

#include <type.h>

// todo need to go through and remove appending and prepending functions
// they do not fit with the encapsulation purpose of the formatted output
// and instead open up internal functionality that should be  hidden
// instead, operations needing these functions should act directly on the
// underlying ValueList structure

StumplessStatusCode
StumplessAppendFormattedOutputs( StumplessFormattedOutput *,
                                 StumplessFormattedOutput * );

StumplessStatusCode
StumplessAppendStringToFormattedOutput( StumplessFormattedOutput *,
                                        const char * );

StumplessStatusCode
StumplessAppendUnsignedIntToFormattedOutput( StumplessFormattedOutput *,
                                             unsigned );

StumplessStatusCode
StumplessAppendValueToFormattedOutput( StumplessFormattedOutput *,
                                       StumplessValue * );

StumplessStatusCode
StumplessFormattedOutputIntoString( char *, StumplessFormattedOutput * );

unsigned short
StumplessFormattedOutputIsEmpty( StumplessFormattedOutput * );

char *
StumplessFormattedOutputToString( StumplessFormattedOutput * );

StumplessStatusCode
StumplessPrependStringToFormattedOutput( StumplessFormattedOutput *,
                                         const char * );

StumplessStatusCode
StumplessPrependValueToFormattedOutput( StumplessFormattedOutput *,
                                        StumplessValue * );

#endif
