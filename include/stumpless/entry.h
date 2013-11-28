#ifndef __STUMPLESS_ENTRY_H
#define __STUMPLESS_ENTRY_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

char *
__STUMPLESS_NAME( EntryToString )( __STUMPLESS_NAME( Entry ) * );

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( GetDebugEntry )( void );

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( EntryForEvent )( __STUMPLESS_NAME( Event ) * );

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( GetErrorEntry )( void );

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( GetFatalEntry )( void );

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( GetInfoEntry )( void );

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( GetWarningEntry )( void );

__STUMPLESS_NAME( Entry ) *
__STUMPLESS_NAME( MergeEntries )
( __STUMPLESS_NAME( Entry ) *, __STUMPLESS_NAME( Entry ) * );

#endif
