#include "stdafx.h"
#include "SourceOfNondeterminism.h"

namespace Random
{
   SourceOfNondeterminism::SourceOfNondeterminism(int bufferSize)
   {
      _bitGenerators = new vector<AsyncBitGenerator*>();
      _buffer = new boost::circular_buffer<char>(bufferSize);
      _mutex = new boost::mutex();
      for(int i = 0 ; i < NUMBER_OF_GENERATORS ; ++i)
      {
         AsyncBitGenerator* temp = new AsyncBitGenerator(boost::bind(&SourceOfNondeterminism::SetBits,this,_1,_2),1<<(i>>1));
         _bitGenerators->push_back(temp);
         temp->Start();
      }
      _reset();
   }


   SourceOfNondeterminism::~SourceOfNondeterminism(void)
   {
      _bitGenerators->clear();
      delete _bitGenerators;
      delete _buffer;
      delete _mutex;
   }

   vector<char> SourceOfNondeterminism::GetBytes(int size)
   {
      vector<char> result = vector<char>();
      for(int i = 0 ; i < size ; ++i)
      {
         _mutex->lock();
         while(_buffer->empty())
         {
            _insertCurrent();
            _mutex->unlock();
            boost::this_thread::yield();
            _mutex->lock();
            _insertCurrent();
         }
         result.push_back(_buffer->front());
         _buffer->pop_front();
         _mutex->unlock();
      }
      return result;
   }

   void SourceOfNondeterminism::SetBits(char value,char mask)
   {
      _mutex->lock();
      _currentInteger &= ~mask;
      _currentInteger |= mask&value;
      _currentMask |= mask;
      _mutex->unlock();
   }
   
   void SourceOfNondeterminism::_reset()
   {
      _currentInteger = NO_BITS_SET;
      _currentMask = NO_BITS_SET;
   }

   void SourceOfNondeterminism::_insertCurrent()
   {
      if(_currentMask == ALL_BITS_SET)
      {
         _buffer->push_back(_currentInteger);
         _reset();
      }
   }
}