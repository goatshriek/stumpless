#ifndef STUMPLESS_TEST_INCLUDE_BUILDER_H
#define STUMPLESS_TEST_INCLUDE_BUILDER_H

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

Dictionary *
BuildDictionaryOfStrings
( void );

Entry *
BuildEmptyEntry
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

Entry *
BuildEntry
( void );

EntryAttribute *
BuildEntryAttribute
( void );

EntryAttribute **
BuildEntryAttributeList
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

EventAttribute **
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
BuildIntArrayValue( void );

Value *
BuildIntValue( void );

Level *
BuildLevel( void );

List *
BuildListOfStrings
( void );

OutputProfile *
BuildOutputProfile( void );

Output *
BuildRawStringOutput( void );

Value *
BuildStringValue( void );

Output *
BuildTextOutput( void );

Value *
BuildUnsignedIntValue( void );

Value *
BuildUnsignedShortValue( void );

ValueList *
BuildValueList( void );

ValueList *
BuildValueListOfStrings( void );

ValueProfile *
BuildValueProfile( void );

Value *
BuildVoidValue( void );

Status *
BuildWarningStatus
( void );

#endif
