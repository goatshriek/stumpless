#ifndef __STUMPLESS_PRIVATE_OUTPUT_PROFILE_INITIALIZER_H
#define __STUMPLESS_PRIVATE_OUTPUT_PROFILE_INITIALIZER_H

#include "private/type.h"

OutputProfile *
InitializeOutputProfileByName
( const char * );

OutputProfile *
InitializeRawStringOutputProfile
( void );

OutputProfile *
InitializeTextOutputProfile
( void );

#endif
