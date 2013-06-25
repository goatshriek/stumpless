#ifndef STUMPLESS_PRIVATE_TYPE_H
#define STUMPLESS_PRIVATE_TYPE_H

#include <type.h>

typedef enum __NAME( HTTPMethod ) HTTPMethod;
typedef enum __NAME( SortingMethod ) SortingMethod;
typedef enum __NAME( StatusCode ) StatusCode;

typedef struct __NAME( Boolean ) Boolean;
typedef struct __NAME( BooleanFormat ) BooleanFormat;
typedef struct __NAME( ByteList ) ByteList;
typedef struct __NAME( Configuration ) Configuration;
typedef struct __NAME( Entry ) Entry;
typedef struct __NAME( EntryAttribute ) EntryAttribute;
typedef struct __NAME( Event ) Event;
typedef struct __NAME( EventAttribute ) EventAttribute;
typedef struct __NAME( FileConfiguration ) FileConfiguration;
typedef struct __NAME( FormattedOutput ) FormattedOutput;
typedef struct __NAME( HTTPConfiguration ) HTTPConfiguration;
typedef struct __NAME( Level ) Level;
typedef struct __NAME( LoggingProfile ) LoggingProfile;
typedef struct __NAME( OutputProfile ) OutputProfile;
typedef struct __NAME( Status ) Status;
typedef struct __NAME( SortingConfiguration ) SortingConfiguration;
typedef struct __NAME( StringConfiguration ) StringConfiguration;
typedef struct __NAME( ThreadingConfiguration ) ThreadingConfiguration;
typedef union __NAME( Type ) Type;
typedef struct __NAME( Value ) Value;
typedef struct __NAME( ValueList ) ValueList;
typedef struct __NAME( ValueListNode ) ValueListNode;
typedef struct __NAME( ValueProfile ) ValueProfile;

typedef unsigned char Byte;

#endif
