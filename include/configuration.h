#ifndef STUMPLESS_CONFIGURATION_H
#define STUMPLESS_CONFIGURATION_H

#include <types.h>

extern StumplessConfiguration * configuration;

StumplessConfiguration * StumplessGetConfiguration( void );
StumplessStatusCode StumplessInitializeConfiguration( void );

#endif
