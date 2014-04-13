#ifndef __STUMPLESS_PRIVATE_FORMATTER_H
#define __STUMPLESS_PRIVATE_FORMATTER_H

#include "private/type.h"

Status *
AddFormatter
( Formatter * );

Status *
AppendHandlerToFormatter
( Formatter *, Handler * );

void
DestroyFormatter
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
