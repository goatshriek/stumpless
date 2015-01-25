#include <stdlib.h>

#include <stumpless/config.h>
#include <stumpless/exception.h>
#include <stumpless/logger.h>

#ifdef __STUMPLESS_MULTIPROCESSING_ENABLED
# include <unistd.h>
# include <sys/types.h>
#endif

#include "private/container/dictionary.h"
#include "private/container/list/adapter.h"
#include "private/container/list/formatter.h"
#include "private/container/list/iterator/formatter.h"
#include "private/container/list/target.h"
#include "private/formatter.h"
#include "private/type.h"

static Dictionary *loggers = NULL;

Logger *
AppendAdapterToLogger
( Logger *logger, Adapter *adapter )
{
  return logger;
}

// todo refactor with append formatter to target list function
Logger *
AppendFormatterToLogger
( Logger *logger, Formatter *formatter )
{
  return NULL;
}

// todo refactor with new target data structure
Logger *
AppendHandlerToLogger
( Logger *logger, Handler *handler )
{
  return NULL;
}

Exception *
CheckLoggerException
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

  DestroyTargetList( logger->targets );

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

  Record *record;

  while( 1 ){
    ProcessRecord( logger, ReceiveNextRecord( logger ) );
  }
}

Logger *
NewLogger
( const char *name )
{
  Logger *logger;

  if( !name ){
    RaiseException( "empty argument" );
    return NULL;
  }

  if( !loggers ){
    loggers = NewDictionary();
    if( !loggers ){
      RaiseException( "constructor failure" );
      return NULL;
    }
  } else if( logger = GetDictionaryValue( loggers, name ) ){
      return logger;
  }

  logger = malloc( sizeof( Logger ) );
  if( !logger ){
    RaiseException( "memory allocation failure" );
    return NULL;
  }

  if( !SetDictionaryValue( loggers, name, logger ) ){
    RaiseException( "dictionary failure" );
    return NULL;
  }

  logger->name = name;

#ifdef __STUMPLESS_MULTIPROCESSING_ENABLED
  int pipes[2];
  if( pipe( pipes ) == -1 ){
    RaiseException( "pipe failure" );
    return NULL;
  }

  logger->receive_pipe = pipes[0];
  logger->send_pipe = pipes[1];

  pid_t process_id = fork();
  if( process_id == -1 ){
    RaiseException( "fork failure" );
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


// todo refactor to use new target structure in logger
Logger *
ProcessRecord
( Logger *logger, Record *record )
{
  return NULL;
}

Record *
ReceiveNextRecord
( Logger *logger )
{
  // this function listens for values sent to the logging process
  // from the invocating process

  return NULL;
}
