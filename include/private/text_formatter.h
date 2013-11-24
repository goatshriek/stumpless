#ifndef STUMPLESS_PRIVATE_TEXT_FORMATTER_H
#define STUMPLESS_PRIVATE_TEXT_FORMATTER_H

#include "private/type.h"

Output *
ArrayValueToText( Value * );

Output *
EntryToText( Entry *, Dictionary * );

Output *
EntryAttributeToText( EntryAttribute * );

Output *
EntryAttributeListToText( Entry * );

Output *
EntrySummaryToText( Entry * );

Output *
EventToText( Event * );

Output * 
EventAttributeToText( EventAttribute * );

Output *
EventAttributeListToText( Event * );

Output *
EventSummaryToText( Event * );

Output *
LevelToText( Level * );

Output *
SingularValueToText( Value * );

#endif
