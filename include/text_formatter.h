#ifndef STUMPLESS_TEXT_FORMATTER_H
#define STUMPLESS_TEXT_FORMATTER_H

#include <type.h>

StumplessFormattedOutput *
StumplessEntryToText( StumplessEntry * );

StumplessFormattedOutput *
StumplessEntryAttributeToText( StumplessEntryAttribute * );

StumplessFormattedOutput *
StumplessEntryAttributeListToText( StumplessEntry * );

StumplessFormattedOutput *
StumplessEntrySummaryToText( StumplessEntry * );

StumplessFormattedOutput *
StumplessEventToText( StumplessEvent * );

StumplessFormattedOutput * 
StumplessEventAttributeToText( StumplessEventAttribute * );

StumplessFormattedOutput *
StumplessEventAttributeListToText( StumplessEvent * );

StumplessFormattedOutput *
StumplessEventSummaryToText( StumplessEvent * );

StumplessFormattedOutput *
StumplessGenericArrayValueToText( StumplessValue * );

StumplessFormattedOutput *
StumplessGenericValueToText( StumplessValue * );

StumplessFormattedOutput *
StumplessLevelToText( StumplessLevel * );

#endif
