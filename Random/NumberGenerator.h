#pragma once

namespace Random
{
   class NumberGenerator
   {
   public:
      NumberGenerator(void);
      ~NumberGenerator(void);

      int GetInteger(int,int);
      double GetDouble(double,double);
   };
}

