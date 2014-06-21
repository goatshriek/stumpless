#ifndef STUMPLESS_PRIVATE_DICTIONARY_H
#define STUMPLESS_PRIVATE_DICIONTARY_H

#include "private/type.h"

void
DestroyDictionary
( Dictionary * );

void *
GetDictionaryValue
( Dictionary *, const char * );

Dictionary *
NewDictionary
();

void *
RemoveDictionaryValue
( Dictionary *, const char * );

Dictionary *
SetDictionaryValue
( Dictionary *, const char *, void * );

#endif
