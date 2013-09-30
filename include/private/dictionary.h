#ifndef STUMPLESS_PRIVATE_DICTIONARY_H
#define STUMPLESS_PRIVATE_DICIONTARY_H

Status *
AddValueToDictionary
( Dictionary *, const char *, const void * );

void
DestroyDictionary
( Dictionary * );

void *
GetValueFromDictionary
( Dictionary *, const char * );

Dictionary *
NewDictionary
();

Status *
RemoveValueFromDictionary
( Dictionary *, const char * );

#endif
