#include <iostream>
#include "SourceOfNondeterminism.h"
#include "SourceOfNondeterminismFactory.h"
#include "Generator.h"
#include "DistributableGenerator.h"
#include "RandomNumberGeneratorFactory.h"
#include "CharPadder.h"
#include "SquaredDistributor.h"
#include "AverageDistributor.h"
#include "NormalDistributor.h"
#include <cmath>
#include <fstream>
#include <boost/timer/timer.hpp>
//#include <../Dieharder/Interface.h>


using namespace std;
using namespace Random;

template<class T> void repititionTest(int max);
void distribution(long, bool toCsv = false);
void repititionDistribution(long noOfSamples, bool toCsv);
template<class T> void saveToFile(string fileName, vector<T> samples, long long millis, string header, string unit = "samples");
template<class T> void distributionAndRepDistribution(long noOfSamples);
template<class T> void distributionAndRepDistributionFloat(long noOfSamples,long granularity);

SourceOfNondeterminism* sod;
int main(int argc, char** argv)
{
   sod = SourceOfNondeterminismFactory::GetInstance()->Create();
   //repititionTest<short>(20000000);
   //repititionTest<char>(20000000);
   //distribution(2000000000,true);
   //repititionDistribution(20000,true);
   distributionAndRepDistribution<unsigned char>(100000);
   //test_some_stuff();
   //test_some_stuff();
   cout << "done" << endl;
   cin.get();

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
   boost::timer::cpu_timer timer = boost::timer::cpu_timer();
   for(int i = 0 ; i < 256 ; ++i)
   {
      samples[i] = 0;
   }
   
   unsigned char *ptr = new unsigned char;
   int last = 256;
   timer.start();
   for(long i = 0 ; i < noOfSamples ; ++i)
   {
      gen.Generate(ptr);
      if(*ptr == last)
      {
         samples[*ptr]++;
      }
      last = *ptr;
   }
   timer.stop();
   if(toCsv)
   {
      saveToFile("repitition distribution.csv",samples,timer.elapsed().wall /1000000,"Repitition Distribution");
   }
   else
   {
      cout << "Repitition Distribution:" << endl;

      for(int i = 0 ; i < 256 ; ++i)
      {
         cout << CharPadder(3) << i << "," << samples[i] << endl;
      }
   }
}

template<class T> void saveToFile(string fileName, vector<T> samples, long long millis, string header,string unit)
{
      ofstream file;
      file.open(fileName);
      file << header << endl;
      
      int size = samples.size();
      int width = (int)log10((double)size) + 1;
      long total = 0;

      for(int i = 0 ; i < size ; ++i)
      {
         file << CharPadder(width) << i << "," << samples[i] << "," << unit << endl;
         total += samples[i];
      }
      file << "total," << total << "," << unit << endl;
      file << "time," << millis << ",ms" << endl;
      file << "throughput," << total*1000/millis << "," << unit << "/s" << endl;

      file.close();
}

char log(char c)
{
	return (char)(int)log((double) c);
}

template<class T> void distributionAndRepDistribution(long noOfSamples)
{
   long size = (long)powl(256,sizeof(T));
   Generator<T> &gen = *__RandomNumberGeneratorFactory::GetInstance()->GetGenerator<T>(new AverageDistributor(4));
   vector<long> samples(size);
   vector<long> repSamples(size);
   boost::timer::cpu_timer timer = boost::timer::cpu_timer();
   for(int i = 0 ; i < size ; ++i)
   {
      samples[i] = 0;
      repSamples[i] = 0;
   }
   
   T temp;
   T last = size+1;
   timer.start();
   for(long i = 0 ; i < noOfSamples ; ++i)
   {
      temp = gen.Generate();
      if(temp == last)
      {
         repSamples[temp]++;
      }
      samples[temp]++;
      last = temp;
   }
   timer.stop();
   saveToFile("repitition distribution.csv",repSamples,timer.elapsed().wall /1000000,"Repitition Distribution","repititions");
   saveToFile("distribution.csv",samples,timer.elapsed().wall /1000000,"Distribution","occurences");
}

template<class T> void distributionAndRepDistributionFloat(long noOfSamples,long granularity)
{
   long size = granularity+1;
   DistributableGenerator<T> gen(sod,new NormalDistributor());
   vector<long> samples(size);
   vector<long> repSamples(size);
   boost::timer::cpu_timer timer = boost::timer::cpu_timer();
   for(int i = 0 ; i < size ; ++i)
   {
      samples[i] = 0;
      repSamples[i] = 0;
   }
   
   T temp;
   T last = size+1;
   timer.start();
   for(long i = 0 ; i < noOfSamples ; ++i)
   {
      temp = gen.Generate();
      if(temp == last)
      {
         repSamples[temp*granularity]++;
      }
      samples[temp*granularity]++;
      last = temp;
   }
   timer.stop();
   saveToFile("repitition distribution.csv",repSamples,timer.elapsed().wall /1000000,"Repitition Distribution","repititions");
   saveToFile("distribution.csv",samples,timer.elapsed().wall /1000000,"Distribution","occurences");
}