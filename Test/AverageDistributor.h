#pragma once
#include "../Random/Distributor.h"
#include <vector>

class AverageDistributor :
   public Random::Distributor<unsigned char>
{
private:
   long _samples;
public:
   unsigned char Distribute(std::vector<unsigned char> const& randomVector) const
{
   long sum = 0;
   for(long i = 0 ; i < _samples; ++i)
   {
      sum +=randomVector[i];
   }
   return (unsigned char)(sum/_samples);
}

long GetExpectedVectorSize() const
{
   return _samples;
}

AverageDistributor(long samples) : _samples(samples) {}
~AverageDistributor(void){}
};

