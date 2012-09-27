#include "stdafx.h"
#include "IntegerGenerator.h"


namespace Random
{
   IntegerGenerator::IntegerGenerator(int bufferSize)
   {
      _buffer = new boost::circular_buffer<int>(bufferSize);
      _mutex = new boost::mutex();
      _bitGenerators = new AsyncBitGenerator*[NUMBER_OF_GENERATORS];
      for(int i = 0 ; i < NUMBER_OF_GENERATORS ; ++i)
      {
         _bitGenerators[i] = new AsyncBitGenerator(boost::bind(&IntegerGenerator::SetBit,this,_1,_2),1<<(i>>1));
         _bitGenerators[i]->Start();
      }
      _reset();
   }


   IntegerGenerator::~IntegerGenerator(void)
   {
      for(int i = 0 ; i < NUMBER_OF_GENERATORS ; ++i)
      {
         _bitGenerators[i]->Stop();
         delete _bitGenerators[i];
      }
      delete[] _bitGenerators;
      _mutex->lock();
      delete _buffer;
      _buffer = 0;
      _mutex->unlock();
      delete _mutex;
   }
   
   int IntegerGenerator::GetInteger(int min, int max) 
   {
      _mutex->lock();
      while(_buffer->empty())
      {
         _mutex->unlock();
         boost::this_thread::yield();
         _mutex->lock();
      }
      int result = (_buffer->front())%(max-min)+min;
      _buffer->pop_front();
      _mutex->unlock();
      return result;
   }

   void IntegerGenerator::SetBit(int value, int mask)
   {
      _mutex->lock();
      _currentInteger &= ~mask;
      _currentInteger |= mask&value;
      _currentMask |= mask;
      _insertCurrent();
      _mutex->unlock();
   }
   
   void IntegerGenerator::_reset()
   {
      _currentInteger = 0;
      _currentMask = 0;
   }

   void IntegerGenerator::_insertCurrent()
   {
      if(_currentMask == ALL_SET)
      {
         _buffer->push_back(_currentInteger);
         _reset();
      }
   }
}