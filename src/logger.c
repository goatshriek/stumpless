#include <stdlib.h>

#include "private/logger.h"
#include "private/type.h"

void
ListenForValues
( Logger * logger )
{ 
  Value * value;
  Status * status;
  
  while( 1 ){
    value = ReceiveNextValue( logger );
    status = ProcessValue( logger, value );
    UpdateStatus( logger, status );
  }
}

Status *
ProcessValue
( Logger * logger, Value * value )
{
  // send to adapter
  // send to formatter
  // send to handler list
  
  return NULL;
}

Value *
ReceiveNextValue
( Logger * logger )
{
  return NULL;
}

Status *
SendValue
( Logger * logger, Value * value )
{
  return ProcessValue( logger, value );
}

void
UpdateStatus
( Logger * logger, Status * status )
{
  return;
}
