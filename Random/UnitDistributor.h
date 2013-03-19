#pragma once
#include "Distributor.h"

namespace Random
{
	template<class T> class UnitDistributor :
			public  Distributor<T>
	{
		virtual T Distribute(std::vector<T> const& randomVector) const
		{
			return randomVector[0]
		}

		virtual long GetExpectedVectorSize() const
		{
			return 1;
		}

		UnitDistributor() {}

		~UnitDistributor() {}
	};
}