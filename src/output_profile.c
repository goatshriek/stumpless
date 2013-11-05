#include <stdlib.h>

#include "private/dictionary.h"
#include "private/output_profile.h"
#include "private/output_profile_initializer.h"
#include "private/status.h"
#include "private/type.h"

static Dictionary * profiles = NULL;

Status *
AddOutputProfile
( OutputProfile * profile )
{
  if( profile == NULL || profile->name == NULL )
    return NULL;
  
  if( profiles == NULL ){
    profiles = NewDictionary();
    
    if( profiles == NULL )
      return RaiseAbnormalStatus( "constructor failure" );
  }
  
  void * value = ( void * ) profile;
  if( SetDictionaryValue( profiles, profile->name, value ) == NULL )
    return NULL;
  
  return NULL;
}

OutputProfile *
FindOutputProfileByName
( const char * name )
{
  if( profiles == NULL ){
    profiles = NewDictionary();
    
    if( profiles == NULL )
      return NULL;
  }
  
  OutputProfile * profile = GetDictionaryValue( profiles, name );
  
  if( profile == NULL ){
    if( InitializeOutputProfileByName( name ) != NULL )
      return NULL;
    profile = GetDictionaryValue( profiles, name );
  }
  
  return profile;
}
