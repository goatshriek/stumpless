#ifndef __STUMPLESS_CONFIG_FEATURE_H
#define __STUMPLESS_CONFIG_FEATURE_H

#include <stumpless/config/check.h>

#ifndef __STUMPLESS_MULTIPROCESSING_DISABLED
# ifdef __STUMPLESS_HAVE_SYS_TYPES_H
#  ifdef __STUMPLESS_HAVE_UNISTD_H
#   define __STUMPLESS_MULTIPROCESSING_ENABLED 1
#  endif
# endif
#endif

#endif
