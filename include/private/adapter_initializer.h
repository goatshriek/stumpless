#ifndef STUMPLESS_PRIVATE_ADAPTER_INITIALIZER_H
#define STUMPLESS_PRIVATE_ADAPTER_INITIALIZER_H

#include "private/type.h"

Adapter *
InitializeContextAdapter
( void );

Status *
InitializeAdapterByName
( const char * );

#endif
