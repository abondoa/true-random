#pragma once
#include "Generator.h"
#include "SourceOfNondeterminism.h"
#include "Distributor.h"
#include "DistributableGenerator.h"

namespace Random
{
	class RandomNumberGeneratorFactory
	{
		RandomNumberGeneratorFactory(void);
		SourceOfNondeterminism *_source;

	public:
		~RandomNumberGeneratorFactory(void);

		template<class T> Generator<T> *GetGenerator()
		{
			return new Generator<T>(_source);
		}

		template<class T> Generator<T> *GetGenerator(Distributor<T> *dist)
		{
			return new DistributableGenerator<T>(_source, dist);
		}
		
		static RandomNumberGeneratorFactory* GetInstance()
		{
			static RandomNumberGeneratorFactory instance;
			return &instance;
		}
	};

}