#ifndef __STUMPLESS_PRIVATE_FORMATTER_H
#define __STUMPLESS_PRIVATE_FORMATTER_H

#include "private/type.h"

Status *
AddFormatter
( Formatter * );

void
DestroyFormatter
( Formatter * );

Formatter *
FindFormatterByName
( const char * );

Output *
FormatEntry
( const Formatter *, const Entry * );

void *
GetFormatterOption
( const Formatter *, const char * );

Status *
SetFormatterOption
( Formatter *, const char *, void * );

#endif
