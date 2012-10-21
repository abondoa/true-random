#include <iostream>
#include "../Random/SourceOfNondeterminism.h"
#include "../Random/SourceOfNondeterminismFactory.h"
#include "../Random/Generator.h"
#include <cmath>
#include <fstream>

using namespace std;
using namespace Random;
template<class T> void repititionTest(int max);
void distribution(long, bool toCsv = false);
void repititionDistribution(long noOfSamples, bool toCsv);

SourceOfNondeterminism* sod;
int main(int argc, char** argv)
{
   sod = SourceOfNondeterminismFactory::GetInstance()->Create();
   //repititionTest<short>(20000000);
   //repititionTest<char>(20000000);
   //distribution(2000000000,true);
   repititionDistribution(20000000,true);
   cout << "done" << endl;
   string str;
   cin >> str;

   return 0;
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
   return;
}

void distribution(long noOfSamples, bool toCsv)
{
   Generator<unsigned char> gen(sod);
   vector<long> samples(256);

   for(int i = 0 ; i < 256 ; ++i)
   {
      samples[i] = 0;
   }
   
   unsigned char *ptr = new unsigned char;
   for(long i = 0 ; i < noOfSamples ; ++i)
   {
      gen.Generate(ptr);
      samples[*ptr]++;
   }

   // Assume x is in the correct range (0 <= x <= 9999)
   char target[5];
   if(toCsv)
   {
      ofstream file;
      file.open("distribution.csv");
      
      for(int i = 0 ; i < 256 ; ++i)
      {
         sprintf(target, "%03d", i);
         file << target << "," << samples[i] << endl;
      }

      file.close();
   }
   else
   {
      cout << "Distribution:" << endl;

      for(int i = 0 ; i < 256 ; ++i)
      {
         sprintf(target, "%03d", i);
         cout << target << " : " << samples[i] << endl;
      }
   }
}


void repititionDistribution(long noOfSamples, bool toCsv)
{
   Generator<unsigned char> gen(sod);
   vector<long> samples(256);

   for(int i = 0 ; i < 256 ; ++i)
   {
      samples[i] = 0;
   }
   
   unsigned char *ptr = new unsigned char;
   int last = 256;
   for(long i = 0 ; i < noOfSamples ; ++i)
   {
      gen.Generate(ptr);
      if(*ptr == last)
      {
         samples[*ptr]++;
      }
      last = *ptr;
   }

   // Assume x is in the correct range (0 <= x <= 9999)
   char target[5];
   if(toCsv)
   {
      ofstream file;
      file.open("repitition distribution.csv");
      
      for(int i = 0 ; i < 256 ; ++i)
      {
         sprintf(target, "%03d", i);
         file << target << "," << samples[i] << endl;
      }

      file.close();
   }
   else
   {
      cout << "Repitition Distribution:" << endl;

      for(int i = 0 ; i < 256 ; ++i)
      {
         sprintf(target, "%03d", i);
         cout << target << " : " << samples[i] << endl;
      }
   }
}


