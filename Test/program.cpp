#include <iostream>
#include "../Random/SourceOfNondeterminism.h"

using namespace std;
using namespace Random;

int main(int argc, char** argv)
{
   SourceOfNondeterminism gen = SourceOfNondeterminism(10);
   int cur = -999;
   int last = 999;
   int max = 1000000;
   int count = 0;
   for(int i = 0 ; i < max ; ++i)
   {
      cur = (int)gen.GetBytes(1).at(0);
      if(cur == last)
      {
         ++count;
         //cout << i << ": " << cur << endl;
      }
      last = cur;
   }
   cout << "Total: " << count << ": " << (double)max/(count*256) << endl;
   string str;
   cin >> str;
   return 0;
}