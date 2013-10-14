#ifndef STUMPLESS_TEST_INCLUDE_BUILDER_H
#define STUMPLESS_TEST_INCLUDE_BUILDER_H

#include "private/type.h"

Boolean *
BuildBoolean( void );

Value *
BuildBooleanValue( void );

Output *
BuildByteOutput( void );

Value *
BuildCharArrayValue( void );

Dictionary *
BuildDictionaryOfStrings
( void );

Value *
BuildEmptyUnsignedIntArrayValue( void );

Entry *
BuildEntry( void );

EntryAttribute *
BuildEntryAttribute( void );

EntryAttribute **
BuildEntryAttributeList( void );

Status *
BuildErrorStatus
( void );

Event *
BuildEvent( void );

EventAttribute *
BuildEventAttribute( void );

EventAttribute **
BuildEventAttributeList( void );

Status *
BuildFailureStatus
( void );

Value *
BuildIntArrayValue( void );

Value *
BuildIntValue( void );

Level *
BuildLevel( void );

LoggerProfile *
BuildLoggerProfile( void );

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
