#ifndef STUMPLESS_PRIVATE_STATIC_TEXT_FORMATTER_H
#define STUMPLESS_PRIVATE_STATIC_TEXT_FORMATTER_H

#include "private/type.h"

static
ValueList *
ArrayValueToValueList( Value * );

static
ValueList *
EntryToValueList( Entry * );

static
ValueList *
EntryAttributeToValueList( EntryAttribute * );

static
ValueList *
EntryAttributeListToValueList( Entry * );

static
ValueList *
EntrySummaryToValueList( Entry * );

static
ValueList *
EventToValueList( Event * );

static
ValueList *
EventAttributeToValueList( EventAttribute * );

static
ValueList *
EventAttributeListToValueList( Event * );

static
ValueList *
EventSummaryToValueList( Event * );

static
ValueList *
GenericArrayValueToValueList( Value * );

static
ValueList *
GenericValueToValueList( Value * );

static
ValueList *
LevelToValueList( Level * );

static
ValueList *
SingularValueToValueList( Value * );

static
Output *
TextOutputFromValueList( ValueList * );

#endif
