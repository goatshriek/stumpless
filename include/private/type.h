#ifndef STUMPLESS_PRIVATE_TYPE_H
#define STUMPLESS_PRIVATE_TYPE_H

#include <public_name.h>
#include <type.h>

struct Dictionary;

typedef struct Dictionary
        Dictionary;

typedef __STUMPLESS_NAME( Byte )
        Byte;

typedef enum __STUMPLESS_NAME( HTTPMethod )
        HTTPMethod;
typedef enum __STUMPLESS_NAME( SortingMethod )
        SortingMethod;

typedef struct __STUMPLESS_NAME( Adapter )
        Adapter;
typedef struct __STUMPLESS_NAME( Boolean )
        Boolean;
typedef struct __STUMPLESS_NAME( BooleanFormat )
        BooleanFormat;
typedef struct __STUMPLESS_NAME( ByteList )
        ByteList;
typedef struct __STUMPLESS_NAME( Configuration )
        Configuration;
typedef struct __STUMPLESS_NAME( Entry )
        Entry;
typedef struct __STUMPLESS_NAME( EntryAttribute )
        EntryAttribute;
typedef struct __STUMPLESS_NAME( Event )
        Event;
typedef struct __STUMPLESS_NAME( EventAttribute )
        EventAttribute;
typedef struct __STUMPLESS_NAME( FileConfiguration )
        FileConfiguration;
typedef struct __STUMPLESS_NAME( Filter )
        Filter;
typedef struct __STUMPLESS_NAME( Formatter )
        Formatter;
typedef struct __STUMPLESS_NAME( Handler )
        Handler;
typedef struct __STUMPLESS_NAME( HTTPConfiguration )
        HTTPConfiguration;
typedef struct __STUMPLESS_NAME( Level )
        Level;
typedef struct __STUMPLESS_NAME( Logger )
        Logger;
typedef struct __STUMPLESS_NAME( Output )
        Output;
typedef struct __STUMPLESS_NAME( OutputProfile )
        OutputProfile;
typedef struct __STUMPLESS_NAME( Status )
        Status;
typedef struct __STUMPLESS_NAME( SortingConfiguration )
        SortingConfiguration;
typedef struct __STUMPLESS_NAME( StringConfiguration )
        StringConfiguration;
typedef struct __STUMPLESS_NAME( ThreadingConfiguration )
        ThreadingConfiguration;
typedef union __STUMPLESS_NAME( Type )
        Type;
typedef struct __STUMPLESS_NAME( Value )
        Value;
typedef struct __STUMPLESS_NAME( ValueList )
        ValueList;
typedef struct __STUMPLESS_NAME( ValueProfile )
        ValueProfile;

#endif
