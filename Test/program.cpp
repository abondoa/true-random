#include <iostream>
#include "../Random/SourceOfNondeterminism.h"
#include "../Random/SourceOfNondeterminismFactory.h"
#include "../Random/Generator.h"
#include <cmath>

using namespace std;
using namespace Random;
template<class T> void repititionTest(int max);

SourceOfNondeterminism* sod;
int main(int argc, char** argv)
{
   sod = SourceOfNondeterminismFactory::GetInstance()->Create();
   repititionTest<short>(20000000);
   repititionTest<char>(20000000);
}

template<class T> void repititionTest(int max)
{
   Generator<T> gen(sod);
   T* dat = new T;
   T cur = -999;
   T last = 999;
   int count = 0;
   for(int i = 0 ; i < max ; ++i)
   {
      gen.Generate(dat);
      cur = *dat;
      if(cur == last)
      {
         ++count;
      }
      last = cur;
   }
   
   cout << "Repitition test on: " << count << " numbers, with a repitition factor of: " << (double)max/(count*pow(256,sizeof(T))) << " (close to 1 is good)" << endl;
   string str;
   cin >> str;
   return;
}