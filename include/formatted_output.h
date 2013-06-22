#ifndef STUMPLESS_FORMATTED_OUTPUT_H
#define STUMPLESS_FORMATTED_OUTPUT_H

#include <type.h>

unsigned short
StumplessBinaryFormattedOutputIsEmpty( StumplessFormattedOutput * );

char *
StumplessBinaryFormattedOutputToString( StumplessFormattedOutput * );

unsigned short
StumplessCSVFormattedOutputIsEmpty( StumplessFormattedOutput * );

char *
StumplessCSVFormattedOutputToString( StumplessFormattedOutput * );

unsigned short
StumplessFormattedOutputIsEmpty( StumplessFormattedOutput * );

char *
StumplessFormattedOutputToString( StumplessFormattedOutput * );

unsigned short
StumplessJSONFormattedOutputIsEmpty( StumplessFormattedOutput * );

char *
StumplessJSONFormattedOutputToString( StumplessFormattedOutput * );

unsigned short
StumplessRawStringFormattedOutputIsEmpty( StumplessFormattedOutput * );

char *
StumplessRawStringFormattedOutputToString( StumplessFormattedOutput * );

unsigned short
StumplessTextFormattedOutputIsEmpty( StumplessFormattedOutput * );

char *
StumplessTextFormattedOutputToString( StumplessFormattedOutput * );

unsigned short
StumplessXMLFormattedOutputIsEmpty( StumplessFormattedOutput * );

char *
StumplessXMLFormattedOutputToString( StumplessFormattedOutput * );

#endif
