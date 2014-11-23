#include <stumpless/logger.h>
#include <stumpless/logger/sender.h>

#include "private/type.h"

Status *
SendLoggerStatus
( Logger *logger )
{
  // sends the status to the check status function

  return NULL;
}

Status *
SendRecord
( Logger *logger, Record *record )
{
  // multiprocessing will call send to other process
  // logging process will be listening with Listen function

  return ProcessRecord( logger, record );
}
