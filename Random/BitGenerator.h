#pragma once

namespace Random
{

   class BitGenerator
   {
   private:
      int nextBit;

   public:
      BitGenerator(int);
      ~BitGenerator(void);

      int GetBit(void);
   };

}

