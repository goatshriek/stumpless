#ifndef STUMPLESS_LEVELS_H
#define STUMPLESS_LEVELS_H

#include <types.h>

StumplessLevel * StumplessGetDebugLevel( void );
StumplessLevel * StumplessGetErrorLevel( void );
StumplessLevel * StumplessGetFatalLevel( void );
StumplessLevel * StumplessGetInfoLevel( void );
StumplessLevel * StumplessGetWarningLevel( void );

#endif
