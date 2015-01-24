#ifndef __STUMPLESS_TEST_TYPE_H
#define __STUMPLESS_TEST_TYPE_H

#include "private/type.h"

/**
 * Stores information regarding events in the test environment. Only
 * information that is registered to the log is captured.
 */
struct TestLog {
  const Record *last_adapted_record; /**< the last Record adapted */
  const Adapter *last_adapter; /**< the last Adapter run */
  const Exception *last_exception; /**< the last Exception thrown */
  const Record *last_formatted_record; /**< the last Record formatted */
  const Formatter *last_formatter; /**< the last Formatter run */
  const Output *last_generated_output; /**< the last Output generated */
  const Output *last_handled_output; /**< the last Output handled */
  const Handler *last_handler; /**< the last Handler run */
  const char *last_message; /**< the last message logged */
};

typedef struct TestLog TestLog;

#endif
