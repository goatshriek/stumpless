#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_FORMATTER_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_FORMATTER_H

#include "private/type.h"

FormatterListIterator *
CopyFormatterListIterator
( const FormatterListIterator * );

void
DestroyFormatterListIterator
( FormatterListIterator * );

unsigned short
FormatterListIteratorHasNext
( const FormatterListIterator * );

FormatterListIterator *
NewFormatterListIterator
( FormatterList *, int );

Formatter *
NextInFormatterListIterator
( FormatterListIterator * );

#endif
