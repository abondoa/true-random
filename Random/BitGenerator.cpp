#include "stdafx.h"
#include "BitGenerator.h"
#include <exception>

namespace Random
{
   BitGenerator::BitGenerator(int firstBit)
   {
      if(firstBit < 0 || firstBit > 1)
      {
         throw std::exception("It's not a bit value: " + firstBit);
      }
      nextBit = firstBit;
   }

   BitGenerator::~BitGenerator(void)
   {
   }

   int BitGenerator::GetBit(void)
   {
      nextBit = 1 - nextBit;
      return nextBit;
   }
}