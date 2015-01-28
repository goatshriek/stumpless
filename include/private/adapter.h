#ifndef __STUMPLESS_PRIVATE_ADAPTER_H
#define __STUMPLESS_PRIVATE_ADAPTER_H

/**
 * @file
 * Functions for working with Adapters.
 */

#include "private/type.h"

/**
 * Runs a Record through the given Adapter. If the provided Adapter is NULL or
 * does not have an adapt function the Record is left unchanged.
 *
 * @param adapter the Adapter to run
 * @param record the Record to adapt
 *
 * @return record, or NULL if a problem is encountered
 */
Record *
AdaptRecord
( Adapter *adapter, Record *record );

Adapter *
AddAdapter
( Adapter * );

void
DestroyAdapter
( Adapter * );

Adapter *
FindAdapterByName
( const char * );

void *
GetAdapterOption
( const Adapter *, const char * );

Adapter *
SetAdapterOption
( Adapter *, const char *, void * );

#endif
