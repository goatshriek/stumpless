#ifndef STUMPLESS_TEST_INCLUDE_BUILDER_H
#define STUMPLESS_TEST_INCLUDE_BUILDER_H

#include <stumpless.h>

StumplessBoolean *
BuildBoolean( void );

StumplessFormattedOutput *
BuildByteFormattedOutput( void );

StumplessCustomProfile *
BuildCustomProfile( void );

StumplessValue *
BuildEmptyUnsignedIntArrayValue( void );

StumplessEntry *
BuildEntry( void );

StumplessEntryAttribute *
BuildEntryAttribute( void );

StumplessEntryAttribute **
BuildEntryAttributeList( void );

StumplessEvent *
BuildEvent( void );

StumplessEventAttribute *
BuildEventAttribute( void );

StumplessEventAttribute **
BuildEventAttributeList( void );

StumplessValue *
BuildIntArrayValue( void );

StumplessValue *
BuildIntValue( void );

StumplessLevel *
BuildLevel( void );

StumplessValue *
BuildStringValue( void );

StumplessFormattedOutput *
BuildTextFormattedOutput( void );

StumplessValue *
BuildUnsignedIntValue( void );

StumplessValue *
BuildUnsignedShortValue( void );

StumplessValueList *
BuildValueList( void );

StumplessValueList *
BuildValueListOfStrings( void );

StumplessValue *
BuildVoidValue( void );

#endif
