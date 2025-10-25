#include <stddef.h>
#include <string.h>
#include <stumpless/severity.h>
#include "private/error.h"
#include "private/severity.h"
#include "private/strhelper.h"
#include "private/config/wrapper/strncasecmp.h"

static char *severity_enum_to_string[] = {
    STUMPLESS_FOREACH_SEVERITY(GENERATE_STRING)};

/* helper alias mapping */
struct severity_alias
{
  const char *name;
  enum stumpless_severity value;
};

static struct severity_alias aliases[] = {
    {"PANIC", STUMPLESS_SEVERITY_EMERG_VALUE},
    {"ERROR", STUMPLESS_SEVERITY_ERR_VALUE},
    {"WARN", STUMPLESS_SEVERITY_WARNING_VALUE}};

enum stumpless_severity
stumpless_get_severity_enum_from_buffer(const char *severity_buffer, size_t severity_buffer_length)
{
  if (!severity_buffer || severity_buffer_length == 0)
  {
    raise_argument_empty("severity buffer");
    return -1;
  }

  clear_error();

  const size_t severity_bound = sizeof(severity_enum_to_string) / sizeof(severity_enum_to_string[0]);
  const size_t str_offset = 19; // skip "STUMPLESS_SEVERITY_"

  for (size_t i = 0; i < severity_bound; i++)
  {
    const char *name = severity_enum_to_string[i] + str_offset;
    size_t name_len = strlen(name);

    /* only accept exact-length matches */
    if (severity_buffer_length == name_len &&
        config_strncasecmp(severity_buffer, name, severity_buffer_length) == 0)
    {
      return i;
    }
  }

  /* check aliases */
  for (size_t i = 0; i < sizeof(aliases) / sizeof(aliases[0]); i++)
  {
    if (severity_buffer_length == strlen(aliases[i].name) &&
        config_strncasecmp(severity_buffer, aliases[i].name, severity_buffer_length) == 0)
    {
      return aliases[i].value;
    }
  }

  raise_invalid_severity(-1);
  return -1;
}
