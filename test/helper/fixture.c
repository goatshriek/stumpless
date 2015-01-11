#include <stdlib.h>

#include <stumpless/exception.h>
#include <stumpless/formatter/text.h>
#include <stumpless/record.h>
#include <stumpless/value/constructor.h>

#include "private/output.h"
#include "test/helper.h"
#include "test/type.h"

Record *
BadAdaptFunction
( const Adapter *adapter, Record *record )
{
  TestLogSetLastAdapter( adapter );
  TestLogSetLastAdaptedRecord( record );

  return NULL;
}

Output *
BadFormatFunction
( const Formatter *formatter, const Record *record )
{
  TestLogSetLastFormatter( formatter );
  TestLogSetLastFormattedRecord( record );

  return NULL;
}

Exception *
BadHandleFunction
( const Handler *handler, const Output *output )
{
  TestLogSetLastHandler( handler );
  TestLogSetLastHandledOutput( output );

  return RaiseException( "malformed structure" );
}

Record *
TestAdaptFunction
( const Adapter *adapter, Record *record )
{
  if( !adapter || !record )
    return NULL;

  TestLogSetLastAdapter( adapter );
  TestLogSetLastAdaptedRecord( record );

  SetRecordAttribute( record, "test adapt function attribute", NewValueForString( "test attribute value" ) );

  return record;
}

Output *
TestFormatFunction
( const Formatter *formatter, const Record *record )
{
  Output *output;

  TestLogSetLastFormatter( formatter );
  TestLogSetLastFormattedRecord( record );

  output = RecordToText( formatter, record );
  TestLogSetLastGeneratedOutput( output );

  return output;
}

Exception *
TestHandleFunction
( const Handler *handler, const Output *output )
{
  TestLogSetLastHandler( handler );
  TestLogSetLastHandledOutput( output );
  TestLogSetLastMessage( OutputToString( output ) );

  return NULL;
}
