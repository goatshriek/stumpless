#ifndef __STUMPLESS_TEST_HELPER_BUILDER_H
#define __STUMPLESS_TEST_HELPER_BUILDER_H

/**
 * @file
 * Functions for building test instances of structures.
 */

#include "private/type.h"

/**
 * Builds an Adapter. The adapt function is set to TestAdaptFunction.
 *
 * @return an Adapter, or NULL on failure
 */
Adapter *
BuildAdapter
( void );

AdapterList *
BuildAdapterList
( void );

/**
 * Builds an Adapter with an adapt function that fails. The adapt function is
 * set to BadAdaptFunction.
 *
 * @return an Adapter, or NULL on failure
 */
Adapter *
BuildBadAdapter
( void );

/**
 * Builds a Formatter with a format function that fails. The format function
 * is set to BadFormatFunction.
 *
 * @return a Formatter, or NULL on failure
 */
Formatter *
BuildBadFormatter
( void );

/**
 * Builds a Handler with a handle function that fails. The handle function is
 * set to BadHandleFunction.
 *
 * @return a Handler, or NULL on failure
 */
Handler *
BuildBadHandler
( void );

/**
 * Builds a Target that has format and handle functions that fail. The
 * Formatter is built using BuildBadFormatter and the Handler is built using
 * BuildBadHandler.
 */
Target *
BuildBadTarget
( void );

Boolean *
BuildBoolean
( void );

Value *
BuildBooleanValue
( void );

Output *
BuildByteOutput
( void );

Value *
BuildCharArrayValue
( void );

Comparator *
BuildComparator
( void );

ComparatorList *
BuildComparatorList
( void );

/**
 * Builds a const iterator for a Dictionary. The Dictionary of strings is used
 * to create the iterator.
 *
 * @return a new DictionaryConstIterator
 */
DictionaryConstIterator *
BuildDictionaryConstIterator
( void );

Dictionary *
BuildDictionaryOfEventAttributes
( void );

Dictionary *
BuildDictionaryOfRecordAttributes
( void );

Dictionary *
BuildDictionaryOfStrings
( void );

Record *
BuildEmptyRecord
( void );

Output *
BuildEmptyOutput
( void );

Value *
BuildEmptyUnsignedIntArrayValue
( void );

Value *
BuildEmptyValue
( void );

Record *
BuildRecord
( void );

RecordAttribute *
BuildRecordAttribute
( void );

Status *
BuildErrorStatus
( void );

Event *
BuildEvent
( void );

EventAttribute *
BuildEventAttribute
( void );

Status *
BuildFailureStatus
( void );

Filter *
BuildFilter
( void );

FilterList *
BuildFilterList
( void );

Formatter *
BuildFormatter
( void );

FormatterList *
BuildFormatterList
( void );

/**
 * Builds a Handler. The handle function is set to TestHandleFunction.
 *
 * @return a Handler, or NULL on failure
 */
Handler *
BuildHandler
( void );

HandlerList *
BuildHandlerList
( void );

Value *
BuildIntArrayValue
( void );

Value *
BuildIntValue
( void );

Level *
BuildLevel
( void );

/**
 * Creates a ListConstIterator for a list of strings.
 *
 * @return a ListConstIterator at the beginning of the list, or NULL on failure
 */
ListConstIterator *
BuildListConstIterator
( void );

/**
 * Creates a ListIterator for a list of strings.
 *
 * @return a ListIterator at the beginning of the list, or NULL on failure
 */
ListIterator *
BuildListIterator
( void );

List *
BuildListOfStrings
( void );

ListReverseIterator *
BuildListReverseIterator
( void );

/**
 * Creates a Logger with testing components.
 *
 * @return a Logger, or NULL on failure
 */
Logger *
BuildLogger
( void );

/**
 * Creates an Output.
 *
 * @return an Output, or NULL on failure
 */
Output *
BuildOutput
( void );

OutputProfile *
BuildOutputProfile
( void );

/**
 * Creates a Queue containing several strings.
 *
 * @return a Queue, or NULL on failure
 */
Queue *
BuildQueue
( void );

Output *
BuildRawStringOutput
( void );

Stack *
BuildStackOfStrings
( void );

Value *
BuildStringValue
( void );

/**
 * Builds a Target. The Formatter is created using BuildFormatter, and the
 * Handler using BuildHandler.
 *
 * @return a Target, or NULL on failure
 */
Target *
BuildTarget
( void );

/**
 * Builds a TargetList. The list consists of two Targets, the first created
 * using BuildTarget, and the second using BuildBadTarget.
 *
 * @return a TargetList, or NULL on failure
 */
TargetList *
BuildTargetList
( void );

Output *
BuildTextOutput
( void );

Tree *
BuildTreeOfStrings
( void );

Value *
BuildUnsignedIntValue
( void );

Value *
BuildUnsignedShortValue
( void );

Value *
BuildValue
( void );

ValueList *
BuildValueList
( void );

ValueList *
BuildValueListOfStrings
( void );

ValueProfile *
BuildValueProfile
( void );

Value *
BuildVoidValue
( void );

Status *
BuildWarningStatus
( void );

#endif
