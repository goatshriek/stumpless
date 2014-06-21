#ifndef __STUMPLESS_LIST_ITERATOR_ADAPTER_H
#define __STUMPLESS_LIST_ITERATOR_ADAPTER_H

#include <stumpless/type.h>

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
( AdapterList * );

Adapter *
NextInAdapterListIterator
( AdapterListIterator * );

#endif
