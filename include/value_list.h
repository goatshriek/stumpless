#ifndef STUMPLESS_VALUE_LIST_H
#define STUMPLESS_VALUE_LIST_H

#include <stdio.h>

#include <types.h>

StumplessStatusCode
StumplessAppendStringToValueList( StumplessValueList *, char * );

StumplessStatusCode
StumplessAppendToValueList( StumplessValueList *, StumplessValue * );

void
StumplessDestroyValueList( StumplessValueList * );

StumplessValueList *
StumplessNewValueList( void );

short
StumplessValueListIsEmpty( StumplessValueList * );

char *
StumplessValueListToString( StumplessValueList * );

StumplessStatusCode
StumplessWriteAndDestroyValueList( FILE *, StumplessValueList * );

StumplessStatusCode
StumplessWriteValueListToStream( FILE *, StumplessValueList * );

#endif
