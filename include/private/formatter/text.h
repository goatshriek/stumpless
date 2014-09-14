#ifndef __STUMPLESS_PRIVATE_FORMATTER_TEXT_H
#define __STUMPLESS_PRIVATE_FORMATTER_TEXT_H

#include "private/type.h"

Output *
ArrayValueToText
( const Value * );

Output *
RecordToText
( const Record *, Dictionary * );

Output *
RecordAttributeToText
( const RecordAttribute * );

Output *
RecordAttributeListToText
( const Record * );

Output *
RecordSummaryToText
( const Record * );

Output *
EventToText
( const Event * );

Output * 
EventAttributeToText
( const EventAttribute * );

Output *
EventAttributeListToText
( const Event * );

Output *
EventSummaryToText
( const Event * );

Output *
LevelToText
( const Level * );

Output *
SingularValueToText
( const Value * );

#endif
