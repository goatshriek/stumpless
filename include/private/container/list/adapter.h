#ifndef __STUMPLESS_PRIVATE_LIST_ADAPTER_H
#define __STUMPLESS_PRIVATE_LIST_ADAPTER_H

#include "private/type.h"

Adapter *
AdapterListBack
( const AdapterList * );

unsigned short
AdapterListContains
( const AdapterList *, const Adapter * );

Adapter *
AdapterListFront
( const AdapterList * );

unsigned short
AdapterListIsEmpty
( const AdapterList * );

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

AdapterListIterator *
BeginAdapterList
( AdapterList * );

AdapterListConstIterator *
CBeginAdapterList
( const AdapterList * );

AdapterListConstIterator *
CEndAdapterList
( const AdapterList * );

AdapterList *
CopyAdapterList
( const AdapterList * );

AdapterListConstReverseIterator *
CRBeginAdapterList
( const AdapterList * );

AdapterListConstReverseIterator *
CREndAdapterList
( const AdapterList * );

void
DestroyAdapterList
( AdapterList * );

AdapterListIterator *
EndAdapterList
( AdapterList * );

Record *
RecordThroughAdapterList
( AdapterList *, Record * );

AdapterList *
NewAdapterList
();

AdapterList *
PrependToAdapterList
( AdapterList *, Adapter * );

AdapterListReverseIterator *
RBeginAdapterList
( AdapterList * );

AdapterListReverseIterator *
REndAdapterList
( AdapterList * );

#endif
