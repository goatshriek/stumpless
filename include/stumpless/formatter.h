#ifndef __STUMPLESS_FORMATTER_H
#define __STUMPLESS_FORMATTER_H

#include <stumpless/type.h>

Status *
AddFormatter
( Formatter * );

Status *
AppendHandlerToFormatter
( Formatter *, Handler * );

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
