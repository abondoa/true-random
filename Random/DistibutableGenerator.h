#pragma once
#include "generator.h"
#include "SourceOfNondeterminism.h"
#include "Distributor.h"

namespace Random
{
   template<class T> class DistibutableGenerator :
      public Generator<T>
   {
   private:
      Distributor<T>* _distributor;

   public:
      DistibutableGenerator(SourceOfNondeterminism* sod, Distributor<T>* distributer) : Generator(sod)
      {
         _distributor = distributer;
      }

      ~DistibutableGenerator(void) {}

      T Generate()
      {
         long size = _distributor->GetExpectedVectorSize();
         std::vector<T> randVector = std::vector<T>(size);

         for(long i = 0; i < size; ++i)
         {
            randVector[i] = Generator<T>::Generate();
         }

         T result = _distributor->Distribute(randVector);
         return result;
      }
   };

}