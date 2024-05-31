/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2020-2024 Joel E. Anderson
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

#ifndef __STUMPLESS_PRIVATE_CONFIG_WRAPPER_LOCALE_H
#define __STUMPLESS_PRIVATE_CONFIG_WRAPPER_LOCALE_H

#include "private/config.h"

#ifdef USE_LOCALE_ES_ES
#  include "private/config/locale/es-es.h"
#elif defined USE_LOCALE_FR_FR
#  include "private/config/locale/fr-fr.h"
#elif defined USE_LOCALE_DE_DE
#  include "private/config/locale/de-de.h"
#elif defined USE_LOCALE_IT_IT
#  include "private/config/locale/it-it.h"
#elif defined USE_LOCALE_SV_SE
#  include "private/config/locale/sv-se.h"
#elif defined USE_LOCALE_SK_SK
#  include "private/config/locale/sk-sk.h"
#elif defined USE_LOCALE_BG_BG
#  include "private/config/locale/bg-bg.h"
#elif defined USE_LOCALE_CZ_CZ
#  include "private/config/locale/cz-cz.h"
#elif defined USE_LOCALE_PL_PL
#  include "private/config/locale/pl-pl.h"
#elif defined USE_LOCALE_EL_GR
#  include "private/config/locale/el-gr.h"
#elif defined USE_LOCALE_PT_BR
#  include "private/config/locale/pt-br.h"
#elif defined USE_LOCALE_ZH_CN
#  include "private/config/locale/zh-cn.h"
#elif defined USE_LOCALE_HI_IN
#  include "private/config/locale/hi-in.h"
#elif defined USE_LOCALE_BN_IN
#  include "private/config/locale/bn-in.h"
#elif defined USE_LOCALE_TE_IN
#  include "private/config/locale/te-in.h"
#elif defined USE_LOCALE_DA_DK
#  include "private/config/locale/da-dk.h"
#elif defined USE_LOCALE_HE_IL
#  include "private/config/locale/he-il.h"
#elif defined USE_LOCALE_SW_KE
#  include "private/config/locale/sw-ke.h"
#elif defined USE_LOCALE_TR_TR
#  include "private/config/locale/tr-tr.h"
#elif defined USE_LOCALE_HU_HU
#  include "private/config/locale/hu-hu.h"
#elif defined USE_LOCALE_SI_LK
#  include "private/config/locale/si-lk.h"
#elif defined USE_LOCALE_JA_JP
#  include "private/config/locale/ja-jp.h"
#elif defined USE_LOCALE_KO_KR
#  include "private/config/locale/ko-kr.h"
#else
#  include "private/config/locale/en-us.h"
#endif

#endif /* __STUMPLESS_PRIVATE_CONFIG_WRAPPER_LOCALE_H */
