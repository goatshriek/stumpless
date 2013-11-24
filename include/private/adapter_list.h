#ifndef STUMPLESS_PRIVATE_ADAPTER_LIST_H
#define STUMPLESS_PRIVATE_ADAPTER_LIST_H

#include "private/type.h"

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

unsigned short
AdapterListIsEmpty
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
