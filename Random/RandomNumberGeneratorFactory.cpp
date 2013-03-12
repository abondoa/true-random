#include "RandomNumberGeneratorFactory.h"
#include "SourceOfNondeterminismFactory.h"
#include "Generator.h"


namespace Random
{

	RandomNumberGeneratorFactory::RandomNumberGeneratorFactory(void)
	{
		_source = SourceOfNondeterminismFactory::GetInstance()->Create();
	}

	RandomNumberGeneratorFactory::~RandomNumberGeneratorFactory(void)
	{
		delete _source;
	}
}