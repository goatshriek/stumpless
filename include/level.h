#ifndef STUMPLESS_LEVEL_H
#define STUMPLESS_LEVEL_H

#include <types.h>

StumplessLevel * StumplessGetDebugLevel( void );
StumplessLevel * StumplessGetErrorLevel( void );
StumplessLevel * StumplessGetFatalLevel( void );
StumplessLevel * StumplessGetInfoLevel( void );
StumplessLevel * StumplessGetWarningLevel( void );
char * StumplessLevelToString( StumplessLevel * );

#endif
