#include "stdafx.h"
#include "BitGenerator.h"

namespace Random
{
   BitGenerator::BitGenerator(void)
   {
      nextBit = 0;
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