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
 * - month and day values are not checked for sanit (for example, the 30th of
 *   february will not be rejected
 * - proper escaping of characters in the PARAM-VALUE elements within structured
 *   data is not detected
 * - the values in MSG are not checked for encoding differences, for example
 *   the BOM is not detected
 * todo document with parenthesis groups align to which elements in the RFC
 */
#define RFC_5424_REGEX_STRING "^<\\d{1,3}>"                          /* PRI */ \
                              "[1-9]\\d{0,2}"                     /* HEADER */ \
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
                              "[!#-<>-\\\\\\^-~]{1,32}"            /* SD-ID */ \
			      "( [!#-<>-\\\\\\^-~]{1,32}"     /* PARAM-NAME */ \
                              "=\".*\")*"                    /* PARAM-VALUE */ \
			      "\\]"                           /* SD-ELEMENT */ \
                              ")+))"                     /* STRUCTURED-DATA */ \
                              " "                                     /* SP */ \
                              ".*$"                                  /* MSG */

#endif /* __STUMPLESS_TEST_FUNCTION_H */
