#ifndef __STUMPLESS_TYPE_DECLARATION_H
#define __STUMPLESS_TYPE_DECLARATION_H

struct Adapter;
struct AdapterList;
struct AdapterListIterator;
struct Boolean;
struct BooleanFormat;
struct ByteList;
struct Comparator;
struct ComparatorList;
struct ComparatorListIterator;
struct Configuration;
struct Dictionary;
struct Entry;
struct EntryAttribute;
struct EntryAttributeList;
struct EntryAttributeListIterator;
struct Event;
struct EventAttribute;
struct EventAttributeList;
struct EventAttributeListIterator;
struct FileConfiguration;
struct Filter;
struct FilterList;
struct FilterListIterator;
struct Formatter;
struct FormatterList;
struct FormatterListIterator;
struct Handler;
struct HandlerList;
struct HandlerListIterator;
struct HTTConfiguration;
enum HTTPMethod;
struct Level;
struct Log;
struct Logger;
struct Output;
struct OutputProfile;
struct Record;
struct RecordList;
struct Status;
struct SortingConfiguration;
enum SortingMethod;
struct StringConfiguration;
struct ThreadingConfiguration;
union Type;
struct Value;
struct ValueList;
struct ValueListIterator;
struct ValueProfile;


typedef struct Adapter Adapter;
typedef struct AdapterList AdapterList;
typedef struct AdapterListIterator AdapterListIterator;
typedef struct Boolean Boolean;
typedef struct BooleanFormat BooleanFormat;
typedef struct ByteList ByteList;
typedef struct Comparator Comparator;
typedef struct ComparatorList ComparatorList;
typedef struct ComparatorListIterator ComparatorListIterator;
typedef struct Configuration Configuration;
typedef struct Dictionary Dictionary;
typedef struct Entry Entry;
typedef struct EntryAttribute EntryAttribute;
typedef struct EntryAttributeList EntryAttributeList;
typedef struct EntryAttributeListIterator EntryAttributeListIterator;
typedef struct Event Event;
// and so on...
typedef struct EventAttribute;
typedef struct EventAttributeList;
typedef struct EventAttributeListIterator;
typedef struct FileConfiguration;
typedef struct Filter;
typedef struct FilterList;
typedef struct FilterListIterator;
typedef struct Formatter;
typedef struct FormatterList;
typedef struct FormatterListIterator;
typedef struct Handler;
typedef struct HandlerList;
typedef struct HandlerListIterator;
typedef struct HTTConfiguration;
typedef enum HTTPMethod;
typedef struct Level;
typedef struct Log;
typedef struct Logger;
typedef struct Output;
typedef struct OutputProfile;
typedef struct Record;
typedef struct RecordList;
typedef struct Status;
typedef struct SortingConfiguration;
typedef enum SortingMethod;
typedef struct StringConfiguration;
typedef struct ThreadingConfiguration;
typedef union Type;
typedef struct Value;
typedef struct ValueList;
typedef struct ValueListIterator;
typedef struct ValueProfile;




typedef enum __STUMPLESS_NAME( HTTPMethod )
        __STUMPLESS_NAME( HTTPMethod );
typedef enum __STUMPLESS_NAME( SortingMethod )
        __STUMPLESS_NAME( SortingMethod );

typedef struct __STUMPLESS_NAME( Adapter )
        __STUMPLESS_NAME( Adapter );
typedef struct __STUMPLESS_NAME( AdapterList )
        __STUMPLESS_NAME( AdapterList );
typedef struct __STUMPLESS_NAME( AdapterListIterator )
        __STUMPLESS_NAME( AdapterListIterator );
typedef struct __STUMPLESS_NAME( Boolean )
        __STUMPLESS_NAME( Boolean );
typedef struct __STUMPLESS_NAME( BooleanFormat )
        __STUMPLESS_NAME( BooleanFormat );
typedef struct __STUMPLESS_NAME( ByteList )
        __STUMPLESS_NAME( ByteList );
typedef struct __STUMPLESS_NAME( Comparator )
        __STUMPLESS_NAME( Comparator );
typedef struct __STUMPLESS_NAME( ComparatorList )
        __STUMPLESS_NAME( ComparatorList );
typedef struct __STUMPLESS_NAME( ComparatorListIterator )
        __STUMPLESS_NAME( ComparatorListIterator );
