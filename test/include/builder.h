#ifndef __STUMPLESS_TEST_INCLUDE_BUILDER_H
#define __STUMPLESS_TEST_INCLUDE_BUILDER_H

#include "private/type.h"

Adapter *
BuildAdapter
( void );

AdapterList *
BuildAdapterList
( void );

Boolean *
BuildBoolean
( void );

Value *
BuildBooleanValue
( void );

Output *
BuildByteOutput
( void );

Value *
BuildCharArrayValue
( void );

Comparator *
BuildComparator
( void );

ComparatorList *
BuildComparatorList
( void );

Dictionary *
BuildDictionaryOfStrings
( void );

Record *
BuildEmptyRecord
( void );

Output *
BuildEmptyOutput
( void );

Value *
BuildEmptyUnsignedIntArrayValue
( void );

Value *
BuildEmptyValue
( void );

Record *
BuildRecord
( void );

RecordAttribute *
BuildRecordAttribute
( void );

RecordAttributeList *
BuildRecordAttributeList
( void );

Status *
BuildErrorStatus
( void );

Event *
BuildEvent
( void );

EventAttribute *
BuildEventAttribute
( void );

EventAttributeList *
BuildEventAttributeList
( void );

Status *
BuildFailureStatus
( void );

Filter *
BuildFilter
( void );

FilterList *
BuildFilterList
( void );

Formatter *
BuildFormatter
( void );

FormatterList *
BuildFormatterList
( void );

Handler *
BuildHandler
( void );

HandlerList *
BuildHandlerList
( void );

Value *
BuildIntArrayValue
( void );

Value *
BuildIntValue
( void );

Level *
BuildLevel
( void );

ListIterator *
BuildListIterator
( void );

List *
BuildListOfStrings
( void );

ListReverseIterator *
BuildListReverseIterator
( void );

Logger *
BuildLogger
( void );

OutputProfile *
BuildOutputProfile
( void );

Output *
BuildRawStringOutput
( void );

Stack *
BuildStackOfStrings
( void );

Value *
BuildStringValue
( void );

Target *
BuildTarget
( void );

TargetList *
BuildTargetList
( void );

Output *
BuildTextOutput
( void );

Tree *
BuildTreeOfStrings
( void );

Value *
BuildUnsignedIntValue
( void );

Value *
BuildUnsignedShortValue
( void );

Value *
BuildValue
( void );

ValueList *
BuildValueList
( void );

ValueList *
BuildValueListOfStrings
( void );

ValueProfile *
BuildValueProfile
( void );

Value *
BuildVoidValue
( void );

Status *
BuildWarningStatus
( void );

#endif
