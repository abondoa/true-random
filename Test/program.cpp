#include <iostream>
#include "../Random/IntegerGenerator.h"

using namespace std;
using namespace Random;

int main(int argc, char** argv)
{
   IntegerGenerator gen = IntegerGenerator(10);
   for(int i = 0 ; i < 100 ; ++i)
   {
      cout << gen.GetInteger(0,10) << endl;
   }
   string str;
   cin >> str;
   return 0;
}