#ifndef __STUMPLESS_DICTIONARY_H
#define __STUMPLESS_DICIONTARY_H

#include <public_name.h>
#include <type.h>

void
__STUMPLESS_NAME( DestroyDictionary )
( __STUMPLESS_NAME( Dictionary ) * );

void *
__STUMPLESS_NAME( GetDictionaryValue )
( __STUMPLESS_NAME( Dictionary ) *, const char * );

__STUMPLESS_NAME( Dictionary ) *
__STUMPLESS_NAME( NewDictionary )
();

void *
__STUMPLESS_NAME( RemoveDictionaryValue )
( __STUMPLESS_NAME( Dictionary ) *, const char * );

__STUMPLESS_NAME( Dictionary ) *
__STUMPLESS_NAME( SetDictionaryValue )
( __STUMPLESS_NAME( Dictionary ) *, const char *, void * );

#endif
