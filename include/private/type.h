#ifndef __STUMPLESS_PRIVATE_TYPE_H
#define __STUMPLESS_PRIVATE_TYPE_H

#include "stumpless/public_name.h"
#include "stumpless/type.h"

struct Dimension;
struct List;
struct ListConstIterator;
struct ListConstReverseIterator;
struct ListIterator;
struct ListReverseIterator;
struct Stack;
struct Tree;

typedef struct Dimension
        Dimension;
typedef struct List
        List;
typedef struct ListConstIterator
        ListConstIterator;
typedef struct ListConstReverseIterator
        ListConstReverseIterator;
typedef struct ListIterator
        ListIterator;
typedef struct ListReverseIterator
        ListReverseIterator;
typedef struct Stack
        Stack;
typedef struct Tree
        Tree;

typedef __STUMPLESS_NAME( Byte )
        Byte;

typedef enum __STUMPLESS_NAME( HTTPMethod )
        HTTPMethod;
typedef enum __STUMPLESS_NAME( SortingMethod )
        SortingMethod;


typedef struct __STUMPLESS_NAME( Adapter )
        Adapter;
typedef struct __STUMPLESS_NAME( AdapterList )
        AdapterList;
typedef struct __STUMPLESS_NAME( AdapterListConstIterator )
        AdapterListConstIterator;
typedef struct __STUMPLESS_NAME( AdapterListConstReverseIterator )
        AdapterListConstReverseIterator;
typedef struct __STUMPLESS_NAME( AdapterListIterator )
        AdapterListIterator;
typedef struct __STUMPLESS_NAME( AdapterListReverseIterator )
        AdapterListReverseIterator;
typedef struct __STUMPLESS_NAME( Boolean )
        Boolean;
typedef struct __STUMPLESS_NAME( BooleanFormat )
        BooleanFormat;
typedef struct __STUMPLESS_NAME( ByteList )
        ByteList;
typedef struct __STUMPLESS_NAME( Comparator )
        Comparator;
typedef struct __STUMPLESS_NAME( ComparatorList )
        ComparatorList;
typedef struct __STUMPLESS_NAME( ComparatorListConstIterator )
        ComparatorListConstIterator;
typedef struct __STUMPLESS_NAME( ComparatorListConstReverseIterator )
        ComparatorListConstReverseIterator;
typedef struct __STUMPLESS_NAME( ComparatorListIterator )
        ComparatorListIterator;
typedef struct __STUMPLESS_NAME( ComparatorListReverseIterator )
        ComparatorListReverseIterator;
typedef struct __STUMPLESS_NAME( Configuration )
        Configuration;
typedef struct __STUMPLESS_NAME( Dictionary )
        Dictionary;
typedef struct __STUMPLESS_NAME( Entry )
        Entry;
typedef struct __STUMPLESS_NAME( EntryAttribute )
        EntryAttribute;
typedef struct __STUMPLESS_NAME( EntryAttributeList )
        EntryAttributeList;
typedef struct __STUMPLESS_NAME( EntryAttributeListConstIterator )
        EntryAttributeListConstIterator;
typedef struct __STUMPLESS_NAME( EntryAttributeListConstReverseIterator )
        EntryAttributeListConstReverseIterator;
typedef struct __STUMPLESS_NAME( EntryAttributeListIterator )
        EntryAttributeListIterator;
typedef struct __STUMPLESS_NAME( EntryAttributeListReverseIterator )
        EntryAttributeListReverseIterator;
typedef struct __STUMPLESS_NAME( Event )
        Event;
typedef struct __STUMPLESS_NAME( EventAttribute )
        EventAttribute;
typedef struct __STUMPLESS_NAME( EventAttributeList )
        EventAttributeList;
typedef struct __STUMPLESS_NAME( EventAttributeListConstIterator )
        EventAttributeListConstIterator;
typedef struct __STUMPLESS_NAME( EventAttributeListConstReverseIterator )
        EventAttributeListConstReverseIterator;
typedef struct __STUMPLESS_NAME( EventAttributeListIterator )
        EventAttributeListIterator;
typedef struct __STUMPLESS_NAME( EventAttributeListReverseIterator )
        EventAttributeListReverseIterator;
typedef struct __STUMPLESS_NAME( FileConfiguration )
        FileConfiguration;
typedef struct __STUMPLESS_NAME( Filter )
        Filter;
typedef struct __STUMPLESS_NAME( FilterList )
        FilterList;
typedef struct __STUMPLESS_NAME( FilterListConstIterator )
        FilterListConstIterator;
typedef struct __STUMPLESS_NAME( FilterListConstReverseIterator )
        FilterListConstReverseIterator;
typedef struct __STUMPLESS_NAME( FilterListIterator )
        FilterListIterator;
typedef struct __STUMPLESS_NAME( FilterListReverseIterator )
        FilterListReverseIterator;
typedef struct __STUMPLESS_NAME( Formatter )
        Formatter;
typedef struct __STUMPLESS_NAME( FormatterList )
        FormatterList;
typedef struct __STUMPLESS_NAME( FormatterListConstIterator )
        FormatterListConstIterator;
typedef struct __STUMPLESS_NAME( FormatterListConstReverseIterator )
        FormatterListConstReverseIterator;
typedef struct __STUMPLESS_NAME( FormatterListIterator )
        FormatterListIterator;
typedef struct __STUMPLESS_NAME( FormatterListReverseIterator )
        FormatterListReverseIterator;
typedef struct __STUMPLESS_NAME( Handler )
        Handler;
typedef struct __STUMPLESS_NAME( HandlerList )
        HandlerList;
typedef struct __STUMPLESS_NAME( HandlerListConstIterator )
        HandlerListConstIterator;
typedef struct __STUMPLESS_NAME( HandlerListConstReverseIterator )
        HandlerListConstReverseIterator;
typedef struct __STUMPLESS_NAME( HandlerListIterator )
        HandlerListIterator;
typedef struct __STUMPLESS_NAME( HandlerListReverseIterator )
        HandlerListReverseIterator;
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
typedef struct __STUMPLESS_NAME( ValueListConstIterator )
        ValueListConstIterator;
typedef struct __STUMPLESS_NAME( ValueListConstReverseIterator )
        ValueListConstReverseIterator;
typedef struct __STUMPLESS_NAME( ValueListIterator )
        ValueListIterator;
typedef struct __STUMPLESS_NAME( ValueListReverseIterator )
        ValueListReverseIterator;
typedef struct __STUMPLESS_NAME( ValueProfile )
        ValueProfile;

#endif
