#ifndef __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_RECORD_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_CONST_REVERSE_ITERATOR_RECORD_ATTRIBUTE_H

#include "private/type.h"

RecordAttributeListConstReverseIterator *
CopyRecordAttributeListConstReverseIterator
( const RecordAttributeListConstReverseIterator * );

void
DestroyRecordAttributeListConstReverseIterator
( RecordAttributeListConstReverseIterator * );

unsigned short
RecordAttributeListConstReverseIteratorHasNext
( const RecordAttributeListConstReverseIterator * );

RecordAttributeListConstReverseIterator *
NewRecordAttributeListConstReverseIterator
( const RecordAttributeList *, int );

const RecordAttribute *
NextInRecordAttributeListConstReverseIterator
( RecordAttributeListConstReverseIterator * );

#endif
