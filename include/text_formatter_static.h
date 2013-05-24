#ifndef STUMPLESS_TEXT_FORMATTER_STATIC_H
#define STUMPLESS_TEXT_FORMATTER_STATIC_H

#include <type.h>

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
GenericArrayValueAsValueList( StumplessValue * );

static
StumplessValueList *
GenericValueAsValueList( StumplessValue * );

static
StumplessValueList *
LevelAsValueList( StumplessLevel * );

static
StumplessFormattedOutput *
TextFormattedOutputFromValueList( StumplessValueList * );

static
StumplessValueList * // todo remove this function
ValueAsValueList( StumplessValue * );

static
StumplessValueList * // todo remove this function
ValueTypeAsValueList( StumplessValueType );

#endif
