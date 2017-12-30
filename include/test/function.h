/*
 * Copyright 2017, Joel Anderson.
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

#ifndef __STUMPLESS_TEST_FUNCTION_H
#define __STUMPLESS_TEST_FUNCTION_H

/*
 * This format is specified in https://tools.ietf.org/html/rfc5424
 * Note that this regular expression does not ensure total compliance with the
 * RFC. Specifically, the following aspects of the specification are left
 * unchecked:
 * - the range of the PRIVAL is not validated, only that it is a number between
 *   one and three digits
 * - month and day values are not checked for sanit (for example, the 30th of
 *   february will not be rejected
 * - proper escaping of characters in the PARAM-VALUE elements within structured
 *   data is not detected
 * - the values in MSG are not checked for encoding differences, for example
 *   the BOM is not detected
 *
 * This expression will also populate several subgroups on the message, assuming
 * that there is a match. A description of each of these subgroups ordered by
 * their index is included below, using names from RFC 5424 where appropriate.
 * For optional components, the subgroup will of course be empty if the item was
 * absent in the message.
 * 0  - SYSLOG-MSG (the entire message)
 * 1  - PRIVAL
 * 2  - VERSION
 * 3  - TIMESTAMP
 * 4  - FULL-DATE "T" FULL-YEAR if TIMESTAMP was not NILVALUE
 * 5  - TIME-SECFRAC if it was provided
 * 6  - TIME-OFFSET
 * 7  - TIME-NUMOFFSET if provided (that is, if TIME-OFFSET was not "Z")
 * 8  - The "+" or "-" character in TIME-NUMOFFSET if it was provided
 * 9  - HOSTNAME
 * 10 - HOSTNAME if it was not NILVALUE
 * 11 - APP-NAME
 * 12 - APP-NAME if it was not NILVALUE
 * 13 - PROCID
 * 14 - PROCID if it was not NILVALUE
 * 15 - MSGID
 * 16 - MSGID if it was not NILVALUE
 * 17 - STRUCTURED-DATA
 * 18 - 1*SD-ELEMENT if STRUCTURED-DATA was not NILVALUE
 * 19 - 1*SD-ELEMENT IF STRUCTURED-DATA was not NILVALUE
 * 20 - the first SD-ID in the message
 * 21 - everything from the first PARAM-NAME to the last "PARAM-VALUE"
 * 22 - MSG (the log message itself)
 */
#define RFC_5424_REGEX_STRING "^<(\\d{1,3})>"                        /* PRI */ \
                              "([1-9]\\d{0,2})"                  /* VERSION */ \
                              " "                                     /* SP */ \
                              "(-|("                           /* TIMESTAMP */ \
                              "\\d{4}-\\d{2}-\\d{2}"           /* FULL-DATE */ \
			      "T"                                    /* "T" */ \
                              "\\d{2}:\\d{2}:\\d{2}"        /* PARTIAL-TIME */ \
			      "(\\.\\d{1,6})?"              /* TIME-SECFRAC */ \
                              "(Z|("                         /* TIME-OFFSET */ \
			      "(\\+|-)\\d{2}:\\d{2}"      /* TIME-NUMOFFSET */ \
                              "))"                           /* TIME-OFFSET */ \
                              "))"                             /* TIMESTAMP */ \
                              " "                                     /* SP */ \
                              "(-|([!-~]{1,255}))"              /* HOSTNAME */ \
                              " "                                     /* SP */ \
                              "(-|([!-~]{1,48}))"               /* APP-NAME */ \
                              " "                                     /* SP */ \
                              "(-|([!-~]{1,128}))"                /* PROCID */ \
                              " "                                     /* SP */ \
                              "(-|([!-~]{1,32}))"                  /* MSGID */ \
                              " "                                     /* SP */ \
                              "(-|(("                    /* STRUCTURED-DATA */ \
                              "\\["                           /* SD-ELEMENT */ \
                              "([!#-<>-\\\\\\^-~]{1,32})"          /* SD-ID */ \
			      "( [!#-<>-\\\\\\^-~]{1,32}"     /* PARAM-NAME */ \
                              "=\".*\")*"                    /* PARAM-VALUE */ \
			      "\\]"                           /* SD-ELEMENT */ \
                              ")+))"                     /* STRUCTURED-DATA */ \
                              " "                                     /* SP */ \
                              "(.*)$"                                /* MSG */

#endif /* __STUMPLESS_TEST_FUNCTION_H */
