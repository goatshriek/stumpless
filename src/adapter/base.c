#include <stumpless/config.h>

#ifdef __STUMPLESS_HAVE_TIME_H
# include <time.h>
#endif

#include "private/adapter/base.h"
#include "private/type.h"

// todo implement
Record *
RecordThroughContextAdapter
( const Adapter *adapter, Record *record )
{
  return NULL;
}

// todo implement
Record *
RecordThroughLevelAdapter
( const Adapter *adapter, Record *record )
{
  return NULL;
}


#ifdef __STUMPLESS_HAVE_TIME_H
// todo implement
Record *
RecordThroughTimeAdapter
( const Adapter *adapter, Record *record )
{
  if( !record )
    return NULL;
  
  
  
  return NULL;
}
#endif
