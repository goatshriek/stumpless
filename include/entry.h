#ifndef STUMPLESS_ENTRY_H
#define STUMPLESS_ENTRY_H

#include <types.h>

char * StumplessEntryToString( StumplessEntry * );
StumplessEntry * StumplessGetDebugEntry( void );
StumplessEntry * StumplessEntryForEvent( StumplessEvent * );
StumplessEntry * StumplessGetErrorEntry( void );
StumplessEntry * StumplessGetFatalEntry( void );
StumplessEntry * StumplessGetInfoEntry( void );
StumplessEntry * StumplessGetWarningEntry( void );

#endif
