#pragma once
#include "SourceOfNondeterminism.h"
#include <cstring>

using namespace std;

namespace Random
{
template <class T> class Generator
{
private:
   int _typeSize;
   SourceOfNondeterminism* _source;

public:
   Generator(SourceOfNondeterminism* source)
   {
      _typeSize = sizeof(T);
      _source = source;
   }

   ~Generator(void)
   {}

   T* Generate(T* ptr)
   {
      //char* temp = new char[_typeSize];
      vector<char> temp = _source->GetBytes(_typeSize);
      char *tempPtr = (char*)ptr;
      for(int i = 0; i < _typeSize; ++i)
      {
         tempPtr[i] = temp[i];
      }
      return ptr;
   }
};
}
