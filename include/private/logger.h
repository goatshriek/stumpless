#ifndef STUMPLESS_LOGGER_H
#define STUMPLESS_LOGGER_H

#include <type.h>

StumplessStatusCode StumplessLogDebug( const char * );
StumplessStatusCode StumplessLogError( const char * );
StumplessStatusCode StumplessLogFatal( const char * );
StumplessStatusCode StumplessLogInfo( const char * );
StumplessStatusCode StumplessLogWarning( const char * );

#endif
