#ifndef STUMPLESS_PRIVATE_TEXT_FORMATTER_H
#define STUMPLESS_PRIVATE_TEXT_FORMATTER_H

#include <type.h>

FormattedOutput *
ArrayValueToText( Value * );

FormattedOutput *
EntryToText( Entry * );

FormattedOutput *
EntryAttributeToText( EntryAttribute * );

FormattedOutput *
EntryAttributeListToText( Entry * );

FormattedOutput *
EntrySummaryToText( Entry * );

FormattedOutput *
EventToText( Event * );

FormattedOutput * 
EventAttributeToText( EventAttribute * );

FormattedOutput *
EventAttributeListToText( Event * );

FormattedOutput *
EventSummaryToText( Event * );

FormattedOutput *
LevelToText( Level * );

FormattedOutput *
SingularValueToText( Value * );

#endif
