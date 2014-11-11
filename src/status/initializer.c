#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/status.h"
#include "private/status/initializer.h"
#include "private/type.h"

#define ADD_STATUS( name, function )                                           \
SetDictionaryValue( initializers, name, Initialize##function##Status );

#define CREATE_STATUS                                                          \
Status *status = malloc( sizeof( Status ) );                                   \
if( !status )                                                                  \
  return NULL;

static Dictionary *initializers = NULL;

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
InitializeDictionaryFailureStatus
( void )
{
  CREATE_STATUS

  status->name = "dictionary failure";
  status->description = "an operation on an underlying dictionary structure has failedfrom either a memory allocation failure or a malformed dictionary state";
  status->error = 0;
  status->failure = 1;
  status->warning = 0;

  return status;
}

Status *
InitializeDuplicateStatus
( void )
{
  CREATE_STATUS

  status->name = "duplicate";
  status->description = "an attempt to add to a collection detected the same member already existing in the collection";
  status->error = 1;
  status->failure = 0;
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
InitializeEventFailureStatus
( void )
{
  CREATE_STATUS
 
  status->name = "event failure";
  status->description = "an Event could not be found";
  status->error = 1;
  status->failure = 1;
  status->warning = 0;

  return status;
}

Status *
InitializeForkFailureStatus
( void )
{
  CREATE_STATUS

  status->name = "fork failure";
  status->description = "a call to fork failed";
  status->error = 0;
  status->failure = 1;
  status->warning = 0;

  return status;
}

Status *
InitializeIncompatibleProfileStatus
( void )
{
  CREATE_STATUS

  status->name = "incompatible profile";
  status->description = "the profile of an object used for the request operation did not support the operation in question";
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
  status->description = "an operation on an underlying list structure has failed due to either a memory allocation failure or a malformed list structure";
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
InitializePipeFailureStatus
( void )
{
  CREATE_STATUS

  status->name = "pipe failure";
  status->description = "a call to pipe failed";
  status->error = 0;
  status->failure = 1;
  status->warning = 0;

  return status;
}

Status *
InitializeStatusByName
( const char * name )
{
  if( !initializers ){

    initializers = NewDictionary();
    if( !initializers )
      return NULL;

    ADD_STATUS( "constructor failure", ConstructorFailure )
    ADD_STATUS( "dictionary failure", DictionaryFailure )
    ADD_STATUS( "duplicate", Duplicate )
    ADD_STATUS( "empty argument", EmptyArgument )
    ADD_STATUS( "fork failure", ForkFailure )
    ADD_STATUS( "incompatible profile", IncompatibleProfile )
    ADD_STATUS( "list failure", ListFailure )
    ADD_STATUS( "malformed structure", MalformedStructure )
    ADD_STATUS( "memory allocation failure", MemoryAllocationFailure )
    ADD_STATUS( "pipe failure", PipeFailure )
    ADD_STATUS( "stream write failure", StreamWriteFailure )
    ADD_STATUS( "string write failure", StringWriteFailure )
    ADD_STATUS( "value profile not found", ValueProfileNotFound )
  }

  Status * ( *initializer )() = GetDictionaryValue( initializers, name );
  if( !initializer )
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
