#ifndef __STUMPLESS_FORMATTER_H
#define __STUMPLESS_FORMATTER_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AddFormatter )
( __STUMPLESS_NAME( Formatter ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendHandlerToFormatter )
( __STUMPLESS_NAME( Formatter ) *, __STUMPLESS_NAME( Handler ) * );

__STUMPLESS_NAME( Formatter ) *
__STUMPLESS_NAME( FindFormatterByName )
( const char * );

void *
__STUMPLESS_NAME( GetFormatterOption )
( const __STUMPLESS_NAME( Formatter ) *, const char * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( SetFormatterOption )
( __STUMPLESS_NAME( Formatter ) *, const char *, void * );

#endif
