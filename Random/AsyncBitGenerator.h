#pragma once
#include "bitgenerator.h"
#include <boost/thread.hpp>

namespace Random
{
   namespace Threaded
   {
      class AsyncBitGenerator :
         public BitGenerator
      {
      private:
         boost::thread* _generatorThread;
         boost::mutex* _mutex;
         boost::function<void(int,int)> _bitSetter;
         bool _running;
         int _bitMaskAssociation;
      
         void _threadLoop(void);

      public:
         AsyncBitGenerator(boost::function<void(int,int)>,int);
         ~AsyncBitGenerator(void);

         bool Start(void);
         bool Stop(void);
      };
   }
}