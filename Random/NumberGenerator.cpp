#include "stdafx.h"
#include "NumberGenerator.h"

namespace Random
{
   NumberGenerator::NumberGenerator(void)
   {
   }


   NumberGenerator::~NumberGenerator(void)
   {
   }
   
   int  NumberGenerator::GetInteger(int min = 0, int max = (1<<31)-1) 
   {
      return 1;
   }

   double  NumberGenerator::GetDouble(double min = 0,double max = 1)
   {
      return 0.5;
   }
}