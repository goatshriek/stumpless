#ifndef STUMPLESS_TEXT_FORMATTER_STATIC_H
#define STUMPLESS_TEXT_FORMATTER_STATIC_H

#include <type.h>

static
StumplessValueList *
EntryToValueList( StumplessEntry * );

static
StumplessValueList *
EntryAttributeToValueList( StumplessEntryAttribute * );

static
StumplessValueList *
EntryAttributeListToValueList( StumplessEntry * );

static
StumplessValueList *
EntrySummaryToValueList( StumplessEntry * );

static
StumplessValueList *
EventToValueList( StumplessEvent * );

static
StumplessValueList *
EventAttributeToValueList( StumplessEventAttribute * );

static
StumplessValueList *
EventAttributeListToValueList( StumplessEvent * );

static
StumplessValueList *
EventSummaryToValueList( StumplessEvent * );

static
StumplessValueList *
GenericArrayValueToValueList( StumplessValue * );

static
StumplessValueList *
GenericValueToValueList( StumplessValue * );

static
StumplessValueList *
LevelToValueList( StumplessLevel * );

static
StumplessFormattedOutput *
TextFormattedOutputFromValueList( StumplessValueList * );

static
StumplessValueList * // todo remove this function
ValueToValueList( StumplessValue * );

static
StumplessValueList * // todo remove this function
ValueTypeToValueList( StumplessValueType );

#endif
