#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_ADAPTER_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_ADAPTER_H

#include "private/type.h"

unsigned short
AdapterListReverseIteratorHasNext
( const AdapterListReverseIterator * );

AdapterListReverseIterator *
CopyAdapterListReverseIterator
( const AdapterListReverseIterator * );

void
DestroyAdapterListReverseIterator
( AdapterListReverseIterator * );

AdapterListReverseIterator *
NewAdapterListReverseIterator
( AdapterList *, int );

Adapter *
NextInAdapterListReverseIterator
( AdapterListReverseIterator * );

#endif
