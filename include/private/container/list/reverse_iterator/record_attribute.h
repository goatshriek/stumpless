#ifndef __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_RECORD_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_REVERSE_ITERATOR_RECORD_ATTRIBUTE_H

#include "private/type.h"

RecordAttributeListReverseIterator *
CopyRecordAttributeListReverseIterator
( const RecordAttributeListReverseIterator * );

void
DestroyRecordAttributeListReverseIterator
( RecordAttributeListReverseIterator * );

unsigned short
RecordAttributeListReverseIteratorHasNext
( const RecordAttributeListReverseIterator * );

RecordAttributeListReverseIterator *
NewRecordAttributeListReverseIterator
( RecordAttributeList *, int );

RecordAttribute *
NextInRecordAttributeListReverseIterator
( RecordAttributeListReverseIterator * );

#endif
