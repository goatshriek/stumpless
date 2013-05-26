#ifndef STUMPLESS_VALUE_LIST_H
#define STUMPLESS_VALUE_LIST_H

#include <stdio.h>

#include <type.h>

StumplessStatusCode
StumplessAddSeparatorToValueList( StumplessValueList *, StumplessValue * );

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
StumplessPrependStringToValueList( StumplessValueList *, const char * );

StumplessStatusCode
StumplessPrependValueToValueList( StumplessValueList *, StumplessValue * );

StumplessStatusCode
StumplessValueListIntoString( char *, StumplessValueList * );

unsigned short
StumplessValueListIsEmpty( StumplessValueList * );

char *
StumplessValueListToString( StumplessValueList * );

StumplessValueList *
StumplessValueListToStrings( StumplessValueList * );

StumplessStatusCode // todo remove this function
StumplessWriteValueListToStream( FILE *, StumplessValueList * );

#endif
