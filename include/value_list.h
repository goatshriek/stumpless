#ifndef STUMPLESS_VALUE_LIST_H
#define STUMPLESS_VALUE_LIST_H

#include <stdio.h>

#include <types.h>

StumplessStatusCode
StumplessAppendToValueList( StumplessValueList *, StumplessValue * );

void
StumplessDestroyValueList( StumplessValueList * );

StumplessValueList *
StumplessNewValueList( void );

char *
StumplessValueListToString( StumplessValueList * );

StumplessStatusCode
StumplessWriteValueListToStream( FILE *, StumplessValueList * );

#endif
