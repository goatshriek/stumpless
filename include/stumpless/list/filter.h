#ifndef __STUMPLESS_LIST_FILTER_LIST_H
#define __STUMPLESS_LIST_FILTER_LIST_H

#include <stumpless/public_name.h>
#include <stumpless/type.h>

__STUMPLESS_NAME( FilterList ) *
__STUMPLESS_NAME( AddSeparatorToFilterList )
( __STUMPLESS_NAME( FilterList ) *, __STUMPLESS_NAME( Filter ) * );

__STUMPLESS_NAME( FilterList ) *
__STUMPLESS_NAME( AppendFilterLists )
( __STUMPLESS_NAME( FilterList ) *, __STUMPLESS_NAME( FilterList ) * );

__STUMPLESS_NAME( FilterList ) *
__STUMPLESS_NAME( AppendToFilterList )
( __STUMPLESS_NAME( FilterList ) *, __STUMPLESS_NAME( Filter ) * );

__STUMPLESS_NAME( FilterList ) *
__STUMPLESS_NAME( CopyFilterList )
( __STUMPLESS_NAME( FilterList ) * );

void
__STUMPLESS_NAME( DestroyFilterList )
( __STUMPLESS_NAME( FilterList ) * );

unsigned short
__STUMPLESS_NAME( EntryThroughFilterList )
( __STUMPLESS_NAME( FilterList ) *, __STUMPLESS_NAME( Entry ) * );

unsigned short
__STUMPLESS_NAME( FilterListContains )
( __STUMPLESS_NAME( FilterList ) *, __STUMPLESS_NAME( Filter ) * );

unsigned short
__STUMPLESS_NAME( FilterListIsEmpty )
( __STUMPLESS_NAME( FilterList ) * );

unsigned
__STUMPLESS_NAME( FilterListSize )
( const __STUMPLESS_NAME( FilterList ) * );

__STUMPLESS_NAME( FilterList ) *
__STUMPLESS_NAME( NewFilterList )
( void );

unsigned short
__STUMPLESS_NAME( OutputThroughFilterList )
( __STUMPLESS_NAME( FilterList ) *, __STUMPLESS_NAME( Output ) * );

__STUMPLESS_NAME( FilterList ) *
__STUMPLESS_NAME( PrependToFilterList )
( __STUMPLESS_NAME( FilterList ) *, __STUMPLESS_NAME( Filter ) * );

unsigned short
__STUMPLESS_NAME( ValueThroughFilterList )
( __STUMPLESS_NAME( FilterList ) *, __STUMPLESS_NAME( Value ) * );

#endif
