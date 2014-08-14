#include <stdlib.h>
#include <stumpless/config.h>

#ifdef __STUMPLESS_MULTIPROCESSING_ENABLED
# include <unistd.h>
# include <sys/types.h>
#endif

#include "private/container/dictionary.h"
#include "private/container/list/adapter.h"
#include "private/container/list/formatter.h"
#include "private/container/list/iterator/formatter.h"
#include "private/formatter.h"
#include "private/logger.h"
#include "private/status.h"
#include "private/type.h"

static Dictionary *loggers = NULL;

Status *
AppendAdapterToLogger
( Logger *logger, Adapter *adapter )
{
  if( !logger || !adapter )
    return RaiseStatus( "empty argument" );

  if( !logger->adapters ){
    logger->adapters = NewAdapterList();
    if( !logger->adapters )
      return RaiseStatus( "constructor failure" );
  }

  if( AdapterListContains( logger->adapters, adapter ) )
    return RaiseStatus( "duplicate" );

  if( !AppendToAdapterList( logger->adapters, adapter ) )
    return RaiseStatus( "list failure " );

  return NULL;
}

Status *
AppendFormatterToLogger
( Logger *logger, Formatter *formatter )
{
  if( !logger || !formatter )
    return RaiseStatus( "empty argument" );

  if( !logger->formatters ){
    logger->formatters = NewFormatterList();
    if( !logger->formatters )
      return RaiseStatus( "constructor failure" );
  }

  if( FormatterListContains( logger->formatters, formatter ) )
    return RaiseStatus( "duplicate" );

  if( !AppendToFormatterList( logger->formatters, formatter ) )
    return RaiseStatus( "list failure" );

  return NULL;
}

// todo refactor with new path data structure
Status *
AppendHandlerToLogger
( Logger *logger, Handler *handler )
{
  if( !logger || !handler )
    return RaiseStatus( "empty argument" );

  Formatter *formatter;
  FormatterListIterator *formatters = BeginFormatterList( logger->formatters );
  while( formatter = NextInFormatterListIterator( formatters ) ){
    //if( !AppendHandlerToFormatter( formatter, handler ) )
      return RaiseStatus( "list failure ");
  }

  return NULL;
}

Status *
CheckLoggerStatus
( Logger *logger )
{
  // the invocating process will call this function to check the
  // current status of a Logger, which will be the status of the last
  // logging attempt

  return NULL;
}

void
DestroyLogger
( Logger *logger )
{
  if( !logger )
    return;

  DestroyAdapterList( logger->adapters );
  DestroyFormatterList( logger->formatters );

#ifdef __STUMPLESS_MULTIPROCESSING_ENABLED
// todo send destroy command through pipe
#endif

  free( logger );

  return;
}

void
Listen
( Logger *logger )
{
  // logging process calls this function
  // a return will signify a fatal error which caused the logging to halt

  Value *value;
  Status *status;

  while( 1 ){
    value = ReceiveNextValue( logger );
    status = ProcessValue( logger, value );
  }
}

Logger *
NewLogger
( const char *name )
{
  if( !name ){
    RaiseStatus( "empty argument" );
    return NULL;
  }

  Logger *logger;

  if( !loggers ){
    loggers = NewDictionary();
    if( !loggers ){
      RaiseStatus( "constructor failure" );
      return NULL;
    }
  } else if( logger = GetDictionaryValue( loggers, name ) ){
      return logger;
  }

  logger = malloc( sizeof( Logger ) );
  if( !logger ){
    RaiseStatus( "memory allocation failure" );
    return NULL;
  }

  if( !SetDictionaryValue( loggers, name, logger ) ){
    RaiseStatus( "dictionary failure" );
    return NULL;
  }

  logger->name = name;

#ifdef __STUMPLESS_MULTIPROCESSING_ENABLED
  int pipes[2];
  if( pipe( pipes ) == -1 ){
    RaiseStatus( "pipe failure" );
    return NULL;
  }

  logger->receive_pipe = pipes[0];
  logger->send_pipe = pipes[1];

  pid_t process_id = fork();
  if( process_id == -1 ){
    RaiseStatus( "fork failure" );
    return NULL;
  }

  if( process_id == 0 ){
    close( logger->send_pipe );
    Listen( logger );
  } else {
    close( logger->receive_pipe );
  }
#endif

  return logger;
}


// todo refactor to use new path structure in logger
Status *
ProcessValue
( Logger *logger, Value *value )
{
  if( !logger || !value )
    return RaiseStatus( "empty argument" );

  Entry *entry = ValueThroughAdapterList( logger->adapters, value );
  if( !entry )
    return RaiseStatus( "list failure" );

  return NULL;
}

Value *
ReceiveNextValue
( Logger *logger )
{
  // this function listens for values sent to the logging process
  // from the invocating process

  return NULL;
}

Status *
SendLoggerStatus
( Logger *logger )
{
  // sends the status to the check status function

  return NULL;
}
