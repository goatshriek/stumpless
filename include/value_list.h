#ifndef STUMPLESS_VALUE_LIST_H
#define STUMPLESS_VALUE_LIST_H

#include <stdio.h>

#include <types.h>

StumplessStatusCode
StumplessAppendStringToValueList( StumplessValueList *, char * );

StumplessStatusCode
StumplessAppendUnsignedIntToValueList( StumplessValueList *, unsigned );

StumplessStatusCode
StumplessAppendValueListToValueList( StumplessValueList *,
                                     StumplessValueList * );

StumplessStatusCode
StumplessAppendValueToValueList( StumplessValueList *, StumplessValue * );

StumplessValueList *
StumplessCopyValueList( StumplessValueList * );

void
StumplessDestroyValueList( StumplessValueList * );

StumplessValueList *
StumplessNewValueList( void );

StumplessStatusCode
StumplessValueListIntoString( char *, StumplessValueList * );

short
StumplessValueListIsEmpty( StumplessValueList * );

char *
StumplessValueListToString( StumplessValueList * );

StumplessStatusCode
StumplessWriteAndDestroyValueList( FILE *, StumplessValueList * );

StumplessStatusCode
StumplessWriteValueListToStream( FILE *, StumplessValueList * );

#endif
