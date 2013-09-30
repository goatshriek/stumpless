#ifndef STUMPLESS_TEST_INCLUDE_BUILDER_H
#define STUMPLESS_TEST_INCLUDE_BUILDER_H

#include "private/type.h"

Boolean *
BuildBoolean( void );

Value *
BuildBooleanValue( void );

FormattedOutput *
BuildByteFormattedOutput( void );

Value *
BuildCharArrayValue( void );

Value *
BuildEmptyUnsignedIntArrayValue( void );

Entry *
BuildEntry( void );

EntryAttribute *
BuildEntryAttribute( void );

EntryAttribute **
BuildEntryAttributeList( void );

Event *
BuildEvent( void );

EventAttribute *
BuildEventAttribute( void );

EventAttribute **
BuildEventAttributeList( void );

Value *
BuildIntArrayValue( void );

Value *
BuildIntValue( void );

Level *
BuildLevel( void );

LoggingProfile *
BuildLoggingProfile( void );

OutputProfile *
BuildOutputProfile( void );

Value *
BuildStringValue( void );

FormattedOutput *
BuildTextFormattedOutput( void );

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

#endif
