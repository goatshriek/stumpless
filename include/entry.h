#ifndef __STUMPLESS_ENTRY_H
#define __STUMPLESS_ENTRY_H

#include <public_name.h>
#include <type.h>

char *
__NAME( EntryToString )( __NAME( Entry ) * );

__NAME( Entry ) *
__NAME( GetDebugEntry )( void );

__NAME( Entry ) *
__NAME( EntryForEvent )( __NAME( Event ) * );

__NAME( Entry ) *
__NAME( GetErrorEntry )( void );

__NAME( Entry ) *
__NAME( GetFatalEntry )( void );

__NAME( Entry ) *
__NAME( GetInfoEntry )( void );

__NAME( Entry ) *
__NAME( GetWarningEntry )( void );

#endif
