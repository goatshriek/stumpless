#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_FORMATTER_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_FORMATTER_H

#include "private/type.h"

FormatterListReverseIterator *
CopyFormatterListReverseIterator
( const FormatterListReverseIterator * );

void
DestroyFormatterListReverseIterator
( FormatterListReverseIterator * );

unsigned short
FormatterListReverseIteratorHasNext
( const FormatterListReverseIterator * );

FormatterListReverseIterator *
NewFormatterListReverseIterator
( FormatterList *, int );

Formatter *
NextInFormatterListReverseIterator
( FormatterListReverseIterator * );

#endif
