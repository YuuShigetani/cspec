/* This sample file will run the skip list functions specifications */

#include <stdio.h>
#include "../src/skip_list.h"
#include "cspec/cspec.h"

int main()
{
  CSpec_vRun(EmptySkipList);
  CSpec_vRun(SkipListCount);
  CSpec_vRun(SkipListInsert);
  CSpec_vRun(SkipListContains);
  CSpec_vRun(SkipListDelete);

  return 0;
}

