#include "stdafx.h"
#include "AsyncBitGenerator.h"

namespace Random
{
   AsyncBitGenerator::AsyncBitGenerator(boost::function<void(int,int)> bitSetter, int bitMaskAssociation)
   {
      _mutex = new boost::mutex();
      _generatorThread = 0;
      _bitSetter = bitSetter;
      _running = false;
      _bitMaskAssociation = bitMaskAssociation;
   }

   AsyncBitGenerator::~AsyncBitGenerator(void)
   {
      Stop();
      delete _mutex;
      if(_generatorThread != 0)
      {
         delete _generatorThread;
      }
   }

   bool AsyncBitGenerator::Start(void)
   {
      if(_mutex->try_lock())
      {
         _running = true;
         _generatorThread = new boost::thread(boost::bind(&AsyncBitGenerator::_threadLoop,this));
         _mutex->unlock();

         return _running;
      }
      return false;
   }

   bool AsyncBitGenerator::Stop(void)
   {
      if(_mutex->try_lock())
      {
         _running = false;
         _generatorThread->join();
         _generatorThread = 0;
         _mutex->unlock();

         return !_running;
      }
      return false;
   }
   
   void AsyncBitGenerator::_threadLoop(void)
   {
      while(_running)
      {
         _bitSetter(-GetBit(),_bitMaskAssociation);
      }
   }
}