#ifndef STUMPLESS_FORMATTED_OUTPUT_H
#define STUMPLESS_FORMATTED_OUTPUT_H

#include <type.h>

char *
StumplessBinaryFormattedOutputToString( StumplessFormattedOutput * );

char *
StumplessCSVFormattedOutputToString( StumplessFormattedOutput * );

unsigned short
StumplessFormattedOutputIsEmpty( StumplessFormattedOutput * );

char *
StumplessFormattedOutputToString( StumplessFormattedOutput * );

char *
StumplessJSONFormattedOutputToString( StumplessFormattedOutput * );

char *
StumplessTextFormattedOutputToString( StumplessFormattedOutput * );

char *
StumplessXMLFormattedOutputToString( StumplessFormattedOutput * );

#endif
