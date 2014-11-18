#ifndef __STUMPLESS_FORMATTER_TEXT_H
#define __STUMPLESS_FORMATTER_TEXT_H

#include <stumpless/type.h>

Output *
ArrayValueToText
( const Formatter *formatter, const Value *value );

Output *
EventToText
( const Formatter *formatter, const Event *event );

Output *
EventAttributeToText
( const Formatter *formatter, const EventAttribute *attribute );

Output *
EventAttributesToText
( const Formatter *formatter, const Dictionary *attributes );

Output *
LevelToText
( const Formatter *formatter, const Level *level );

Output *
RecordToText
( const Formatter *formatter, const Record *record );

Output *
RecordAttributeToText
( const Formatter *formatter, const RecordAttribute *attribute );

Output *
RecordAttributesToText
( const Formatter *formatter, const Dictionary *attributes );

Output *
SingularValueToText
( const Formatter *formatter, const Value *value );

#endif
