#ifndef __STUMPLESS_TEST_FUNCTION_CONTAINER_DICTIONARY_CONST_ITERATOR_H
#define __STUMPLESS_TEST_FUNCTION_CONTAINER_DICTIONARY_CONST_ITERATOR_H

/**
 * @file
 * Functions for testing DictionaryConstIterators and the related functions.
 */

/**
 * Tests the CopyDictionaryConstIterator function.
 *
 * @test A NULL argument returns NULL. The Copy of a normal iterator has a
 * different address, but the same values for the Dictionary and current node.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestCopy
( void );

/**
 * Tests the DestroyDictionaryConstIterator function.
 *
 * @test A NULL argument simply returns. Destroying an iterator does not cause
 * any errors or faults.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestDestroy
( void );

/**
 * Tests the DictionaryConstIteratorHasNext function.
 *
 * @test If a NULL argument is passed, then a logically false value is returned.
 * An iterator at the beginning, the middle, or the end of its iteration returns
 * a logically true value. A finished iterator returns a logically false value.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestHasNext
( void );

/**
 * Tests the NewDictionaryConstIterator function.
 *
 * @test If a NULL argument is passed, then NULL must be returned. A non-NULL
 * value must be returned for a valid Dictionary. The Dictionary of the
 * iterator must be the same as the one used to create it, and the starting
 * point of the iterator must be the first entry in the dictionary.
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestNew
( void );

/**
 * Tests the NextInDictionaryConstIterator function.
 *
 * @test If a NULL iterator is passed, then a NULl must be returned. The
 * Dictionary must be walked in order by each successive call to
 * NextInDictionaryConstIterator, and NULL is returned when no values are left.
 *
 * @todo test a larger Dictionary than three entries
 *
 * @return NULL on completion, or a string describing the failure
 */
const char *
TestNext
( void );

#endif
