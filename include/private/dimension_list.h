#ifndef STUMPLESS_PRIVATE_DIMENSION_LIST_H
#define STUMPLESS_PRIVATE_DIMENSION_LIST_H

#include "private/type.h"

Status *
AppendToDimensionList
( DimensionList *, Dimension * );

Dimension *
BeginDimensionList
( DimensionList * );

DimensionList *
CopyDimensionList
( DimensionList * );

void
DestroyDimensionList
( DimensionList * );

unsigned short
DimensionListIsEmpty
( DimensionList * );

DimensionList *
MergeDimensionLists
( DimensionList *, DimensionList * );

DimensionList *
NewDimensionList
( void );

Dimension *
NextInDimensionList
( DimensionList * );

Status *
PrependToDimensionList
( DimensionList *, Dimension * );

#endif
