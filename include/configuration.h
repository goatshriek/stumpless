#ifndef STUMPLESS_CONFIGURATION_H
#define STUMPLESS_CONFIGURATION_H

#include <type.h>

StumplessStatusCode
StumplessAddLoggingProfile( StumplessLoggingProfile * );

StumplessStatusCode
StumplessAddOutputProfile( StumplessOutputProfile * );

StumplessStatusCode
StumplessAddValueProfile( StumplessValueProfile * );

StumplessLoggingProfile *
StumplessFindLoggingProfileByName( const char * );

StumplessOutputProfile *
StumplessFindOutputProfileByName( const char * );

StumplessValueProfile *
StumplessFindValueProfileByName( const char * );

StumplessConfiguration *
StumplessGetConfiguration( void );

StumplessStatusCode
StumplessInitializeConfiguration( void );

StumplessStatusCode
StumplessInitializeLoggingProfiles( void );

StumplessStatusCode
StumplessInitializeOutputProfiles( void );

StumplessStatusCode
StumplessInitializeValueProfiles( void );

StumplessStatusCode
StumplessSetConfiguration( StumplessConfiguration * );

#endif
