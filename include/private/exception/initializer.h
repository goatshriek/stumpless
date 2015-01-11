#ifndef __STUMPLESS_PRIVATE_EXCEPTION_INITIALIZER_H
#define __STUMPLESS_PRIVATE_EXCEPTION_INITIALIZER_H

#include "private/type.h"

Exception *
InitializeConstructorFailureException
( void );

Exception *
InitializeDictionaryFailureException
( void );

Exception *
InitializeDuplicateException
( void );

Exception *
InitializeEmptyArgumentException
( void );

Exception *
InitializeEventFailureException
( void );

Exception *
InitializeForkFailureException
( void );

Exception *
InitializeIncompatibleProfileException
( void );

Exception *
InitializeListFailureException
( void );

Exception *
InitializeMalformedStructureException
( void );

Exception *
InitializeMemoryAllocationFailureException
( void );

Exception *
InitializePipeFailureException
( void );

Exception *
InitializeExceptionByName
( const char * );

Exception *
InitializeStreamWriteFailureException
( void );

Exception *
InitializeStringWriteFailureException
( void );

Exception *
InitializeValueProfileNotFoundException
( void );

#endif
