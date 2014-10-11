#ifndef __STUMPLESS_STATIC_FORMATTER_TEXT_H
#define __STUMPLESS_STATIC_FORMATTER_TEXT_H

#include "private/type.h"

static
ValueList *
ArrayValueToValueList
( const Value * );

static
ValueList *
RecordToValueList
( const Record * );

static
ValueList *
RecordAttributeToValueList
( const RecordAttribute * );

static
ValueList *
RecordAttributeListToValueList
( const Record * );

static
ValueList *
RecordSummaryToValueList
( const Record * );

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
