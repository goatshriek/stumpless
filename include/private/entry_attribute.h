#ifndef __STUMPLESS_PRIVATE_ENTRY_ATTRIBUTE_H
#define __STUMPLESS_PRIVATE_ENTRY_ATTRIBUTE_H

#include "private/type.h"

void
DestroyEntryAttribute
( EntryAttribute * );

EntryAttribute *
EntryAttributeForEventAttribute
( const EventAttribute * );

#endif
