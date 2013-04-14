#ifndef STUMPLESS_TEST_INCLUDE_BUILDER_H
#define STUMPLESS_TEST_INCLUDE_BUILDER_H

#include <stumpless.h>

StumplessFormattedOutput *
BuildByteFormattedOutput( void );

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

StumplessLevel *
BuildLevel( void );

StumplessFormattedOutput *
BuildTextFormattedOutput( void );

StumplessValue *
BuildUnsignedShortValue( void );

#endif
