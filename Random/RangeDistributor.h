#pragma once
#include "Distributor.h"
#include "RedistributionRequired.h"
#include <limits>

namespace Random
{
	template<class T, class S = T> class RangeDistributor :
		public Distributor<T, S>
	{
		T _typeMax;
		T _remainder;
		T _bucket;
		T _min;
		T _max;
	protected:

	   virtual bool isAcceptable(T const& rand) const
	   {
		  return !((rand == _typeMax) || (rand >= _typeMax - _remainder));
	   }

	   virtual S Distribute(T const& rand) const
	   {
		  if(isAcceptable(rand))
		  {
			 return _min + S(rand) / _bucket;
		  }
		  else
		  {
			 throw RedistributionRequired();
		  }
	   }

	public:
	   virtual S Distribute(std::vector<T> const& randomVector) const
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

		RangeDistributor(T const& typeMax, T const& min = std::numeric_limits<T>::min(), T const& max = std::numeric_limits<T>::max()) :  
				_typeMax(typeMax),
				_min(min),
				_max(max)
	   {
		   if(max < min)
		   {
			   throw std::exception("max < min in RangeDistributor");
		   }
		   T range = max - min + 1;
		   _remainder = _typeMax % range;
		   _bucket = _typeMax / range;
	   }

	   ~RangeDistributor() {}
	};

	//RangeDistributor<long double>::RangeDistributor(long double const &min, long double const& max, long double const& typeMax) : _min(min), _max(max), _typeMax(typeMax)
	//{
	//}

	//bool RangeDistributor<long double>::isAcceptable(long double const& rand) const
	//{
	//	return (rand == rand) && rand < std::numeric_limits<long double>::infinity() && rand > -std::numeric_limits<long double>::infinity() &&
	//		rand / _typeMax > 0.0 && rand / _typeMax < 1.0;
	//}

	//long double RangeDistributor<long double>::Distribute(long double const& rand) const
	//{
	//	if(isAcceptable(rand))
	//	{
	//		return rand / _typeMax;
	//	}
	//	else
	//	{
	//		throw RedistributionRequired();
	//	}
	//}

	//RangeDistributor<double>::RangeDistributor(double const &min, double const& max, double const& typeMax) : _min(min), _max(max), _typeMax(typeMax)
	//{
	//}

	//bool RangeDistributor<double>::isAcceptable(double const& rand) const
	//{
	//	return (rand == rand) && rand < std::numeric_limits<double>::infinity() && rand > -std::numeric_limits<double>::infinity() &&
	//		rand / _typeMax > 0.0 && rand / _typeMax < 1.0;
	//}

	//double RangeDistributor<double>::Distribute(double const& rand) const
	//{
	//	if(isAcceptable(rand))
	//	{
	//		return rand / _typeMax;
	//	}
	//	else
	//	{
	//		throw RedistributionRequired();
	//	}
	//}

	//RangeDistributor<float>::RangeDistributor(float const &min, float const& max, float const& typeMax) : _min(min), _max(max), _typeMax(typeMax)
	//{
	//}

	//bool RangeDistributor<float>::isAcceptable(float const& rand) const
	//{
	//	return (rand == rand) && rand < std::numeric_limits<float>::infinity() && rand > -std::numeric_limits<float>::infinity() &&
	//		rand / _typeMax > 0.0 && rand / _typeMax < 1.0;
	//}

	//float RangeDistributor<float>::Distribute(float const& rand) const
	//{
	//	if(isAcceptable(rand))
	//	{
	//		return rand / _typeMax;
	//	}
	//	else
	//	{
	//		throw RedistributionRequired();
	//	}
	//}
}