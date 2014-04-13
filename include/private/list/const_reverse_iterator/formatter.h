#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_FORMATTER_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_FORMATTER_H

#include "private/type.h"

FormatterListConstReverseIterator *
CopyFormatterListConstReverseIterator
( const FormatterListConstReverseIterator * );

void
DestroyFormatterListConstReverseIterator
( FormatterListConstReverseIterator * );

unsigned short
FormatterListConstReverseIteratorHasNext
( const FormatterListConstReverseIterator * );

FormatterListConstReverseIterator *
NewFormatterListConstReverseIterator
( const FormatterList *, int );

const Formatter *
NextInFormatterListConstReverseIterator
( FormatterListConstReverseIterator * );

#endif
