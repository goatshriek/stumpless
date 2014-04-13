#ifndef __STUMPLESS_PRIVATE_TEXT_FORMATTER_H
#define __STUMPLESS_PRIVATE_TEXT_FORMATTER_H

#include "private/type.h"

Output *
ArrayValueToText
( const Value * );

Output *
EntryToText
( const Entry *, Dictionary * );

Output *
EntryAttributeToText
( const EntryAttribute * );

Output *
EntryAttributeListToText
( const Entry * );

Output *
EntrySummaryToText
( const Entry * );

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
