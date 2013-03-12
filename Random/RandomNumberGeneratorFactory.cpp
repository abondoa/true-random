#include "RandomNumberGeneratorFactory.h"
#include "SourceOfNondeterminismFactory.h"
#include "Generator.h"


namespace Random
{

	__RandomNumberGeneratorFactory::__RandomNumberGeneratorFactory(void)
	{
		_source = SourceOfNondeterminismFactory::GetInstance()->Create();
	}

	__RandomNumberGeneratorFactory::~__RandomNumberGeneratorFactory(void)
	{
		delete _source;
	}
}