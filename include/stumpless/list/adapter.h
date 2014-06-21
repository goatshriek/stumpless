#ifndef __STUMPLESS_LIST_ADAPTER_LIST_H
#define __STUMPLESS_LIST_ADAPTER_LIST_H

#include <stumpless/type.h>

unsigned short
AdapterListContains
( AdapterList *, Adapter * );

unsigned short
AdapterListIsEmpty
( AdapterList * );

unsigned
AdapterListSize
( const AdapterList * );

AdapterList *
AddSeparatorToAdapterList
( AdapterList *, Adapter * );

AdapterList *
AppendAdapterLists
( AdapterList *, AdapterList * );

AdapterList *
AppendToAdapterList
( AdapterList *, Adapter * );

AdapterList *
CopyAdapterList
( AdapterList * );

void
DestroyAdapterList
( AdapterList * );

AdapterList *
NewAdapterList
( void );

AdapterList *
PrependToAdapterList
( AdapterList *, Adapter * );

Entry *
ValueThroughAdapterList
( AdapterList *, Value * );

#endif
