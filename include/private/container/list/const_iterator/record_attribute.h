#ifndef __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_RECORD_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_LIST_CONST_ITERATOR_RECORD_ATTRIBUTE_H

#include "private/type.h"

RecordAttributeListConstIterator *
CopyRecordAttributeListConstIterator
( const RecordAttributeListConstIterator * );

void
DestroyRecordAttributeListConstIterator
( RecordAttributeListConstIterator * );

unsigned short
RecordAttributeListConstIteratorHasNext
( const RecordAttributeListConstIterator * );

RecordAttributeListConstIterator *
NewRecordAttributeListConstIterator
( const RecordAttributeList *, int );

const RecordAttribute *
NextInRecordAttributeListConstIterator
( RecordAttributeListConstIterator * );

#endif
