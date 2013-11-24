#ifndef STUMPLESS_PRIVATE_FORMATTER_H
#define STUMPLESS_PRIVATE_FORMATTER_H

#include "private/type.h"

Status *
AddFormatter
( Formatter * );

Formatter *
FindFormatterByName
( const char * );

void *
GetFormatterOption
( const Formatter *, const char * );

Status *
SetFormatterOption
( Formatter *, const char *, void * );

#endif
