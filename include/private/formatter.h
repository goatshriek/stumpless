#ifndef __STUMPLESS_PRIVATE_FORMATTER_H
#define __STUMPLESS_PRIVATE_FORMATTER_H

#include "private/type.h"

Exception *
AddFormatter
( Formatter * );

void
DestroyFormatter
( Formatter * );

Formatter *
FindFormatterByName
( const char * );

Output *
FormatRecord
( const Formatter *, const Record * );

void *
GetFormatterOption
( const Formatter *, const char * );

Exception *
SetFormatterOption
( Formatter *, const char *, void * );

#endif
