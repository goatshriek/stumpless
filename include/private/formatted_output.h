#ifndef STUMPLESS_PRIVATE_FORMATTED_OUTPUT_H
#define STUMPLESS_PRIVATE_FORMATTED_OUTPUT_H

#include "private/type.h"

unsigned short
BinaryFormattedOutputIsEmpty
( FormattedOutput * );

char *
BinaryFormattedOutputToString
( FormattedOutput * );

unsigned short
CSVFormattedOutputIsEmpty
( FormattedOutput * );

char *
CSVFormattedOutputToString
( FormattedOutput * );

unsigned short
FormattedOutputIsEmpty
( FormattedOutput * );

char *
FormattedOutputToString
( FormattedOutput * );

unsigned short
JSONFormattedOutputIsEmpty
( FormattedOutput * );

char *
JSONFormattedOutputToString
( FormattedOutput * );

unsigned short
RawStringFormattedOutputIsEmpty
( FormattedOutput * );

char *
RawStringFormattedOutputToString
( FormattedOutput * );

unsigned short
TextFormattedOutputIsEmpty
( FormattedOutput * );

char *
TextFormattedOutputToString
( FormattedOutput * );

unsigned short
XMLFormattedOutputIsEmpty
( FormattedOutput * );

char *
XMLFormattedOutputToString
( FormattedOutput * );

#endif
