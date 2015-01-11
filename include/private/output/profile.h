#ifndef __STUMPLESS_PRIVATE_OUTPUT_PROFILE_H
#define __STUMPLESS_PRIVATE_OUTPUT_PROFILE_H

#include "private/type.h"

Exception *
AddOutputProfile
( OutputProfile * );

OutputProfile *
FindOutputProfileByName
( const char * );

#endif
