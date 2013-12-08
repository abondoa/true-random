#pragma once

namespace Random
{
   template<class T> class RandomNumberGenerator
   {
	public:
	   RandomNumberGenerator()
	   {
	   }

	   virtual ~RandomNumberGenerator(void)
	   {
	   }

	   virtual T Generate() = 0;
   };
}

