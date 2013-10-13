#ifndef STUMPLESS_PRIVATE_CONFIGURATION_H
#define STUMPLESS_PRIVATE_CONFIGURATION_H

#include "private/type.h"

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
