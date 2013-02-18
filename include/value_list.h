#ifndef STUMPLESS_VALUE_LIST_H
#define STUMPLESS_VALUE_LIST_H

#include <types.h>

StumplessStatusCode
StumplessAppendToValueList( StumplessValueList *, StumplessValue * );

StumplessStatusCode
StumplessDestroyValueList( StumplessValueList * );

StumplessValueList *
StumplessGetNewValueList( void );

char *
StumplessValueListToString( StumplessValueList * );

#endif
