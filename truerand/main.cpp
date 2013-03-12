#include <iostream>
#include <boost\program_options.hpp>
#include "../Random/RandomNumberGeneratorFactory.h"
#include "../Random/Generator.h"

#define ever (;;)

using namespace std;
using namespace Random;
namespace po = boost::program_options;

template <class T> void generate();

int main(int argc, char** argv)
{
	int bytes;
	po::options_description desc("Allowed options");
	desc.add_options()
		("help,h", "Produce help message")
		("bytes,b", po::value<int>(&bytes)->default_value(4), "Set number of bytes pr generation: 1, 2, 4, 8")
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
		generate<unsigned char>();
		break;
	case 2:
		generate<unsigned short>();
		break;
	case 4:
		generate<unsigned int>();
		break;
	case 8:
		generate<unsigned long long>();
		break;
	default:
		cout << desc << "\n";
		return 1;
	}
	

	return 0;
}

template <class T> void generate()
{
	Generator<T>* gen = RandomNumberGeneratorFactory::GetInstance()->GetGenerator<T>();

	for ever
	{
		cout << (unsigned long long)gen->Generate() << endl;
	}

	delete gen;
}