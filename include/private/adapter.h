#ifndef __STUMPLESS_PRIVATE_ADAPTER_H
#define __STUMPLESS_PRIVATE_ADAPTER_H

#include "private/type.h"

Record *
AdaptRecord
( Adapter *, Record * );

Status *
AddAdapter
( Adapter * );

void
DestroyAdapter
( Adapter * );

Adapter *
FindAdapterByName
( const char * );

void *
GetAdapterOption
( const Adapter *, const char * );

Status *
SetAdapterOption
( Adapter *, const char *, void * );

#endif
