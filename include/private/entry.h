/*
 * Copyright 2018 Joel E. Anderson
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
 
#include <sys/types.h>
#include <stumpless/entry.h>

#ifndef __STUMPLESS_PRIVATE_ENTRY_H
#define __STUMPLESS_PRIVATE_ENTRY_H

ssize_t get_app_name(struct stumpless_entry *entry, char *destination, size_t size);
ssize_t get_hostname(char *destination, size_t size);
ssize_t get_msgid(struct stumpless_entry *entry, char *destination, size_t size);
ssize_t get_message(struct stumpless_entry *entry, char *destination, size_t size);
ssize_t get_procid(char *destination, size_t size);
ssize_t get_structured_data(struct stumpless_entry *entry, char *destination, size_t size);

#endif /* __STUMPLESS_PRIVATE_ENTRY_H */
