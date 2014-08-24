#include <stumpless/config.h>

#ifdef __STUMPLESS_HAVE_TIME_H
# include <time.h>
#endif

#include "private/adapter/base.h"
#include "private/type.h"

// todo implement
Entry *
EntryThroughContextAdapter
( Entry *entry, Dictionary *options )
{
  return NULL;
}

// todo implement
Entry *
EntryThroughLevelAdapter
( Entry *entry, Dictionary *options )
{
  return NULL;
}


#ifdef __STUMPLESS_HAVE_TIME_H
// todo implement
Entry *
EntryThroughTimeAdapter
( Entry *entry, Dictionary *options )
{
  if( !entry )
    return NULL;
  
  
  
  return NULL;
}
#endif
