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
InitializeListFailureStatus
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
InitializeStreamWriteFailureStatus
( void );

Status *
InitializeStringWriteFailureStatus
( void );

Status *
InitializeValueProfileNotFoundStatus
( void );

#endif
