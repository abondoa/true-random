#pragma once
#include "distributor.h"
#include "RedistributionRequired.h"
#include <limits>

namespace Random
{
	template<class T> class RangeDistributor :
		public Distributor<T>
	{
		T _min;
		T _max;
		T _typeMax;
		T _remainder;
		T _bucket;
	protected:

	   virtual bool isAcceptable(T const& rand) const
	   {
		  return !((rand == _typeMax) || (rand >= _typeMax - _remainder));
	   }

	   virtual T Distribute(T const& rand) const
	   {
		  if(isAcceptable(rand))
		  {
			 return _min + rand / _bucket;
		  }
		  else
		  {
			 throw RedistributionRequired();
		  }
	   }

	public:
	   virtual T Distribute(std::vector<T> const& randomVector) const
	   {
		  if(randomVector.size() != 1)
		  {
			 throw std::exception();
		  }
		  return Distribute(randomVector[0]);
	   }

	   virtual long GetExpectedVectorSize() const
	   {
		  return 1;
	   }

	   RangeDistributor(T const &min, T const& max, T const& typeMax) : _min(min), _max(max), _typeMax(typeMax)
	   {
		   if(max <= min)
		   {
			   throw std::exception("max < min in RangeDistributor");
		   }
		   T range = max - min + 1;
		   _remainder = _typeMax % range;
		   _bucket = _typeMax / range;
	   }

	   ~RangeDistributor() {}
	};

	RangeDistributor<long double>::RangeDistributor(long double const &min, long double const& max, long double const& typeMax) : _min(min), _max(max), _typeMax(typeMax)
	{
	}

	bool RangeDistributor<long double>::isAcceptable(long double const& rand) const
	   {
		   return (rand == rand) && rand < std::numeric_limits<long double>::infinity() && rand > -std::numeric_limits<long double>::infinity() &&
			   rand / _typeMax > 0.0 && rand / _typeMax < 1.0;
	   }

	long double RangeDistributor<long double>::Distribute(long double const& rand) const
	{
		if(isAcceptable(rand))
		{
			return rand / _typeMax;
		}
		else
		{
			throw RedistributionRequired();
		}
	}
}