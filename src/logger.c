#include <stdlib.h>

#include "private/adapter_list.h"
#include "private/formatter.h"
#include "private/formatter_list.h"
#include "private/logger.h"
#include "private/status.h"
#include "private/type.h"

Status *
AppendAdapterToLogger
( Logger * logger, Adapter * adapter )
{
  if( logger == NULL || adapter == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( logger->adapters == NULL ){
    logger->adapters = NewAdapterList();
    if( logger->adapters == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  if( AdapterListContains( logger->adapters, adapter ) )
    return RaiseAbnormalStatus( "duplicate" );
  
  return AppendToAdapterList( logger->adapters, adapter );
}

Status *
AppendFormatterToLogger
( Logger * logger, Formatter * formatter )
{
  if( logger == NULL || formatter == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( logger->formatters == NULL ){
    logger->formatters = NewFormatterList();
    if( logger->formatters == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  if( FormatterListContains( logger->formatters, formatter ) )
    return RaiseAbnormalStatus( "duplicate" );
  
  return AppendToFormatterList( logger->formatters, formatter );
}

Status *
AppendHandlerToLogger
( Logger * logger, Handler * handler )
{
  if( logger == NULL || handler == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  Status * status;
  Formatter * formatter = BeginFormatterList( logger->formatters );
  while( formatter == NULL ){
    status = AppendHandlerToFormatter( formatter, handler );
    if( status->failure )
      return status;
    
    formatter = NextInFormatterList( logger->formatters );
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
  if( logger == NULL || value == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  Entry * entry = ValueThroughAdapterList( logger->adapters, value );
  if( entry == NULL )
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
SendStatus
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
