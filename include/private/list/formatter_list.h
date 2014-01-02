#ifndef STUMPLESS_PRIVATE_FORMATTER_LIST_H
#define STUMPLESS_PRIVATE_FORMATTER_LIST_H

#include "private/type.h"

Status *
AppendToFormatterList
( FormatterList *, Formatter * );

FormatterList *
CopyFormatterList
( FormatterList * );

void
DestroyFormatterList
( FormatterList * );

Status *
EntryThroughFormatterList
( FormatterList *, Entry * );

unsigned short
FormatterListContains
( FormatterList *, Formatter * );

unsigned short
FormatterListIsEmpty
( FormatterList * );

FormatterList *
NewFormatterList
( void );

Status *
PrependToFormatterList
( FormatterList *, Formatter * );

#endif
