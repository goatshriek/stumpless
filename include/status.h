#ifndef STUMPLESS_STATUS_H
#define STUMPLESS_STATUS_H

#include <type.h>

StumplessStatus *
StumplessAddStatus( StumplessStatus * );

StumplessStatus *
StumplessFindStatusByName( const char * );

StumplessStatus *
StumplessInitializeStatus( void );

StumplessStatus *
StumplessGetLastError( void );

StumplessStatus *
StumplessGetLastFailure( void );

// todo remove
const char *
StumplessStatusToString( StumplessStatusCode );

#endif
