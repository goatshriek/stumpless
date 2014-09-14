#include <stumpless/config.h>

#ifdef __STUMPLESS_HAVE_TIME_H
# include <time.h>
#endif

#include "private/adapter/base.h"
#include "private/type.h"

// todo implement
Record *
RecordThroughContextAdapter
( Record *record, Dictionary *options )
{
  return NULL;
}

// todo implement
Record *
RecordThroughLevelAdapter
( Record *record, Dictionary *options )
{
  return NULL;
}


#ifdef __STUMPLESS_HAVE_TIME_H
// todo implement
Record *
RecordThroughTimeAdapter
( Record *record, Dictionary *options )
{
  if( !record )
    return NULL;
  
  
  
  return NULL;
}
#endif
