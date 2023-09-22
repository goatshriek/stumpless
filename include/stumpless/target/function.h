/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2021-2022 Joel E. Anderson
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @file
 * Function targets allow log entries to be sent to a custom function, making
 * it possible to implement arbitrary functionality using this library as a
 * logging framework.
 *
 * If a log function returns a negative value, it is passed on as the result of
 * the library call, and a STUMPLESS_FUNCTION_TARGET_FAILURE error is raised.
 * This allows error handling to use either return codes or the stumpless error
 * types.
 *
 * **Thread Safety: MT-Safe**
 * Logging to function targets is thread safe, dependent on the thread safety of
 * the function itself. No coordination is done by stumpless itself to ensure
 * that calls to the function are serialized.
 *
 * **Async Signal Safety: AS-Safe**
 * Logging to function targets is signal safe, depndent on the signal safety of
 * the function itself.
 *
 * **Async Cancel Safety: AC-Safe**
 * Logging to function targets is safe to call from threads that may be
 * asynchronously cancelled, dependent on the cancellation safety of the
 * function itself.
 */

#ifndef __STUMPLESS_TARGET_FUNCTION_H
#  define __STUMPLESS_TARGET_FUNCTION_H

#  include <stumpless/config.h>
#  include <stumpless/entry.h>
#  include <stumpless/target.h>
#  include <stumpless/target/function.h>

#  ifdef __cplusplus
extern "C" {
#  endif

/** A handler for entries sent to a function target. */
typedef int ( *stumpless_log_func_t )( const struct stumpless_target *,
                                       const struct stumpless_entry * );


/**
 * Closes a function target.
 *
 * **Thread Safety: MT-Unsafe**
 * This function is not thread safe as it destroys resources that other threads
 * would use if they tried to reference this target.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * the memory deallocation function to release memory.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory deallocation function may not be AC-Safe itself.
 *
 * @since release v2.1.0
 *
 * @param target The function target to close.
 */
STUMPLESS_PUBLIC_FUNCTION
void
stumpless_close_function_target( const struct stumpless_target *target );

/**
 * Opens a function target.
 *
 * Function targets provide a way to fully customize the behavior of a target,
 * defining any desired functionality and directly providing it to the target.
 * This can be used as a way to implement custom log targets such as a
 * specialized database table, or to take action if specific event types are
 * sent to the target.
 *
 * **Thread Safety: MT-Safe race:name**
 * This function is thread safe, of course assuming that name is not modified by
 * any other threads during execution.
 *
 * **Async Signal Safety: AS-Unsafe heap**
 * This function is not safe to call from signal handlers due to the use of
 * memory allocation functions.
 *
 * **Async Cancel Safety: AC-Unsafe heap**
 * This function is not safe to call from threads that may be asynchronously
 * cancelled, as the memory allocation function may not be AC-Safe itself.
 *
 * @since release v2.1.0
 *
 * @param name The name of the logging target.
 *
 * @param log_function The function to use to log entries sent to the target.
 * This function will be called for each entry sent to the target, and will be
 * given a pointer to the target itself as well as the entry passed to it. It
 * returns an int with the same semantics as stumpless_add_entry where a
 * non-negative value indicates success and a negative value is returned in
 * the event of an error. The target and entry pointers passed to the function
 * are guaranteed to be non-NULL, since NULL pointers will generate errors
 * before the function is called.
 *
 * @return The opened target if no error is encountered. In the event of an
 * error, NULL is returned and an error code is set appropriately.
 */
STUMPLESS_PUBLIC_FUNCTION
struct stumpless_target *
stumpless_open_function_target( const char *name,
                                stumpless_log_func_t log_function );

#  ifdef __cplusplus
}                               /* extern "C" */
#  endif
#endif                          /* __STUMPLESS_TARGET_FUNCTION_H */