typedef struct __STUMPLESS_NAME( Configuration )
        __STUMPLESS_NAME( Configuration );
typedef struct __STUMPLESS_NAME( Dictionary )
        __STUMPLESS_NAME( Dictionary );
typedef struct __STUMPLESS_NAME( Entry )
        __STUMPLESS_NAME( Entry );
typedef struct __STUMPLESS_NAME( EntryAttribute )
        __STUMPLESS_NAME( EntryAttribute );
typedef struct __STUMPLESS_NAME( EntryAttributeList )
        __STUMPLESS_NAME( EntryAttributeList );
typedef struct __STUMPLESS_NAME( EntryAttributeListIterator )
        __STUMPLESS_NAME( EntryAttributeListIterator );
typedef struct __STUMPLESS_NAME( Event )
        __STUMPLESS_NAME( Event );
typedef struct __STUMPLESS_NAME( EventAttribute )
        __STUMPLESS_NAME( EventAttribute );
typedef struct __STUMPLESS_NAME( EventAttributeList )
        __STUMPLESS_NAME( EventAttributeList );
typedef struct __STUMPLESS_NAME( EventAttributeListIterator )
        __STUMPLESS_NAME( EventAttributeListIterator );
typedef struct __STUMPLESS_NAME( FileConfiguration )
        __STUMPLESS_NAME( FileConfiguration );
typedef struct __STUMPLESS_NAME( Filter )
        __STUMPLESS_NAME( Filter );
typedef struct __STUMPLESS_NAME( FilterList )
        __STUMPLESS_NAME( FilterList );
typedef struct __STUMPLESS_NAME( FilterListIterator )
        __STUMPLESS_NAME( FilterListIterator );
typedef struct __STUMPLESS_NAME( Formatter )
        __STUMPLESS_NAME( Formatter );
typedef struct __STUMPLESS_NAME( FormatterList )
        __STUMPLESS_NAME( FormatterList );
typedef struct __STUMPLESS_NAME( FormatterListIterator )
        __STUMPLESS_NAME( FormatterListIterator );
typedef struct __STUMPLESS_NAME( Handler )
        __STUMPLESS_NAME( Handler );
typedef struct __STUMPLESS_NAME( HandlerList )
        __STUMPLESS_NAME( HandlerList );
typedef struct __STUMPLESS_NAME( HandlerListIterator )
        __STUMPLESS_NAME( HandlerListIterator );
typedef struct __STUMPLESS_NAME( HTTPConfiguration )
        __STUMPLESS_NAME( HTTPConfiguration );
typedef struct __STUMPLESS_NAME( Level )
        __STUMPLESS_NAME( Level );
typedef struct __STUMPLESS_NAME( Log )
        __STUMPLESS_NAME( Log );
typedef struct __STUMPLESS_NAME( Logger )
        __STUMPLESS_NAME( Logger );
typedef struct __STUMPLESS_NAME( Output )
        __STUMPLESS_NAME( Output );
typedef struct __STUMPLESS_NAME( OutputProfile )
        __STUMPLESS_NAME( OutputProfile );
typedef struct __STUMPLESS_NAME( Record )
        __STUMPLESS_NAME( Record );
typedef struct __STUMPLESS_NAME( RecordList )
        __STUMPLESS_NAME( RecordList );
typedef struct __STUMPLESS_NAME( Status )
        __STUMPLESS_NAME( Status );
typedef struct __STUMPLESS_NAME( SortingConfiguration )
        __STUMPLESS_NAME( SortingConfiguration );
typedef struct __STUMPLESS_NAME( StringConfiguration )
        __STUMPLESS_NAME( StringConfiguration );
typedef struct __STUMPLESS_NAME( ThreadingConfiguration )
        __STUMPLESS_NAME( ThreadingConfiguration );
typedef union __STUMPLESS_NAME( Type )
        __STUMPLESS_NAME( Type );
typedef struct __STUMPLESS_NAME( Value )
        __STUMPLESS_NAME( Value );
typedef struct __STUMPLESS_NAME( ValueList )
        __STUMPLESS_NAME( ValueList );
typedef struct __STUMPLESS_NAME( ValueListIterator )
        __STUMPLESS_NAME( ValueListIterator );
typedef struct __STUMPLESS_NAME( ValueProfile )
        __STUMPLESS_NAME( ValueProfile );

typedef unsigned char
        __STUMPLESS_NAME( Byte );

#endif
