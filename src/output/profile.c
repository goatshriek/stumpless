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
  if( !profile || !profile->name )
    return NULL;

  if( !profiles ){
    profiles = NewDictionary();

    if( !profiles )
      return RaiseStatus( "constructor failure" );
  }

  void *value = ( void * ) profile;
  if( SetDictionaryValue( profiles, profile->name, value ) == NULL )
    return NULL;

  return NULL;
}

OutputProfile *
FindOutputProfileByName
( const char *name )
{
  if( !profiles ){
    profiles = NewDictionary();

    if( !profiles )
      return NULL;
  }

  OutputProfile *profile = GetDictionaryValue( profiles, name );

  if( !profile ){
    if( InitializeOutputProfileByName( name ) )
      return NULL;
    profile = GetDictionaryValue( profiles, name );
  }

  return profile;
}
