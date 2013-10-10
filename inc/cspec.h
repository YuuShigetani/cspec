/*
 *  cspec.h   :   the main header file
 *
 * See copyright notice at the end of this file
 *
 */

#ifndef CSPEC_H
#define CSPEC_H

/* Include private macros and function definitions */
#include "cspec_config.h"
#include "cspec_private.h"
#include "cspec_output.h"
#include "cspec_output_verbose.h"
#include "cspec_output_header.h"
#include "cspec_output_junit_xml.h"
#include "cspec_output_unit.h"
#include "cspec_output_xml.h"

/*               */
/* Public macros */
/*               */


/* Structural macros */

#define define_description(foo) void foo ## _describe();
#define description(foo)        foo ## _describe

#define describe(foo, caption)  void foo ## _describe () { CSpec_StartDescribe(caption); {
#define end_describe            } CSpec_EndDescribe(); }

#define it(caption)             { CSpec_StartIt(caption); {
#define end_it                  } CSpec_EndIt() ; }
#define end                     } CSpec_End() ; }

#define context(caption)        { CSpec_StartContext(caption); {
#define end_context            } CSpec_EndContext(); }

#define before(foo)                       \
    auto void before_ ## foo (void);      \
    CSpec_set_before( before_ ## foo ); \
    void before_ ## foo () {              \
    CSpec_StartBefore(); {
#define end_before         } CSpec_EndBefore(); }



/* Expectation macros */

#define expect_to_be_true(x)                    CSPEC_EVAL ( (x) )
#define expect_to_equal(x, y)                   CSPEC_EVAL ( (x) == (y) )
#define expect_to_equal_double(x, y, delta)     CSPEC_EVAL ( cspec_fabs( (x) - (y) ) <= delta )
#define expect_to_match(x, y)                   CSPEC_EVAL ( cspec_strcmp(x, y) ==  0   )
#define expect_to_be_null(x)                    CSPEC_EVAL ( (x) == 0 )

#define expect_to_be_false(x)                   CSPEC_EVAL ( !(x) )
#define expect_not_to_equal(x, y)               CSPEC_EVAL ( (x) != (y) )
#define expect_not_to_equal_double(x, y, delta) CSPEC_EVAL ( cspec_fabs( (x) - (y) ) > delta )
#define expect_not_to_match(x, y)               CSPEC_EVAL ( cspec_strcmp(x, y) != 0   )
#define expect_not_to_be_null(x)                CSPEC_EVAL ( (x) != 0 )

#define expect_to_pending(reason)               CSPEC_PENDING(reason)

/* Alias Expectation macros */

#define should_be_true(x)                       expect_to_be_true(x)
#define should_equal(x, y)                      expect_to_equal(x, y)
#define should_equal_double(x, y, delta)        expect_to_equal_double(x, y, delta)
#define should_match(x, y)                      expect_to_match(x, y)
#define should_be_null(x)                       expect_to_be_null(x)

#define should_be_false(x)                      expect_to_be_false(x)
#define should_not_equal(x, y)                  expect_not_to_equal(x, y)
#define should_not_equal_double(x, y, delta)    expect_not_to_equal_double(x, y, delta)
#define should_not_match(x, y)                  expect_not_to_match(x, y)
#define should_not_be_null(x)                   expect_not_to_be_null(x)

#define should_pending(reason)                  expect_to_pending(reason)


/* Public function definition */

typedef void ( * CSpecDescriptionFun ) ( );
int CSpec_Run( CSpecDescriptionFun fun, CSpecOutputStruct* output);
#define CSpec_vRun(fun) \
    define_description(fun) \
    CSpec_Run(description(fun), CSpec_NewOutputVerbose())
#define CSpec_hRun(fun) \
    define_description(fun) \
    CSpec_Run(description(fun), CSpec_NewOutputHeader())
#define CSpec_jxRun(fun) \
    define_description(fun) \
    CSpec_Run(description(fun), CSpec_NewOutputJUnitXml())
#define CSpec_uRun(fun) \
    define_description(fun) \
    CSpec_Run(description(fun), CSpec_NewOutputUnit())
#define CSpec_xRun(fun) \
    define_description(fun) \
    CSpec_Run(description(fun), CSpec_NewOutputXml())

#endif


/*
 * Copyright 2008 Arnaud Brejeon.
 *
 * Cspec is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, version 3.
 *
 * CSpec is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 */

