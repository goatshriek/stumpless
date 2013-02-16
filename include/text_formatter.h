#ifndef STUMPLESS_TEXT_FORMATTER_H
#define STUMPLESS_TEXT_FORMATTER_H

#include <types.h>

StumplessFormattedOutput * StumplessEntryAsText( StumplessEntry * );
StumplessFormattedOutput * StumplessEventAsText( StumplessEvent * );
StumplessFormattedOutput * 
  StumplessEventAttributeAsText( StumplessEventAttribute * );
StumplessFormattedOutput * StumplessLevelAsText( StumplessLevel * );

#endif
