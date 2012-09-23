#pragma once

namespace Random
{

   class BitGenerator
   {
   private:
      int nextBit;

   public:
      BitGenerator(void);
      ~BitGenerator(void);

      int GetBit(void);
   };

}

