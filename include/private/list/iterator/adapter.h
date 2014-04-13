#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_ADAPTER_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_ADAPTER_H

#include "private/type.h"

unsigned short
AdapterListIteratorHasNext
( const AdapterListIterator * );

AdapterListIterator *
CopyAdapterListIterator
( const AdapterListIterator * );

void
DestroyAdapterListIterator
( AdapterListIterator * );

AdapterListIterator *
NewAdapterListIterator
( AdapterList *, int );

Adapter *
NextInAdapterListIterator
( AdapterListIterator * );

#endif
