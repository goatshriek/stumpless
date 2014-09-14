#ifndef __STUMPLESS_PRIVATE_LIST_RECORD_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_RECORD_ATTRIBUTE_H

#include "private/type.h"

RecordAttributeList *
AddSeparatorToRecordAttributeList
( RecordAttributeList *, RecordAttribute * );

RecordAttributeList *
AppendRecordAttributeLists
( RecordAttributeList *, RecordAttributeList * );

RecordAttributeList *
AppendToRecordAttributeList
( RecordAttributeList *, RecordAttribute * );

RecordAttributeListIterator *
BeginRecordAttributeList
( RecordAttributeList * );

RecordAttributeListConstIterator *
CBeginRecordAttributeList
( const RecordAttributeList * );

RecordAttributeListConstIterator *
CEndRecordAttributeList
( const RecordAttributeList * );

RecordAttributeList *
CopyRecordAttributeList
( const RecordAttributeList * );

RecordAttributeListConstReverseIterator *
CRBeginRecordAttributeList
( const RecordAttributeList * );

RecordAttributeListConstReverseIterator *
CREndRecordAttributeList
( const RecordAttributeList * );

void
DestroyRecordAttributeList
( RecordAttributeList * );

RecordAttributeListIterator *
EndRecordAttributeListIterator
( RecordAttributeList * );

RecordAttribute *
RecordAttributeListBack
( const RecordAttributeList * );

unsigned short
RecordAttributeListContains
( const RecordAttributeList *, const RecordAttribute * );

unsigned short
RecordAttributeListContainsEventAttribute
( const RecordAttributeList *, const EventAttribute * );

RecordAttributeList *
RecordAttributeListForEventAttributeList
( const EventAttributeList * );

RecordAttribute *
RecordAttributeListFront
( const RecordAttributeList * );

unsigned short
RecordAttributeListIsEmpty
( const RecordAttributeList * );

unsigned
RecordAttributeListSize
( const RecordAttributeList * );

RecordAttributeList *
MergeRecordAttributeLists
( RecordAttributeList *, RecordAttributeList * );

RecordAttributeList *
NewRecordAttributeList
();

RecordAttributeList *
PrependToRecordAttributeList
( RecordAttributeList *, RecordAttribute * );

RecordAttributeListReverseIterator *
RBeginRecordAttributeList
( RecordAttributeList * );

RecordAttributeListReverseIterator *
REndRecordAttributeList
( RecordAttributeList * );

#endif
