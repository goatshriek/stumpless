#ifndef __STUMPLESS_PRIVATE_RECORD_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_RECORD_ATTRIBUTE_H

#include "private/type.h"

void
DestroyRecordAttribute
( RecordAttribute * );

RecordAttribute *
RecordAttributeForEventAttribute
( const EventAttribute * );

#endif
