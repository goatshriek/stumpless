#ifndef __STUMPLESS_ADAPTER_H
#define __STUMPLESS_ADAPTER_H

#include <stumpless/type.h>

Status *
AddAdapter
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
