#pragma once
#include "SourceOfNondeterminism.h"
#include "RandomNumberGenerator.h"
#include <cstring>

using namespace std;

namespace Random
{
template <class T> class Generator :
	public RandomNumberGenerator<T>
{
private:
   int _typeSize;
   SourceOfNondeterminism* _source;
   T* _pointer;

public:
   Generator(SourceOfNondeterminism* source)
   {
      _typeSize = sizeof(T);
      _source = source;
      _pointer = new T();
   }

   ~Generator(void)
   {
      delete _pointer;
   }

   virtual T* Generate(T* ptr)
   {
      vector<char> temp = _source->GetBytes(_typeSize);
      char *tempPtr = (char*)ptr;
      for(int i = 0; i < _typeSize; ++i)
      {
         tempPtr[i] = temp[i];
      }
      return ptr;
   }

   virtual T Generate()
   {
      Generate(_pointer);
      return *_pointer;
   }
};


}
