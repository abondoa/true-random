#pragma once
#include "Generator.h"
#include "SourceOfNondeterminism.h"
#include "Distributor.h"
#include "DistributableGenerator.h"

namespace Random
{
	class __RandomNumberGeneratorFactory
	{
		__RandomNumberGeneratorFactory(void);
		SourceOfNondeterminism *_source;

	public:
		~__RandomNumberGeneratorFactory(void);

		template<class T> Generator<T> *GetGenerator()
		{
			return new Generator<T>(_source);
		}

		template<class T> Generator<T> *GetGenerator(Distributor<T> *dist)
		{
			return new DistributableGenerator<T>(_source, dist);
		}
		
		static __RandomNumberGeneratorFactory* GetInstance()
		{
			static __RandomNumberGeneratorFactory instance;
			return &instance;
		}
	};

}