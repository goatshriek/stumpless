#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_ADAPTER_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_ADAPTER_H

#include "private/type.h"

unsigned short
AdapterListConstReverseIteratorHasNext
( const AdapterListConstReverseIterator * );

AdapterListConstReverseIterator *
CopyAdapterListConstReverseIterator
( const AdapterListConstReverseIterator * );

void
DestroyAdapterListConstReverseIterator
( AdapterListConstReverseIterator * );

AdapterListConstReverseIterator *
NewAdapterListConstReverseIterator
( const AdapterList *, int );

const Adapter *
NextInAdapterListConstReverseIterator
( AdapterListConstReverseIterator * );

#endif
