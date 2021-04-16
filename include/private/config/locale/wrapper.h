/* SPDX-License-Identifier: Apache-2.0 */

/*
* Copyright 2020 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_LOCALE_WRAPPER_H
#  define __STUMPLESS_PRIVATE_CONFIG_LOCALE_WRAPPER_H

#  include "private/config.h"

#  ifdef USE_LOCALE_ES_ES
#    include "private/config/locale/es-es.h"
#  elif defined USE_LOCALE_FR_FR
#    include "private/config/locale/fr-fr.h"
#  elif defined USE_LOCALE_DE_DE
#	 include "private/config/locale/de-de.h"
#  elif defined USE_LOCALE_IT_IT
#    include "private/config/locale/it-it.h"
#  elif defined USE_LOCALE_SV_SE
#    include "private/config/locale/sv-se.h"
#  elif defined USE_LOCALE_SK_SK
#    include "private/config/locale/sk-sk.h"
#  elif defined USE_LOCALE_BG_BG
#    include "private/config/locale/bg-bg.h"
#  else
#    include "private/config/locale/en-us.h"
#  endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_LOCALE_WRAPPER_H */
