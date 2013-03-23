#ifndef STUMPLESS_TEXT_FORMATTER_H
#define STUMPLESS_TEXT_FORMATTER_H

#include <types.h>

StumplessFormattedOutput *
StumplessEntryAsText( StumplessEntry * );

StumplessFormattedOutput *
StumplessEventAsText( StumplessEvent * );

StumplessFormattedOutput *
StumplessEventSummaryAsText( StumplessEvent * );

StumplessFormattedOutput * 
StumplessEventAttributeAsText( StumplessEventAttribute * );

StumplessFormattedOutput *
StumplessEventAttributeSummaryAsText( StumplessEventAttribute * );

StumplessFormattedOutput *
StumplessEventAttributeListAsText( StumplessEvent * );

StumplessFormattedOutput *
StumplessLevelAsText( StumplessLevel * );

StumplessFormattedOutput *
StumplessValueAsText( StumplessValue * );

#endif
