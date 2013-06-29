/* This sample file will describe the 2 following functions:
 *  . fabs
 *  . strcmp
*/

#include <stdio.h>
#include <string.h>

#include "cspec.h"
#include "cspec_output_verbose.h"

define_description(fabs)

int main()
{
  CSpec_vRun( fabs );

  return 0;
}

