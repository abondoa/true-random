#include <iostream>
#include <time.h>
#include <boost/program_options.hpp>
#include "../Random/RandomNumberGeneratorFactory.h"
#include "../Random/Generator.h"

#define ever (;;)

using namespace std;
using namespace Random;
namespace po = boost::program_options;

template <class T, class S> void generate(Distributor<T,S>* dist = 0);
long long samples;
long long seed;
bool binary = false;

int main(int argc, char** argv)
{
	int bytes = 4;
   bool dieharder = false;
	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "Produce help message")
		("bytes,b", po::value<int>(&bytes)->default_value(4), "Set number of bytes pr generation: 1, 2, 4, 8")
		("float,f","Generate floating point numbers in range [0..1)")
		("seed,S", po::value<long long>(&seed)->default_value(time(NULL)), "seed")
		("samples,t", po::value<long long>(&samples)->default_value(-1), "Number of samples to generate (-1 to keep generating)")
		("dieharder,d", "Use dieharder format")
      ("binary,B", "Print binary")
	;
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);
	
	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
	}
	if (vm.count("binary")) {
      binary = true;
	}
   if (vm.count("dieharder")) {
      dieharder = true;
      cout << "#==================================================================" << endl
           << "# generator pmw8i seed = " << seed << endl
           << "#==================================================================" << endl
           << "type: d" << endl
           << "count: " << samples << endl
           << "numbit: "<< bytes*8 << endl;
	}
	switch(bytes)
	{
	case 1:
		generate<unsigned char,unsigned char>();
		break;
	case 2:
		generate<unsigned short, unsigned short>();
		break;
	case 4:
		if (vm.count("float")) {
            auto temp = RangeDistributor<unsigned int,float>(std::numeric_limits<unsigned int>::max(),0,0);
			generate(&temp);
		}
		else
		{
			generate<unsigned int, unsigned int>();
		}
		break;
	case 8:
		if (vm.count("float")) {
            auto temp = RangeDistributor<unsigned long long,double>(std::numeric_limits<unsigned long long>::max(),0,0);
			generate(&temp);
		}
		else
		{
			generate<unsigned long long, unsigned long long>();
		}
		break;
	default:
		cout << desc << "\n";
		return 1;
	}
	

	return 0;
}

template <class T, class S> void generate(Distributor<T,S>* dist)
{
	RandomNumberGenerator<S>* gen = RandomNumberGeneratorFactory::GetInstance()->GetGenerator(dist);

   if(binary)
   {
      if(samples == -1)
      {
	      for ever
	      {
            T x = gen->Generate();
            std::cout.write(reinterpret_cast<const char*>(&x), sizeof(T));
	      }
      }
      else
      {
         for(long long i = 0 ; i < samples ; i++)
         {
            T x = gen->Generate();
            std::cout.write(reinterpret_cast<const char*>(&x), sizeof(T));
         }
      }
   }
   else
   {
      if(samples == -1)
      {
	      for ever
	      {
		      cout << gen->Generate() << endl;
	      }
      }
      else
      {
         for(long long i = 0 ; i < samples ; i++)
         {
		      cout << gen->Generate() << endl;
         }
      }
   }

	delete gen;
}