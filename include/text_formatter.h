#ifndef __STUMPLESS_TEXT_FORMATTER_H
#define __STUMPLESS_TEXT_FORMATTER_H

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( FormattedOutput ) *
__STUMPLESS_NAME( ArrayValueToText )
( __STUMPLESS_NAME( Value ) * );

__STUMPLESS_NAME( FormattedOutput ) *
__STUMPLESS_NAME( EntryToText )
( __STUMPLESS_NAME( Entry ) * );

__STUMPLESS_NAME( FormattedOutput ) *
__STUMPLESS_NAME( EntryAttributeToText )
( __STUMPLESS_NAME( EntryAttribute ) * );

__STUMPLESS_NAME( FormattedOutput ) *
__STUMPLESS_NAME( EntryAttributeListToText )
( __STUMPLESS_NAME( Entry ) * );

__STUMPLESS_NAME( FormattedOutput ) *
__STUMPLESS_NAME( EntrySummaryToText )
( __STUMPLESS_NAME( Entry ) * );

__STUMPLESS_NAME( FormattedOutput ) *
__STUMPLESS_NAME( EventToText )
( __STUMPLESS_NAME( Event ) * );

__STUMPLESS_NAME( FormattedOutput ) * 
__STUMPLESS_NAME( EventAttributeToText )
( __STUMPLESS_NAME( EventAttribute ) * );

__STUMPLESS_NAME( FormattedOutput ) *
__STUMPLESS_NAME( EventAttributeListToText )
( __STUMPLESS_NAME( Event ) * );

__STUMPLESS_NAME( FormattedOutput ) *
__STUMPLESS_NAME( EventSummaryToText )
( __STUMPLESS_NAME( Event ) * );

__STUMPLESS_NAME( FormattedOutput ) *
__STUMPLESS_NAME( LevelToText )
( __STUMPLESS_NAME( Level ) * );

__STUMPLESS_NAME( FormattedOutput ) *
__STUMPLESS_NAME( SingularValueToText )
( __STUMPLESS_NAME( Value ) * );

#endif
