#ifndef STUMPLESS_TEXT_FORMATTER_H
#define STUMPLESS_TEXT_FORMATTER_H

#include <type.h>

StumplessFormattedOutput *
StumplessBooleanArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessBooleanValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessCharArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessCharValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessDoubleArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessDoubleValueAsText( StumplessValue * );

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
StumplessFloatArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessFloatValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessIntArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessIntValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessLevelAsText( StumplessLevel * );

StumplessFormattedOutput *
StumplessLongArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessLongDoubleArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessLongDoubleValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessLongLongArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessLongLongValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessLongValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessShortArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessShortValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessSignedCharArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessSignedCharValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessStringArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessStringValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessUnsignedCharArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessUnsignedCharValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessUnsignedIntArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessUnsignedIntValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessUnsignedLongArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessUnsignedLongLongArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessUnsignedLongLongValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessUnsignedLongValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessUnsignedShortArrayValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessUnsignedShortValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessValueAsText( StumplessValue * );

StumplessFormattedOutput *
StumplessValueTypeAsText( StumplessValueType );

#endif
