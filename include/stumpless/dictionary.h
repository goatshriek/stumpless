#ifndef __STUMPLESS_DICTIONARY_H
#define __STUMPLESS_DICIONTARY_H

#include <stumpless/type.h>

void
DestroyDictionary
( Dictionary * );

void *
GetDictionaryValue
( Dictionary *, const char * );

Dictionary *
NewDictionary
( void );

void *
RemoveDictionaryValue
( Dictionary *, const char * );

Dictionary *
SetDictionaryValue
( Dictionary *, const char *, void * );

#endif
