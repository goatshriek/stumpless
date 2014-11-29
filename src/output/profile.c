#include <stdlib.h>

#include "private/container/dictionary.h"
#include "private/output/profile.h"
#include "private/output/profile_initializer.h"
#include "private/status.h"
#include "private/type.h"

static Dictionary *profiles = NULL;

Status *
AddOutputProfile
( OutputProfile *profile )
{
  void *value;

  if( !profile || !profile->name )
    return NULL;

  if( !profiles ){
    profiles = NewDictionary();

    if( !profiles )
      return RaiseStatus( "constructor failure" );
  }

  value = ( void * ) profile;
  if( !SetDictionaryValue( profiles, profile->name, value ) )
    return NULL;

  return NULL;
}

OutputProfile *
FindOutputProfileByName
( const char *name )
{
  OutputProfile *profile;

  if( !profiles ){
    profiles = NewDictionary();

    if( !profiles )
      return NULL;
  }

  profile = GetDictionaryValue( profiles, name );

  if( !profile ){
    if( InitializeOutputProfileByName( name ) )
      return NULL;
    profile = GetDictionaryValue( profiles, name );
  }

  return profile;
}
