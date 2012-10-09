#pragma once
#include "SourceOfNondeterminism.h"
#include <cstring>


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
      char* temp = new char[_typeSize];
      for(int i = 0; i < _typeSize; ++i)
      {
         temp[i] = _source->GetBytes(1)[0];
      }
      memcpy(ptr,temp,_typeSize);
      delete temp;
      return ptr;
   }
};
}
