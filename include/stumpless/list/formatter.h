#ifndef __STUMPLESS_LIST_FORMATTER_LIST_H
#define __STUMPLESS_LIST_FORMATTER_LIST_H

#include <stumpless/type.h>

FormatterList *
AddSeparatorToFormatterList
( FormatterList *, Formatter * );

FormatterList *
AppendFormatterLists
( FormatterList *, FormatterList * );

FormatterList *
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

unsigned
FormatterListSize
( const FormatterList * );

FormatterList *
NewFormatterList
( void );

FormatterList *
PrependToFormatterList
( FormatterList *, Formatter * );

#endif
