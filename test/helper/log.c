#include <stdlib.h>

#include "test/helper/log.h"
#include "test/type.h"

static TestLog *log = NULL;

TestLog *
InitializeTestLog
( void )
{
  if( !log ){
    log = malloc( sizeof( TestLog ) );
    if( !log )
      return NULL;
  }

  log->last_adapted_record = NULL;
  log->last_adapter = NULL;
  log->last_formatted_record = NULL;
  log->last_formatter = NULL;
  log->last_generated_output = NULL;

  return log;
}

const Record *
TestLogGetLastAdaptedRecord
( void )
{
  if( !log )
    return NULL;

  return log->last_adapted_record;
}

const Adapter *
TestLogGetLastAdapter
( void )
{
  if( !log )
    return NULL;

  return log->last_adapter;
}

const Record *
TestLogGetLastFormattedRecord
( void )
{
  if( !log )
    return NULL;

  return log->last_formatted_record;
}

const Formatter *
TestLogGetLastFormatter
( void )
{
  if( !log )
    return NULL;

  return log->last_formatter;
}

const Output *
TestLogGetLastGeneratedOutput
( void )
{
  if( !log )
    return NULL;

  return log->last_generated_output;
}

const Output *
TestLogGetLastHandledOutput
( void )
{
  if( !log )
    return NULL;

  return log->last_handled_output;
}

const Handler *
TestLogGetLastHandler
( void )
{
  if( !log )
    return NULL;

  return log->last_handler;
}

const char *
TestLogGetLastMessage
( void )
{
  if( !log )
    return NULL;

  return log->last_message;
}

TestLog *
TestLogSetLastAdaptedRecord
( const Record *record )
{
  if( !log ){
    InitializeTestLog();
    if( !log )
      return NULL;
  }

  if( record )
    log->last_adapted_record = record;

  return log;
}

TestLog *
TestLogSetLastAdapter
( const Adapter *adapter )
{
  if( !log ){
    InitializeTestLog();
    if( !log )
      return NULL;
  }

  if( adapter )
    log->last_adapter = adapter;

  return log;
}

TestLog *
TestLogSetLastFormattedRecord
( const Record *record )
{
  if( !log ){
    InitializeTestLog();
    if( !log )
      return NULL;
  }

  if( record )
    log->last_formatted_record = record;

  return log;
}

TestLog *
TestLogSetLastFormatter
( const Formatter *formatter )
{
  if( !log ){
    InitializeTestLog();
    if( !log )
      return NULL;
  }

  if( formatter )
    log->last_formatter = formatter;

  return log;
}

TestLog *
TestLogSetLastGeneratedOutput
( const Output *output )
{
  if( !log ){
    InitializeTestLog();
    if( !log )
      return NULL;
  }

  if( output )
    log->last_generated_output = output;

  return log;
}

TestLog *
TestLogSetLastHandledOutput
( const Output *output )
{
  if( !log ){
    InitializeTestLog();
    if( !log )
      return NULL;
  }

  if( output )
    log->last_handled_output = output;

  return log;
}

TestLog *
TestLogSetLastHandler
( const Handler *handler )
{
  if( !log ){
    InitializeTestLog();
    if( !log )
      return NULL;
  }

  if( handler )
    log->last_handler = handler;

  return log;
}

TestLog *
TestLogSetLastMessage
( const char *message )
{
  if( !log ){
    InitializeTestLog();
    if( !log )
      return NULL;
  }

  if( message )
    log->last_message = message;

  return log;
}
