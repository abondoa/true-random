#pragma once
#include "generator.h"
#include "SourceOfNondeterminism.h"
#include "Distributor.h"

namespace Random
{
   template<class T> class DistributableGenerator :
      public Generator<T>
   {
   private:
      Distributor<T>* _distributor;

   public:
      DistributableGenerator(SourceOfNondeterminism* sod, Distributor<T>* distributer) : Generator(sod)
      {
         _distributor = distributer;
      }

      ~DistributableGenerator(void) {}

      T Generate()
      {
		 while(true)
		 {
			try
			{
			   long size = _distributor->GetExpectedVectorSize();
			   std::vector<T> randVector = std::vector<T>(size);

			   for(long i = 0; i < size; ++i)
			   {
				  randVector[i] = Generator<T>::Generate();
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