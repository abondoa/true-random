//#include <iostream>
//#include "SourceOfNondeterminism.h"
//#include "SourceOfNondeterminismFactory.h"
//#include "Generator.h"
//#include "DistributableGenerator.h"
//#include "RandomNumberGeneratorFactory.h"
//#include "CharPadder.h"
//#include "SquaredDistributor.h"
//#include "AverageDistributor.h"
//#include "NormalDistributor.h"
//#include <cmath>
//#include <fstream>
//#include <boost/timer/timer.hpp>
////#include <../Dieharder/Interface.h>
//
//using namespace std;
//using namespace Random;
//
//template<class T> void saveToFile(string fileName, vector<T> samples, long long millis, string header, string unit = "samples");
//template<class T> void distributionAndRepDistribution(long noOfSamples);
//
//SourceOfNondeterminism* sod;
int main(int argc, char** argv){return 1;}
//{
//   //distributionAndRepDistribution<unsigned char>(1000000);
//   //test_some_stuff();
//   //test_some_stuff();
//   cout << "done" << endl;
//   cin.get();
//
//   return 0;
//}
///*
//template<class T> void saveToFile(string fileName, vector<T> samples, long long millis, string header,string unit)
//{
//      ofstream file;
//      file.open(fileName);
//      file << header << endl;
//      
//      int size = samples.size();
//      int width = (int)log10((double)size) + 1;
//      long total = 0;
//
//      for(int i = 0 ; i < size ; ++i)
//      {
//         file << CharPadder(width) << i << "," << samples[i] << "," << unit << endl;
//         total += samples[i];
//      }
//      file << "total," << total << "," << unit << endl;
//      file << "time," << millis << ",ms" << endl;
//      file << "throughput," << total*1000/millis << "," << unit << "/s" << endl;
//
//      file.close();
//}
//
//template<class T> void distributionAndRepDistribution(long noOfSamples)
//{
//   long size = (long)powl(256,sizeof(T));
//   Generator<T> &gen = *RandomNumberGeneratorFactory::GetInstance()->GetGenerator<T>();
//   vector<long> samples(size);
//   vector<long> repSamples(size);
//   boost::timer::cpu_timer timer = boost::timer::cpu_timer();
//   for(int i = 0 ; i < size ; ++i)
//   {
//      samples[i] = 0;
//      repSamples[i] = 0;
//   }
//   
//   T temp;
//   T last = size+1;
//   timer.start();
//   for(long i = 0 ; i < noOfSamples ; ++i)
//   {
//      temp = gen.Generate();
//      if(temp == last)
//      {
//         repSamples[temp]++;
//      }
//      samples[temp]++;
//      last = temp;
//   }
//   timer.stop();
//   saveToFile("repitition distribution.csv",repSamples,timer.elapsed().wall /1000000,"Repitition Distribution","repititions");
//   saveToFile("distribution.csv",samples,timer.elapsed().wall /1000000,"Distribution","occurences");
//}
//*/