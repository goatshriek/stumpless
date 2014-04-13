#ifndef __STUMPLESS_STATIC_FORMATTER_TEXT_H
#define __STUMPLESS_STATIC_FORMATTER_TEXT_H

#include "private/type.h"

static
ValueList *
ArrayValueToValueList
( const Value * );

static
ValueList *
EntryToValueList
( const Entry * );

static
ValueList *
EntryAttributeToValueList
( const EntryAttribute * );

static
ValueList *
EntryAttributeListToValueList
( const Entry * );

static
ValueList *
EntrySummaryToValueList
( const Entry * );

static
ValueList *
EventToValueList
( const Event * );

static
ValueList *
EventAttributeToValueList
( const EventAttribute * );

static
ValueList *
EventAttributeListToValueList
( const Event * );

static
ValueList *
EventSummaryToValueList
( const Event * );

static
ValueList *
GenericArrayValueToValueList
( const Value * );

static
ValueList *
GenericValueToValueList
( const Value * );

static
ValueList *
LevelToValueList
( const Level * );

static
ValueList *
SingularValueToValueList
( const Value * );

static
Output *
TextOutputFromValueList
( const ValueList * );

#endif
