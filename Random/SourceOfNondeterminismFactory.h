#pragma once
#include "SourceOfNondeterminism.h"
#include "ThreadedSourceOfNondeterminism.h"

namespace Random
{
   class SourceOfNondeterminismFactory
   {
   public:
      SourceOfNondeterminismFactory(void);
      ~SourceOfNondeterminismFactory(void);

      SourceOfNondeterminism* Create();

      static SourceOfNondeterminismFactory* GetInstance()
      {
         static SourceOfNondeterminismFactory instance;
         return &instance;
      }
   };
}