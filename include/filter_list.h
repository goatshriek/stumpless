#ifndef __STUMPLESS_FILTER_LIST_H
#define __STUMPLESS_FILTER_LIST_H

#include <stdio.h>

#include <public_name.h>
#include <type.h>

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( AppendToFilterList )
( __STUMPLESS_NAME( FilterList ) *, __STUMPLESS_NAME( Filter ) * );

__STUMPLESS_NAME( Filter ) *
__STUMPLESS_NAME( BeginFilterList )
( __STUMPLESS_NAME( FilterList ) * );

__STUMPLESS_NAME( FilterList ) *
__STUMPLESS_NAME( CopyFilterList )
( __STUMPLESS_NAME( FilterList ) * );

void
__STUMPLESS_NAME( DestroyFilterList )
( __STUMPLESS_NAME( FilterList ) * );

__STUMPLESS_NAME( FilterList ) *
__STUMPLESS_NAME( NewFilterList )( void );

__STUMPLESS_NAME( Filter ) *
__STUMPLESS_NAME( NextInFilterList )
( __STUMPLESS_NAME( FilterList ) * );

__STUMPLESS_NAME( Status ) *
__STUMPLESS_NAME( PrependToFilterList )
( __STUMPLESS_NAME( FilterList ) *, __STUMPLESS_NAME( Filter ) * );

unsigned short
__STUMPLESS_NAME( FilterListIsEmpty )
( __STUMPLESS_NAME( FilterList ) * );

#endif
