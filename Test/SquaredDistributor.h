#pragma once
#include "Distributor.h"
#include <vector>

class SquaredDistributor :
   public Random::Distributor<unsigned char>
{
public:
   unsigned char Distribute(std::vector<unsigned char> const& randomVector) const
   {
      return (unsigned char)sqrt((double)(randomVector[0]*randomVector[1]));
   }

   long GetExpectedVectorSize() const
   {
      return 2;
   }

   SquaredDistributor(void){}
   ~SquaredDistributor(void){}
};

