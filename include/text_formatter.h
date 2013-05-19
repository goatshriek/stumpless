#ifndef STUMPLESS_TEXT_FORMATTER_H
#define STUMPLESS_TEXT_FORMATTER_H

#include <type.h>

StumplessFormattedOutput *
StumplessBooleanArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessBooleanValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessEntryAsText( StumplessEntry * );

StumplessFormattedOutput *
StumplessEntryAttributeAsText( StumplessEntryAttribute * );

StumplessFormattedOutput *
StumplessEntryAttributeListAsText( StumplessEntry * );

StumplessFormattedOutput *
StumplessEntrySummaryAsText( StumplessEntry * );

StumplessFormattedOutput *
StumplessEventAsText( StumplessEvent * );

StumplessFormattedOutput * 
StumplessEventAttributeAsText( StumplessEventAttribute * );

StumplessFormattedOutput *
StumplessEventAttributeListAsText( StumplessEvent * );

StumplessFormattedOutput *
StumplessEventSummaryAsText( StumplessEvent * );

StumplessFormattedOutput *
StumplessGenericArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessGenericValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessLevelAsText( StumplessLevel * );

StumplessFormattedOutput *
StumplessValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessValueTypeAsText( StumplessValueType );

#endif
