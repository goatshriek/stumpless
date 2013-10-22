#include <stdio.h>
#include <stdlib.h>

#include "private/status.h"
#include "private/stream_handler.h"
#include "private/type.h"
#include "private/value_list.h"

Status *
BinaryOutputIntoStream
( Output * output, FILE * stream )
{
  // todo need to implement
  
  return NULL;
}

Status *
CSVOutputIntoStream
( Output * output, FILE * stream )
{
  // todo need to implement
  
  return NULL;
}

Status *
JSONOutputIntoStream
( Output * output, FILE * stream )
{
  // todo need to implement
  
  return NULL;
}

Status *
RawStringOutputIntoStream
( Output * output, FILE * stream )
{
  if( output == NULL || stream == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( output->data == NULL || output->data->c_p == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  if( fputs( output->data->c_p, stream ) < 0 )
    return RaiseAbnormalStatus( "stream write failure" );
  
  return NULL;
}

Status *
TextOutputIntoStream
( Output * output, FILE * stream )
{
  if( output == NULL || stream == NULL )
    return RaiseAbnormalStatus( "empty argument" );
  
  if( output->data == NULL || output->data->v_p == NULL )
    return RaiseAbnormalStatus( "malformed structure" );
  
  ValueList * list = ( ValueList * ) output->data->v_p;
  Value * value = BeginValueList( list );
  while( value != NULL ){
    if( value->data == NULL )
      return RaiseAbnormalStatus( "malformed structure" );
  
    if( fputs( value->data->c_p, stream ) < 0 )
      return RaiseAbnormalStatus( "stream write failure" );
    
    value = NextInValueList( list );
  }
  
  return NULL;
}

Status *
XMLOutputIntoStream
( Output * output, FILE * stream )
{
  // todo need to implement
  
  return NULL;
}
