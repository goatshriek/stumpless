#ifndef __STUMPLESS_PRIVATE_LIST_ITERATOR_RECORD_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_ITERATOR_RECORD_ATTRIBUTE_H

#include "private/type.h"

RecordAttributeListIterator *
CopyRecordAttributeListIterator
( const RecordAttributeListIterator * );

void
DestroyRecordAttributeListIterator
( RecordAttributeListIterator * );

unsigned short
RecordAttributeListIteratorHasNext
( const RecordAttributeListIterator * );

RecordAttributeListIterator *
NewRecordAttributeListIterator
( RecordAttributeList *, int );

RecordAttribute *
NextInRecordAttributeListIterator
( RecordAttributeListIterator * );

#endif
