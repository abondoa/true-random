#include <iostream>
#include <boost\program_options.hpp>
#include "../Random/RandomNumberGeneratorFactory.h"
#include "../Random/Generator.h"

#define ever (;;)

using namespace std;
using namespace Random;
namespace po = boost::program_options;

template <class T, class S> void generate(Distributor<T,S>* dist = 0);

int main(int argc, char** argv)
{
	int bytes;
	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "Produce help message")
		("bytes,b", po::value<int>(&bytes)->default_value(4), "Set number of bytes pr generation: 1, 2, 4, 8")
		("float,f","Generate floating point numbers in range [0..1)")
	;
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);
	
	if (vm.count("help")) {
		cout << desc << "\n";
		return 1;
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
		if (vm.count("float") || true) {
			generate(new RangeDistributor<unsigned int,float>(std::numeric_limits<unsigned int>::max(),0,0));
		}
		else
		{
			generate<unsigned int, unsigned int>();
		}
		break;
	case 8:
		if (vm.count("float")) {
			generate(new RangeDistributor<unsigned long long,double>(std::numeric_limits<unsigned long long>::max(),0,0));
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

	for ever
	{
		cout << gen->Generate() << endl;
	}

	delete gen;
	if(dist != 0)
		delete dist;
}