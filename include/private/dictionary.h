#ifndef STUMPLESS_PRIVATE_DICTIONARY_H
#define STUMPLESS_PRIVATE_DICIONTARY_H

#include "private/type.h"

Dictionary *
AddValueToDictionary
( Dictionary *, char *, void * );

void
DestroyDictionary
( Dictionary * );

void *
GetValueFromDictionary
( Dictionary *, const char * );

Dictionary *
NewDictionary
();

Dictionary *
RemoveValueFromDictionary
( Dictionary *, const char * );

#endif
