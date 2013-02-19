#include "stdafx.h"
#include "ThreadedSourceOfNondeterminism.h"


namespace Random
{
   namespace Threaded
   {
      ThreadedSourceOfNondeterminism::ThreadedSourceOfNondeterminism(int bufferSize)
      {
         _bitGenerators = new vector<AsyncBitGenerator*>();
         _buffer = new boost::circular_buffer<char>(bufferSize);
         _mutex = new boost::mutex();
         for(int i = 0 ; i < NUMBER_OF_GENERATORS ; ++i)
         {
            AsyncBitGenerator* temp = new AsyncBitGenerator(boost::bind(&ThreadedSourceOfNondeterminism::SetBits,this,_1,_2),1<<(i>>1));
            _bitGenerators->push_back(temp);
            temp->Start();
         }
         _reset();
      }

      ThreadedSourceOfNondeterminism::~ThreadedSourceOfNondeterminism(void)
      {
         _bitGenerators->clear();
         delete _bitGenerators;
         delete _buffer;
         delete _mutex;
      }

      vector<char> ThreadedSourceOfNondeterminism::GetBytes(int size)
      {
         vector<char> result = vector<char>();
         for(int i = 0 ; i < size ; ++i)
         {
            _mutex->lock();
            while(_isEmpty())
            {
               _mutex->unlock();
               boost::this_thread::yield();
               _mutex->lock();
            }
            result.push_back(_buffer->front());
            _buffer->pop_front();
            _mutex->unlock();
         }
         return result;
      }

      void ThreadedSourceOfNondeterminism::SetBits(char value,char mask)
      {
         _mutex->lock();
         _currentInteger &= ~mask;
         _currentInteger |= mask&value;
         _currentMask |= mask;
         _mutex->unlock();
      }
   
      void ThreadedSourceOfNondeterminism::_reset()
      {
         _currentInteger = NO_BITS_SET;
         _currentMask = NO_BITS_SET;
      }

      bool ThreadedSourceOfNondeterminism::_isEmpty()
      {
         _insertCurrent();
         return _buffer->empty();
      }

      void ThreadedSourceOfNondeterminism::_insertCurrent()
      {
         if(_currentMask == ALL_BITS_SET)
         {
            _buffer->push_back(_currentInteger);
            _reset();
         }
      }
   }
}