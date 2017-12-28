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

// this format is outlined in https://tools.ietf.org/html/rfc5424
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
                              ""                                /* APP-NAME */ \
                              ""                                      /* SP */ \
                              ""                                  /* PROCID */ \
                              ""                                      /* SP */ \
                              ""                                   /* MSGID */ \
                              ""                                      /* SP */ \
                              ""                         /* STRUCTURED-DATA */ \
                              ""                                      /* SP */ \
                              "$"                                    /* MSG */

#endif /* __STUMPLESS_TEST_FUNCTION_H */
