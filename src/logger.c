#include <stdlib.h>

#include "private/formatter.h"
#include "private/logger.h"
#include "private/status.h"
#include "private/type.h"

#include "private/list/adapter.h"
#include "private/list/formatter.h"

#include "private/list/iterator/formatter.h"

Status *
AppendAdapterToLogger
( Logger * logger, Adapter * adapter )
{
  if( !logger || !adapter )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( !logger->adapters ){
    logger->adapters = NewAdapterList();
    if( !logger->adapters )
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  if( AdapterListContains( logger->adapters, adapter ) )
    return RaiseAbnormalStatus( "duplicate" );
  
  if( !AppendToAdapterList( logger->adapters, adapter ) )
    return RaiseAbnormalStatus( "list failure " );
  
  return NULL;
}

Status *
AppendFormatterToLogger
( Logger * logger, Formatter * formatter )
{
  if( !logger || !formatter )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( !logger->formatters ){
    logger->formatters = NewFormatterList();
    if( !logger->formatters )
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  if( FormatterListContains( logger->formatters, formatter ) )
    return RaiseAbnormalStatus( "duplicate" );
  
  if( !AppendToFormatterList( logger->formatters, formatter ) )
    return RaiseAbnormalStatus( "list failure" );
  
  return NULL;
}

Status *
AppendHandlerToLogger
( Logger * logger, Handler * handler )
{
  if( !logger || !handler )
    return RaiseAbnormalStatus( "empty argument" );
  
  Formatter * formatter;
  FormatterListIterator * formatters = BeginFormatterList( logger->formatters );
  while( formatter = NextInFormatterListIterator( formatters ) ){
    if( !AppendHandlerToFormatter( formatter, handler ) )
      return RaiseAbnormalStatus( "list failure ");
  }
  
  return NULL;
}

Status *
CheckLoggerStatus
( Logger * logger )
{
  // the invocating process will call this function to check the
  // current status of a Logger, which will be the status of the last
  // logging attempt
  
  return NULL;
}

void
ListenForValues
( Logger * logger )
{
  // logging process calls this process, and returns when complete
  // a return will signify a fatal error which caused the logging to halt
  
  Value * value;
  Status * status;
  
  while( 1 ){
    value = ReceiveNextValue( logger );
    status = ProcessValue( logger, value );
  }
}

Status *
ProcessValue
( Logger * logger, Value * value )
{
  if( !logger || !value )
    return RaiseAbnormalStatus( "empty argument" );
  
  Entry * entry = ValueThroughAdapterList( logger->adapters, value );
  if( !entry )
    return RaiseAbnormalStatus( "list failure" );
  
  return EntryThroughFormatterList( logger->formatters, entry );
}

Value *
ReceiveNextValue
( Logger * logger )
{
  // this function listens for values sent to the logging process
  // from the invocating process
  
  return NULL;
}

Status *
SendLoggerStatus
( Logger * logger )
{
  // sends the status to the check status function
  
  return NULL;
}

Status *
SendValue
( Logger * logger, Value * value )
{
  // multiprocessing will call send to other process
  // logging process will be listening with Listen function
  
  return ProcessValue( logger, value );
}
