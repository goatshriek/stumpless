#ifndef STUMPLESS_CONFIGURATION_H
#define STUMPLESS_CONFIGURATION_H

#include <type.h>

StumplessProfileIndex
StumplessAddCustomProfile( StumplessCustomProfile * );

StumplessCustomProfile *
StumplessFindProfileByIndex( StumplessProfileIndex );

StumplessCustomProfile *
StumplessFindProfileByName( const char * );

StumplessConfiguration *
StumplessGetConfiguration( void );

StumplessStatusCode
StumplessInitializeConfiguration( void );

StumplessStatusCode
StumplessInitializeProfiles( void );

StumplessStatusCode
StumplessSetConfiguration( StumplessConfiguration * );

#endif
