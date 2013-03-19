#pragma once
#include "RandomNumberGenerator.h"
#include "SourceOfNondeterminism.h"
#include "Distributor.h"
#include "RangeDistributor.h"
#include "DistributableGenerator.h"

namespace Random
{
	class RandomNumberGeneratorFactory
	{
		RandomNumberGeneratorFactory(void);
		SourceOfNondeterminism *_source;

	public:
		~RandomNumberGeneratorFactory(void);

		template<class T> RandomNumberGenerator<T> *GetGenerator()
		{
			return new Generator<T>(_source);
		}

		template<class T, class S> RandomNumberGenerator<S> *GetGenerator(Distributor<T,S> *dist)
		{
			if(dist == 0)
			{
				return GetGenerator<S>();
			}
			return new DistributableGenerator<T,S>(_source, dist);
		}
		
		static RandomNumberGeneratorFactory* GetInstance()
		{
			static RandomNumberGeneratorFactory instance;
			return &instance;
		}
	};

}