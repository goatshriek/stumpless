#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_ADAPTER_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_ADAPTER_H

#include "private/type.h"

unsigned short
AdapterListConstIteratorHasNext
( const AdapterListConstIterator * );

AdapterListConstIterator *
CopyAdapterListConstIterator
( const AdapterListConstIterator * );

void
DestroyAdapterListConstIterator
( AdapterListConstIterator * );

AdapterListConstIterator *
NewAdapterListConstIterator
( const AdapterList *, int );

const Adapter *
NextInAdapterListConstIterator
( AdapterListConstIterator * );

#endif
