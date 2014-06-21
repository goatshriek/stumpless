#ifndef __STUMPLESS_PRIVATE_CONFIGURATION_H
#define __STUMPLESS_PRIVATE_CONFIGURATION_H

#include <stumpless/type.h>

Configuration *
GetConfiguration
( void );

Status *
InitializeConfiguration
( void );

Status *
SetConfiguration
( Configuration * );

#endif
