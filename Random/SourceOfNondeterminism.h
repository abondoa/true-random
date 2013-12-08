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
   public:
      SourceOfNondeterminism(void);
      virtual ~SourceOfNondeterminism(void);
      
      virtual vector<char> GetBytes(int) = 0;
   };

}