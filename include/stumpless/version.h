/*
 * Copyright 2018, Joel Anderson.
 * All Rights Reserved.
 *
 * This file is part of Stumpless.
 * 
 * Stumpless is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * Stumpless is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * Stumpless.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STUMPLESS_VERSION_H
#define __STUMPLESS_VERSION_H

#define STUMPLESS_MAJOR_VERSION 0
#define STUMPLESS_MINOR_VERSION 0
#define STUMPLESS_PATCH_VERSION 1

#ifdef __cplusplus
extern "C" {
#endif

struct stumpless_version {
  int major;
  int minor;
  int patch;
};

struct stumpless_version *get_stumpless_version();

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* __STUMPLESS_VERSION_H */
