#ifndef STUMPLESS_PRIVATE_STATUS_INITIALIZER_H
#define STUMPLESS_PRIVATE_STATUS_INITIALIZER_H

#include "private/type.h"

Status *
InitializeConstructorFailureStatus
( void );

Status *
InitializeEmptyArgumentStatus
( void );

Status *
InitializeMalformedStructureStatus
( void );

Status *
InitializeMemoryAllocationFailureStatus
( void );

Status *
InitializeStatusByName
( const char * );

Status *
InitializeStringWriteFailureStatus
( void );

#endif
