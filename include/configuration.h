#ifndef STUMPLESS_CONFIGURATION_H
#define STUMPLESS_CONFIGURATION_H

#include <types.h>

StumplessConfiguration * StumplessGetConfiguration( void );
StumplessStatusCode StumplessInitializeConfiguration( void );
StumplessStatusCode StumplessSetConfiguration( StumplessConfiguration * );

#endif
