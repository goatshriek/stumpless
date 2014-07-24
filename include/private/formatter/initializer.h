#ifndef __STUMPLESS_PRIVATE_FORMATTER_INITIALIZER_H
#define __STUMPLESS_PRIVATE_FORMATTER_INITIALIZER_H

#include "private/type.h"

Formatter *
InitializeCSVFormatter
( void );

Status *
InitializeFormatterByName
( const char * );

Formatter *
InitializeTextFormatter
( void );

#endif
