#ifndef STUMPLESS_VALUE_LIST_H
#define STUMPLESS_VALUE_LIST_H

#include <stdio.h>

#include <type.h>

StumplessStatusCode
StumplessAppendStringToValueList( StumplessValueList *, const char * );

StumplessStatusCode
StumplessAppendUnsignedIntToValueList( StumplessValueList *, unsigned );

StumplessStatusCode
StumplessAppendValueLists( StumplessValueList *, StumplessValueList * );

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

unsigned short
StumplessValueListIsEmpty( StumplessValueList * );

char *
StumplessValueListToString( StumplessValueList * );

StumplessStatusCode
StumplessWriteAndDestroyValueList( FILE *, StumplessValueList * );

StumplessStatusCode
StumplessWriteValueListToStream( FILE *, StumplessValueList * );

#endif
