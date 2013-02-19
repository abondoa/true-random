#include "Interface.h"
#include <dieharder/tests.h>
#include <dieharder/Dtest.h>
#include <dieharder/std_test.h>
#include <dieharder/libdieharder.h>

void test_some_stuff()
{
   verbose = D_ALL;
   dieharder_test_types();
   Test **test = create_test(dh_test_types[0], dh_test_types[0]->tsamples_std, dh_test_types[0]->psamples_std);;
   ((int (*)(Test **,int))dh_test_types[0]->test)(test,0);
}

