#ifndef __STUMPLESS_PRIVATE_FORMATTER_INITIALIZER_H
#define __STUMPLESS_PRIVATE_FORMATTER_INITIALIZER_H

#include "private/type.h"

Formatter *
InitializeCSVFormatter
( void );

Exception *
InitializeFormatterByName
( const char * );

Formatter *
InitializeTextFormatter
( void );

#endif
