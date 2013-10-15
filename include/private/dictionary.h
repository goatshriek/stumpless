#ifndef STUMPLESS_PRIVATE_DICTIONARY_H
#define STUMPLESS_PRIVATE_DICIONTARY_H

#include "private/type.h"

Dictionary *
AddValueToDictionary
( Dictionary *, const char *, void * );

void
DestroyDictionary
( Dictionary * );

void *
GetValueFromDictionary
( Dictionary *, const char * );

Dictionary *
NewDictionary
();

void *
RemoveValueFromDictionary
( Dictionary *, const char * );

#endif
