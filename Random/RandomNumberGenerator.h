#pragma once

namespace Random
{
   template<class T> class RandomNumberGenerator
   {
	public:
	   RandomNumberGenerator()
	   {
	   }

	   ~RandomNumberGenerator(void)
	   {
	   }

	   virtual T Generate() = 0;
   };
}

