#pragma once
#include "Generator.h"
#include "SourceOfNondeterminism.h"
#include "Distributor.h"

namespace Random
{
	template<class T, class S = T> class DistributableGenerator :
			public RandomNumberGenerator<S>
   {
   private:
      Distributor<T,S>* _distributor;
	  Generator<T> _generator;

   public:
      DistributableGenerator(SourceOfNondeterminism* sod, Distributor<T,S>* distributer) : 
		 _generator(sod)
      {
         _distributor = distributer;
      }

      ~DistributableGenerator(void) {}

      S Generate()
      {
		 while(true)
		 {
			try
			{
			   long size = _distributor->GetExpectedVectorSize();
			   std::vector<T> randVector = std::vector<T>(size);

			   for(long i = 0; i < size; ++i)
			   {
				  randVector[i] = _generator.Generate();
			   }
			   return _distributor->Distribute(randVector);
			}
			catch(RedistributionRequired)
			{
			}
		 }
      }
   };

}