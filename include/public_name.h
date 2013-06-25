#ifndef STUMPLESS_PUBLIC_NAME_H
#define STUMPLESS_PUBLIC_NAME_H

#include <config.h>

#define __NAME( name ) __EXPAND( NMSPC, name )
#define __EXPAND( prefix, name ) __CONCATENATE( prefix, name )
#define __CONCATENATE( prefix, name ) prefix ## name

#endif
