#pragma once
#include <vector>
#include "AsyncBitGenerator.h"
#include <boost/thread.hpp>
#include <boost/circular_buffer.hpp>

using namespace std;

namespace Random
{
   class SourceOfNondeterminism
   {
   private:
      static const char NO_BITS_SET = 0;
      static const char ALL_BITS_SET = -1;
      static const int NUMBER_OF_GENERATORS = 16;

      vector<AsyncBitGenerator*>* _bitGenerators;
      boost::circular_buffer<char>* _buffer;
      boost::mutex* _mutex;
      char _currentInteger;
      char _currentMask;

      void _reset();
      void _insertCurrent();

   public:
      SourceOfNondeterminism(int bufferSize = 256);
      ~SourceOfNondeterminism(void);
      
      vector<char> GetBytes(int);
      void SetBits(char,char);
   };

}