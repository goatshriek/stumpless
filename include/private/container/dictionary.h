#ifndef STUMPLESS_PRIVATE_CONTAINER_DICTIONARY_H
#define STUMPLESS_PRIVATE_CONTAINER_DICIONTARY_H

#include "private/type.h"

/**
 * Creates a new DictionaryConstIterator starting from the beginning of the
 * supplied Dictionary.
 *
 * @param dictionary the Dictionary to get an iterator for
 *
 * @return a new DictionaryConstIterator
 */
DictionaryConstIterator *
CBeginDictionary
( const Dictionary *dictionary );

void
DestroyDictionary
( Dictionary * );

/**
 * Checks the Dictionary to see if it's empty.
 *
 * @param dictionary the Dictionary to check
 *
 * @return a positive value if the Dictionary is empty, 0 otherwise
 */
unsigned short
DictionaryIsEmpty
( const Dictionary *dictionary );

void *
GetDictionaryValue
( Dictionary *, const char * );

/**
 * Combines the provided Dictionaries into the primary Dictionary. All keys
 * contained in either of the Dictionaries will be present in the final. Missing
 * keys are added to the primary if needed, and if both Dictionaries contain the
 * same key then the value from the primary is used. If one of the Dictionaries
 * is NULL or empty, then the other will be returned unchanged.
 *
 * @param primary the primary Dictionary
 * @param secondary the secondary Dictionary
 *
 * @return the combination of the two Dictionaries. This will be primary unless
 * it was NULL or empty, in which case secondary is returned.
 */
Dictionary *
MergeDictionaries
( Dictionary *primary, Dictionary *secondary );

Dictionary *
NewDictionary
();

/**
 * Removes the value associated with the provided key from the Dictionary. If
 * the value does not exist nothing is done.
 *
 * @param dictionary the Dictionary to remove the value from
 * @param key the key the value is associated with
 */
void *
RemoveDictionaryValue
( Dictionary *dictionary, const char *key );

Dictionary *
SetDictionaryValue
( Dictionary *, const char *, void * );

#endif
