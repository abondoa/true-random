#include "Interface.h"

void test_some_stuff()
{
   Test **test;
   verbose = D_ALL;
   dieharder_test_types();
   test = create_test(dh_test_types[0], dh_test_types[0]->tsamples_std, dh_test_types[0]->psamples_std);
   ((int (*)(Test **,int))dh_test_types[0]->test)(test,0);
}

