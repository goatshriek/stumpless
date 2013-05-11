#ifndef STUMPLESS_FORMATTED_OUTPUT_H
#define STUMPLESS_FORMATTED_OUTPUT_H

#include <type.h>

StumplessStatusCode
StumplessFormattedOutputIntoString( char *, StumplessFormattedOutput * );

unsigned short
StumplessFormattedOutputIsEmpty( StumplessFormattedOutput * );

char *
StumplessFormattedOutputToString( StumplessFormattedOutput * );

#endif
