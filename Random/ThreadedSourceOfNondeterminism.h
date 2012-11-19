#pragma once
#include "SourceOfNondeterminism.h"

namespace Random
{
   namespace Threaded
   {
      class ThreadedSourceOfNondeterminism : public SourceOfNondeterminism
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
         bool _isEmpty();

      public:
         ThreadedSourceOfNondeterminism(int bufferSize = 256);
         ~ThreadedSourceOfNondeterminism(void);
      
         virtual vector<char> GetBytes(int);
         void SetBits(char,char);
      };
   }
}