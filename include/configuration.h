#ifndef STUMPLESS_CONFIGURATION_H
#define STUMPLESS_CONFIGURATION_H

#include <type.h>

StumplessStatusCode
StumplessAddTypeProfile( StumplessValueProfile * );

StumplessValueProfile *
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
