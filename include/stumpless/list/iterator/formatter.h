#ifndef __STUMPLESS_LIST_ITERATOR_FORMATTER_H
#define __STUMPLESS_LIST_ITERATOR_FORMATTER_H

#include <stumpless/type.h>

unsigned short
FormatterListIteratorHasNext
( const FormatterListIterator * );

FormatterListIterator *
CopyFormatterListIterator
( const FormatterListIterator * );

void
DestroyFormatterListIterator
( FormatterListIterator * );

FormatterListIterator *
NewFormatterListIterator
( FormatterList * );

Formatter *
NextInFormatterListIterator
( FormatterListIterator * );

#endif
