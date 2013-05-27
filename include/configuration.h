#ifndef STUMPLESS_CONFIGURATION_H
#define STUMPLESS_CONFIGURATION_H

#include <type.h>

StumplessStatusCode
StumplessAddOutputProfile( StumplessOutputProfile * );

StumplessStatusCode
StumplessAddValueProfile( StumplessValueProfile * );

StumplessOutputProfile *
StumplessFindOutputProfileByName( const char * );

StumplessValueProfile *
StumplessFindValueProfileByName( const char * );

StumplessConfiguration *
StumplessGetConfiguration( void );

StumplessStatusCode
StumplessInitializeConfiguration( void );

StumplessStatusCode
StumplessInitializeOutputProfiles( void );

StumplessStatusCode
StumplessInitializeValueProfiles( void );

StumplessStatusCode
StumplessSetConfiguration( StumplessConfiguration * );

#endif
