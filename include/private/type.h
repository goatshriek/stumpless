#ifndef STUMPLESS_PRIVATE_TYPE_H
#define STUMPLESS_PRIVATE_TYPE_H

#include <private_name.h>
#include <type.h>

typedef enum __STUMPLESS_NAME( HTTPMethod ) HTTPMethod;
typedef enum __STUMPLESS_NAME( SortingMethod ) SortingMethod;
typedef enum __STUMPLESS_NAME( StatusCode ) StatusCode;

typedef struct __STUMPLESS_NAME( Boolean ) Boolean;
typedef struct __STUMPLESS_NAME( BooleanFormat ) BooleanFormat;
typedef struct __STUMPLESS_NAME( ByteList ) ByteList;
typedef struct __STUMPLESS_NAME( Configuration ) Configuration;
typedef struct __STUMPLESS_NAME( Entry ) Entry;
typedef struct __STUMPLESS_NAME( EntryAttribute ) EntryAttribute;
typedef struct __STUMPLESS_NAME( Event ) Event;
typedef struct __STUMPLESS_NAME( EventAttribute ) EventAttribute;
typedef struct __STUMPLESS_NAME( FileConfiguration ) FileConfiguration;
typedef struct __STUMPLESS_NAME( FormattedOutput ) FormattedOutput;
typedef struct __STUMPLESS_NAME( HTTPConfiguration ) HTTPConfiguration;
typedef struct __STUMPLESS_NAME( Level ) Level;
typedef struct __STUMPLESS_NAME( LoggingProfile ) LoggingProfile;
typedef struct __STUMPLESS_NAME( OutputProfile ) OutputProfile;
typedef struct __STUMPLESS_NAME( Status ) Status;
typedef struct __STUMPLESS_NAME( SortingConfiguration ) SortingConfiguration;
typedef struct __STUMPLESS_NAME( StringConfiguration ) StringConfiguration;
typedef struct __STUMPLESS_NAME( ThreadingConfiguration ) ThreadingConfiguration;
typedef union __STUMPLESS_NAME( Type ) Type;
typedef struct __STUMPLESS_NAME( Value ) Value;
typedef struct __STUMPLESS_NAME( ValueList ) ValueList;
typedef struct __STUMPLESS_NAME( ValueListNode ) ValueListNode;
typedef struct __STUMPLESS_NAME( ValueProfile ) ValueProfile;

typedef unsigned char Byte;

#endif
