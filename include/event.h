#ifndef STUMPLESS_EVENT_H
#define STUMPLESS_EVENT_H

#include <types.h>

char * StumplessEventToString( StumplessEvent * );
StumplessEvent * StumplessGetDebugEvent( void );
StumplessEvent * StumplessGetErrorEvent( void );
StumplessEvent * StumplessEventForLevel( StumplessLevel * );
StumplessEvent * StumplessGetFatalEvent( void );
StumplessEvent * StumplessGetInfoEvent( void );
StumplessEvent * StumplessGetWarningEvent( void );

#endif
