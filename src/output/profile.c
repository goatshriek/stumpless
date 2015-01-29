#include <stdlib.h>

#include <stumpless/exception.h>

#include "private/container/dictionary.h"
#include "private/output/profile.h"
#include "private/output/profile_initializer.h"
#include "private/type.h"

static Dictionary *profiles = NULL;

OutputProfile *
AddOutputProfile
( OutputProfile *profile )
{
  if( !profile || !profile->name )
    return profile;

  if( !profiles )
    profiles = NewDictionary();

  SetDictionaryValue( profiles, profile->name, ( void * )profile );

  return profile;
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

  if( !profile )
    return InitializeOutputProfileByName( name );

  return profile;
}
