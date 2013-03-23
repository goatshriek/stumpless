#ifndef STUMPLESS_VALUE_LIST_H
#define STUMPLESS_VALUE_LIST_H

#include <stdio.h>

#include <types.h>

StumplessStatusCode
StumplessAppendValueListToValueList( StumplessValueList *,
                                     StumplessValueList * );

StumplessStatusCode
StumplessAppendStringToValueList( StumplessValueList *, char * );

StumplessStatusCode
StumplessAppendUnsignedIntToValueList( StumplessValueList *, unsigned );

StumplessStatusCode
StumplessAppendValueToValueList( StumplessValueList *, StumplessValue * );

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
