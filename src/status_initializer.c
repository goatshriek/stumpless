#include <stdlib.h>

#include "private/dictionary.h"
#include "private/status.h"
#include "private/status_initializer.h"
#include "private/type.h"

#define ADD_STATUS( name, function )                                           \
AddValueToDictionary( initializers, name, Initialize##function##Status );

#define CREATE_STATUS                                                          \
Status * status = malloc( sizeof( Status ) );                                  \
if( status == NULL )                                                           \
  return NULL;

static Dictionary * initializers = NULL;

Status *
InitializeConstructorFailureStatus
( void )
{
  CREATE_STATUS
  
  status->name = "constructor failure";
  status->description = "a call to a constructor has failed, perhaps resulting from a memory allocation failure or invalid argument";
  status->error = 0;
  status->failure = 1;
  status->warning = 0;
  
  return status;
}

Status *
InitializeEmptyArgumentStatus
( void )
{
  CREATE_STATUS
  
  status->name = "empty argument";
  status->description = "an argument required for the operation was either NULL or an empty structure";
  status->error = 1;
  status->failure = 0;
  status->warning = 0;
  
  return status;
}

Status *
InitializeListFailureStatus
( void )
{
  CREATE_STATUS
  
  status->name = "list failure";
  status->description = "an operation on an underlying list structure has failedfrom either a memory allocation failure or a malformed list structure";
  status->error = 0;
  status->failure = 1;
  status->warning = 0;
  
  return status;
}

Status *
InitializeMalformedStructureStatus
( void )
{
  CREATE_STATUS
  
  status->name = "malformed structure";
  status->description = "one of the internal structures is not properly formed, for example a length higher than an array size";
  status->error = 1;
  status->failure = 0;
  status->warning = 0;
  
  return status;
}

Status *
InitializeMemoryAllocationFailureStatus
( void )
{
  CREATE_STATUS
  
  status->name = "memory allocation failure";
  status->description = "a request for allocated memory was denied, likely meaning that there is none left";
  status->error = 0;
  status->failure = 1;
  status->warning = 0;
  
  return status;
}

Status *
InitializeStatusByName
( const char * name )
{
  if( initializers == NULL ){
    
    initializers = NewDictionary();
    if( initializers == NULL )
      return NULL;
    
    ADD_STATUS( "constructor failure", ConstructorFailure )
    ADD_STATUS( "empty argument", EmptyArgument )
    ADD_STATUS( "list failure", ListFailure )
    ADD_STATUS( "malformed structure", MalformedStructure )
    ADD_STATUS( "memory allocation failure", MemoryAllocationFailure )
    ADD_STATUS( "stream write failure", StreamWriteFailure )
    ADD_STATUS( "string write failure", StringWriteFailure )
    ADD_STATUS( "value profile not found", ValueProfileNotFound )
  }
  
  Status * ( *initializer )() = GetValueFromDictionary( initializers, name );
  if( initializer == NULL )
    return NULL;
  else 
    return AddStatus( initializer() );
}

Status *
InitializeStreamWriteFailureStatus
( void )
{
  CREATE_STATUS
  
  status->name = "stream write failure";
  status->description = "an attempt to write to a stream failed, error indicators may give more information";
  status->error = 0;
  status->failure = 1;
  status->warning = 0;
  
  return status;
}

Status *
InitializeStringWriteFailureStatus
( void )
{
  CREATE_STATUS
  
  status->name = "string write failure";
  status->description = "an attempt to write to a string failed, perhaps because the string was not large enough";
  status->error = 0;
  status->failure = 1;
  status->warning = 0;
  
  return status;
}

Status *
InitializeValueProfileNotFoundStatus
( void )
{
  CREATE_STATUS
  
  status->name = "value profile not found";
  status->description = "the value profile specified could not be found in the running list or in the default list, perhaps due to a misspelling";
  status->error = 1;
  status->failure = 0;
  status->warning = 0;
  
  return status;
}
