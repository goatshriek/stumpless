#ifndef __STUMPLESS_PRIVATE_LIST_FORMATTER_H
#define __STUMPLESS_PRIVATE_LIST_FORMATTER_H

#include "private/type.h"

FormatterList *
AddSeparatorToFormatterList
( FormatterList *, Formatter * );

FormatterList *
AppendFormatterLists
( FormatterList *, FormatterList * );

FormatterList *
AppendToFormatterList
( FormatterList *, Formatter * );

FormatterListIterator *
BeginFormatterList
( FormatterList * );

FormatterListConstIterator *
CBeginFormatterList
( const FormatterList * );

FormatterListConstIterator *
CEndFormatterList
( const FormatterList * );

FormatterList *
CopyFormatterList
( const FormatterList * );

FormatterListConstReverseIterator *
CRBeginFormatterList
( const FormatterList * );

FormatterListConstReverseIterator *
CREndFormatterList
( const FormatterList * );

void
DestroyFormatterList
( FormatterList * );

FormatterListIterator *
EndFormatterList
( FormatterList * );

Status *
EntryThroughFormatterList
( const FormatterList *, const Entry * );

Formatter *
FormatterListBack
( const FormatterList * );

unsigned short
FormatterListContains
( const FormatterList *, const Formatter * );

Formatter *
FormatterListFront
( const FormatterList * );

unsigned short
FormatterListIsEmpty
( const FormatterList * );

unsigned
FormatterListSize
( const FormatterList * );

FormatterList *
NewFormatterList
();

FormatterList *
PrependToFormatterList
( FormatterList *, Formatter * );

FormatterListReverseIterator *
RBeginFormatterList
( FormatterList * );

FormatterListReverseIterator *
REndFormatterList
( FormatterList * );

#endif
