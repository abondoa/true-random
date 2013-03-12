#include <iostream>
#include "../Random/RandomNumberGeneratorFactory.h"
#include "../Random/Generator.h"

#define ever (;;)

using namespace std;
using namespace Random;

int main(int argc, char** argv)
{
	Generator<unsigned int>* gen = RandomNumberGeneratorFactory::GetInstance()->GetGenerator<unsigned int>();

	for ever
	{
		cout << gen->Generate() << endl;
	}

	delete gen;
	return 0;
}