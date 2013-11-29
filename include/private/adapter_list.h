#ifndef STUMPLESS_PRIVATE_ADAPTER_LIST_H
#define STUMPLESS_PRIVATE_ADAPTER_LIST_H

#include "private/type.h"

unsigned short
AdapterListContains
( AdapterList *, Adapter * );

unsigned short
AdapterListIsEmpty
( AdapterList * );

Status *
AppendToAdapterList
( AdapterList *, Adapter * );

Adapter *
BeginAdapterList
( AdapterList * );

AdapterList *
CopyAdapterList
( AdapterList * );

void
DestroyAdapterList
( AdapterList * );

AdapterList *
NewAdapterList
( void );

Adapter *
NextInAdapterList
( AdapterList * );

Status *
PrependToAdapterList
( AdapterList *, Adapter * );

Entry *
ValueThroughAdapterList
( AdapterList *, Value * );

#endif
