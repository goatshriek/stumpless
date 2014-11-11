#ifndef __STUMPLESS_PRIVATE_DICTIONARY_CONST_ITERATOR_H
#define __STUMPLESS_PRIVATE_DICTIONARY_CONST_ITERATOR_H

/**
 * @file
 * Functiones for creating and using DictionaryConstIterators. These are used
 * for iterating through the values stored in a Dictionary without changing them.
 */

#include "private/type.h"

/**
 * Creates a copy of the given iterator.
 *
 * @param iterator the DictionaryConstIterator to copy
 *
 * @return a copy of the given DictionaryConstIterator
 */
DictionaryConstIterator *
CopyDictionaryConstIterator
( const DictionaryConstIterator *iterator );

/**
 * Destroys a DictionaryConstIterator.
 *
 * @param iterator the DictionaryConstIterator to destroy
 */
void
DestroyDictionaryConstIterator
( DictionaryConstIterator *iterator );

/**
 * Checks to see if the iterator has any remaining values.
 *
 * @param iterator the DictionaryConstIterator to check
 *
 * @return a positive value if the iterator has a remaining value, zero
 * otherwise
 */
unsigned short
DictionaryConstIteratorHasNext
( const DictionaryConstIterator *iterator );

/**
 * Creates a new DictionaryConstIterator for the provided Dictionary.
 *
 * @todo implement position functionality
 *
 * @param dictionary the Dictionary to iterate through
 * @param position the position to start the iterator at
 *
 * @return a new DictionaryConstIterator for the Dictionary, or NULL on failure
 * or the Dictionary is empty
 */
DictionaryConstIterator *
NewDictionaryConstIterator
( const Dictionary *dictionary, int position );

/**
 * Gets the next value in the iterator.
 *
 * @param iterator the iterator to get the next value in
 *
 * @return the next value in the Dictionary, or NULL on failure or if no more
 * values exist
 */
const void *
NextInDictionaryConstIterator
( DictionaryConstIterator *iterator );

#endif
