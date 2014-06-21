#ifndef __STUMPLESS_OUTPUT_PROFILE_H
#define __STUMPLESS_OUTPUT_PROFILE_H

#include <stumpless/type.h>

Status *
AddOutputProfile
( OutputProfile * );

OutputProfile *
FindOutputProfileByName
( const char * );

#endif
