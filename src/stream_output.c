#include <stdio.h>
#include <stdlib.h>

#include "private/status.h"
#include "private/stream_output.h"
#include "private/type.h"

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
  ValueListNode * node = list->first;
  while( node != NULL ){
    if( node->value == NULL || node->value->data == NULL )
      return RaiseAbnormalStatus( "malformed structure" );
  
    if( fputs( node->value->data->c_p, stream ) < 0 )
      return RaiseAbnormalStatus( "stream write failure" );
    
    node = node->next;
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
