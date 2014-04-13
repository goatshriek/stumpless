#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_FORMATTER_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_FORMATTER_H

#include "private/type.h"

FormatterListConstIterator *
CopyFormatterListConstIterator
( const FormatterListConstIterator * );

void
DestroyFormatterListConstIterator
( FormatterListConstIterator * );

unsigned short
FormatterListConstIteratorHasNext
( const FormatterListConstIterator * );

FormatterListConstIterator *
NewFormatterListConstIterator
( const FormatterList *, int );

const Formatter *
NextInFormatterListConstIterator
( FormatterListConstIterator * );

#endif
