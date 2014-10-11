#ifndef __STUMPLESS_PRIVATE_LIST_TARGET_H
#define __STUMPLESS_PRIVATE_LIST_TARGET_H

#include "private/type.h"

TargetList *
AddSeparatorToTargetList
( TargetList *, Target * );

TargetList *
AppendTargetLists
( TargetList *, TargetList * );

TargetList *
AppendToTargetList
( TargetList *, Target * );

TargetListIterator *
BeginTargetList
( TargetList * );

TargetListConstIterator *
CBeginTargetList
( const TargetList * );

TargetListConstIterator *
CEndTargetList
( const TargetList * );

TargetList *
CopyTargetList
( const TargetList * );

TargetListConstReverseIterator *
CRBeginTargetList
( const TargetList * );

TargetListConstReverseIterator *
CREndTargetList
( const TargetList * );

void
DestroyTargetList
( TargetList * );

TargetListIterator *
EndTargetList
( TargetList * );

Target *
TargetListBack
( const TargetList * );

unsigned short
TargetListContains
( const TargetList *, const Target * );

Target *
TargetListFront
( const TargetList * );

unsigned short
TargetListIsEmpty
( const TargetList * );

unsigned
TargetListSize
( const TargetList * );

Status *
LogToTargetList
( const TargetList *, const Record * );

TargetList *
NewTargetList
( void );

TargetList *
PrependToTargetList
( TargetList *, Target * );

TargetListReverseIterator *
RBeginTargetList
( TargetList * );

TargetListReverseIterator *
REndTargetList
( TargetList * );

#endif
