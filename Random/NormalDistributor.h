#pragma once
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include "RangeDistributor.h"
#include <math.h>
#include <limits>

namespace Random
{
class NormalDistributor :
	public RangeDistributor<long double>
{
public:
   virtual long double Distribute(std::vector<long double> const& randomVector) const
   {
	   if(randomVector.size() != 2)
	   {
		   throw std::exception();
	   }
	   long double rand1 = RangeDistributor::Distribute(randomVector[0]);
	   long double rand2 = RangeDistributor::Distribute(randomVector[1]);
	   return sqrt(-2*log(rand1))*cos(2*M_PI*rand2);
   }

   virtual long GetExpectedVectorSize() const
   {
      return 2;
   }

   NormalDistributor() : RangeDistributor(0,1,std::numeric_limits<long double>::max()) {}
   ~NormalDistributor(void) {}
};

}