#ifndef __STUMPLESS_PUBLIC_NAME_H
#define __STUMPLESS_PUBLIC_NAME_H

#include <config.h>

#define __STUMPLESS_NAME( name ) __STUMPLESS_EXPAND( NMSPC, name )
#define __STUMPLESS_EXPAND( prefix, name ) __STUMPLESS_CONCAT( prefix, name )
#define __STUMPLESS_CONCAT( prefix, name ) prefix ## name

#endif
