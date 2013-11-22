#ifndef __STUMPLESS_ADAPTER_H
#define __STUMPLESS_ADAPTER_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddAdapter )
( __STUMPLESS_NAME( Adapter ) * );

__STUMPLESS_NAME( Adapter ) *
__STUMPLESS_NAME( FindAdapterByName )
( const char * );

void *
__STUMPLESS_NAME( GetAdapterOption )
( const __STUMPLESS_NAME( Adapter ) *, const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetAdapterOption )
( __STUMPLESS_NAME( Adapter ) *, const char *, void * );

#endif
