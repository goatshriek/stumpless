#ifndef STUMPLESS_TEXT_FORMATTER_STATIC_H
#define STUMPLESS_TEXT_FORMATTER_STATIC_H

#include <type.h>

static
StumplessValueList *
BooleanArrayValueAsValueList( StumplessValue * )

static
StumplessValueList *
BooleanValueAsValueList( StumplessValue * );

static
StumplessValueList *
CharArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
CharValueAsValueList( StumplessValue * );

static
StumplessValueList *
DoubleArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
DoubleValueAsValueList( StumplessValue * );

static
StumplessValueList *
EntryAsValueList( StumplessEntry * );

static
StumplessValueList *
EntryAttributeAsValueList( StumplessEntryAttribute * );

static
StumplessValueList *
EntryAttributeListAsValueList( StumplessEntry * );

static
StumplessValueList *
EntrySummaryAsValueList( StumplessEntry * );

static
StumplessValueList *
EventAsValueList( StumplessEvent * );

static
StumplessValueList *
EventAttributeAsValueList( StumplessEventAttribute * );

static
StumplessValueList *
EventAttributeListAsValueList( StumplessEvent * );

static
StumplessValueList *
EventSummaryAsValueList( StumplessEvent * );

static
StumplessValueList *
FloatArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
FloatValueAsValueList( StumplessValue * );

static
StumplessValueList *
IntValueArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
IntValueAsValueList( StumplessValue * );

static
StumplessValueList *
LevelAsValueList( StumplessLevel * );

static
StumplessValueList *
LongArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
LongDoubleArrayValueAsValueList( StumplessValue * )

static
StumplessValueList *
LongDoubleValueAsValueList( StumplessValue * );

static
StumplessValueList *
LongLongArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
LongLongValueAsValueList( StumplessValue * );

static
StumplessValueList *
LongValueAsValueList( StumplessValue * );

static
StumplessValueList *
ShortArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
ShortValueAsValueList( StumplessValue * );

static
StumplessValueList *
SignedCharArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
SignedCharValueAsValueList( StumplessValue * );

static
StumplessValueList *
StringArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
StringValueAsValueList( StumplessValue * );

static
StumplessFormattedOutput *
TextFormattedOutputFromValueList( StumplessValue * );

static
StumplessValueList *
UnsignedCharArrayValueAsValueList( StumplessValue * );

static
UnsignedCharValueAsValueList( StumplessValue * );

static
StumplessValueList *
UnsignedIntArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
UnsignedIntValueAsValueList( StumplessValue * );

static
StumplessValueList *
UnsignedLongArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
UnsignedLongLongArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
UnsignedLongLongValueAsValueList( StumplessValue * );

static
StumplessValueList *
UnsignedLongValueAsValueList( StumplessValue * );

static
StumplessValueList *
UnsignedShortArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
UnsignedShortValueAsValueList( StumplessValue * );

static
StumplessValueList *
ValueAsValueList( StumplessValue * );

static
StumplessValueList *
ValueTypeAsValueList( StumplessValueType );

#endif
