#pragma once
#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>
#include "asyncbitgenerator.h"

namespace Random
{
   class IntegerGenerator
   {
   private:
      static const int ALL_SET = -1;
      static const int NUMBER_OF_GENERATORS = 64;

      boost::circular_buffer<int>* _buffer;
      boost::mutex* _mutex;
      AsyncBitGenerator** _bitGenerators;
      int _currentInteger;
      int _currentMask;

      void _reset();
      void _insertCurrent();

   public:
      IntegerGenerator(int);
      ~IntegerGenerator(void);

      int GetInteger(int,int);
      void SetBit(int,int);
   };

}