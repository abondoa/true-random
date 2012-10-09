#include "stdafx.h"
#include "SourceOfNondeterminismFactory.h"


namespace Random
{
   SourceOfNondeterminismFactory::SourceOfNondeterminismFactory(void)
   {
   }


   SourceOfNondeterminismFactory::~SourceOfNondeterminismFactory(void)
   {
   }

   SourceOfNondeterminism* SourceOfNondeterminismFactory::Create()
   {
      return new Threaded::ThreadedSourceOfNondeterminism();
   }
}