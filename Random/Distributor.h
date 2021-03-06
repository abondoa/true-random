#pragma once
#include <vector>
namespace Random
{
template<class T, class S = T> class Distributor
{
public:
   virtual S Distribute(std::vector<T> const& randomVector) const = 0;
   virtual long GetExpectedVectorSize() const = 0;

   Distributor(void) {}
   ~Distributor(void) {}
};

}