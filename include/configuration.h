#ifndef STUMPLESS_CONFIGURATION_H
#define STUMPLESS_CONFIGURATION_H

#include <types.h>

extern StumplessConfiguration * stumpless_configuration;

StumplessConfiguration * StumplessGetConfiguration( void );
StumplessStatusCode StumplessInitializeConfiguration( void );
StumplessStatusCode StumplessSetConfiguration( StumplessConfiguration * );

#endif
