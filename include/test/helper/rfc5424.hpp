/* SPDX-License-Identifier: Apache-2.0 */

/*
 * Copyright 2018-2021 Joel E. Anderson
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

#ifndef __STUMPLESS_TEST_HELPER_RFC5424_HPP
#  define __STUMPLESS_TEST_HELPER_RFC5424_HPP

/*
 * This format is specified in https://tools.ietf.org/html/rfc5424
 * Note that this regular expression does not ensure total compliance with the
 * RFC. Specifically, the following aspects of the specification are left
 * unchecked:
 * - the range of the PRIVAL is not validated, only that it is a number between
 *   one and three digits
 * - VERSION is not specifically checked to be "1"
 * - month and day values are not checked for sanity (for example, the 30th of
 *   february will not be rejected
 * - proper escaping of characters in the PARAM-VALUE elements within structured
 *   data is not detected
 * - SD-IDs and the associated PARAM-NAMEs are not checked according to the
 *   registrations with the IANA
 * - the values in PARAM-VALUE and MSG are not checked for UTF-8 compliance if
 *   the MSG is indeed encoded in UTF-8
 * If full compliance needs to be checked the TestRFC5424Compliance function
 * can be used to verify the above components as well. The function is written
 * for use with the Google Test framework.
 *
 * This expression will also populate several subgroups on the message, assuming
 * that there is a match. A description of each of these subgroups ordered by
 * their index is included below, using names from RFC 5424 where appropriate.
 * For optional components, the subgroup will of course be empty if the item was
 * absent in the message. For subggroups that are always a component of the RFC
 * grammar, there is a #define of the form RFC_5424_xxx_MATCH_INDEX, for example
 * RFC_5424_HOSTNAME_MATCH_INDEX.
 * 0  - SYSLOG-MSG (the entire message)
 * 1  - PRIVAL
 * 2  - VERSION
 * 3  - TIMESTAMP
 * 4  - FULL-DATE "T" FULL-YEAR if TIMESTAMP was not NILVALUE
 * 5  - DATE-FULLYEAR
 * 6  - DATE-MONTH
 * 7  - DATE-MDAY
 * 8  - TIME-SECFRAC if it was provided
 * 9  - TIME-OFFSET
 * 10 - TIME-NUMOFFSET if provided (that is, if TIME-OFFSET was not "Z")
 * 11 - The "+" or "-" character in TIME-NUMOFFSET if it was provided
 * 12 - HOSTNAME
 * 13 - HOSTNAME if it was not NILVALUE
 * 14 - APP-NAME
 * 15 - APP-NAME if it was not NILVALUE
 * 16 - PROCID
 * 17 - PROCID if it was not NILVALUE
 * 18 - MSGID
 * 19 - MSGID if it was not NILVALUE
 * 20 - STRUCTURED-DATA
 * 21 - 1*SD-ELEMENT if STRUCTURED-DATA was not NILVALUE
 * 22 - 1*SD-ELEMENT IF STRUCTURED-DATA was not NILVALUE
 * 23 - the first SD-ID in the message
 * 24 - everything from the first PARAM-NAME to the last "PARAM-VALUE"
 * 25 - MSG (the log message itself)
 */
#  define RFC_5424_REGEX_STRING "^<(\\d{1,3})>"                      /* PRI */ \
                                "([1-9]\\d{0,2})"                /* VERSION */ \
                                " "                                   /* SP */ \
                                "(-|("                         /* TIMESTAMP */ \
                                "(\\d{4})-(\\d{2})-(\\d{2})"   /* FULL-DATE */ \
                                "T"                                  /* "T" */ \
                                "\\d{2}:\\d{2}:\\d{2}"      /* PARTIAL-TIME */ \
                                "(\\.\\d{1,6})?"            /* TIME-SECFRAC */ \
                                "(Z|("                       /* TIME-OFFSET */ \
                                "(\\+|-)\\d{2}:\\d{2}"    /* TIME-NUMOFFSET */ \
                                "))"                         /* TIME-OFFSET */ \
                                "))"                           /* TIMESTAMP */ \
                                " "                                   /* SP */ \
                                "(-|([!-~]{1,255}))"            /* HOSTNAME */ \
                                " "                                   /* SP */ \
                                "(-|([!-~]{1,48}))"             /* APP-NAME */ \
                                " "                                   /* SP */ \
                                "(-|([!-~]{1,128}))"              /* PROCID */ \
                                " "                                   /* SP */ \
                                "(-|([!-~]{1,32}))"                /* MSGID */ \
                                " "                                   /* SP */ \
                                "(-|(("                  /* STRUCTURED-DATA */ \
                                "\\["                         /* SD-ELEMENT */ \
                                "([!#-<>-\\\\\\^-~]{1,32})"        /* SD-ID */ \
                                "( [!#-<>-\\\\\\^-~]{1,32}"   /* PARAM-NAME */ \
                                "=\".*\")*"                  /* PARAM-VALUE */ \
                                "\\]"                         /* SD-ELEMENT */ \
                                ")+))"                   /* STRUCTURED-DATA */ \
                                "( "                                   /* SP */ \
                                "(.*))?$" /* MSG */

#  define RFC_5424_SYSLOG_MSG_MATCH_INDEX 0
#  define RFC_5424_PRIVAL_MATCH_INDEX 1
#  define RFC_5424_VERSION_MATCH_INDEX 2
#  define RFC_5424_TIMESTAMP_MATCH_INDEX 3
#  define RFC_5424_DATE_FULLYEAR_MATCH_INDEX 5
#  define RFC_5424_DATE_MONTH_MATCH_INDEX 6
#  define RFC_5424_DATE_MDAY_MATCH_INDEX 7
#  define RFC_5424_TIME_SECFRAC_MATCH_INDEX 8
#  define RFC_5424_TIME_OFFSET_MATCH_INDEX 9
#  define RFC_5424_TIME_NUMOFFSET_MATCH_INDEX 10
#  define RFC_5424_HOSTNAME_MATCH_INDEX 12
#  define RFC_5424_APP_NAME_MATCH_INDEX 14
#  define RFC_5424_PROCID_MATCH_INDEX 16
#  define RFC_5424_MSGID_MATCH_INDEX 18
#  define RFC_5424_STRUCTURED_DATA_MATCH_INDEX 20
#  define RFC_5424_SD_ELEMENTS_MATCH_INDEX 21
#  define RFC_5424_MSG_MATCH_INDEX 25

#  define RFC_5424_PRIVAL_MIN 0
#  define RFC_5424_PRIVAL_MAX 191

void TestRFC5424Compliance( const char *syslog_msg );
void TestRFC5424StructuredData( const char *sd_elements );

#endif /* __STUMPLESS_TEST_HELPER_RFC5424_HPP */
