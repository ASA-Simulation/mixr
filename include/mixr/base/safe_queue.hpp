
#include "mixr/base/util/atomics.hpp"

#ifndef __mixr_base_safe_queue_H__
#define __mixr_base_safe_queue_H__

namespace mixr {
namespace base {

//------------------------------------------------------------------------------
// Template: safe_queue<T>
//
// Description: Thread-safe queue of items of type T
//
// Notes:
//    1) Use the constructor's 'qsize' parameter to set the max size of the queue.
//    2) Use put() to add items and get() to remove items.
//    3) put(), get(), peek() and clear() are internally protected by a semaphore
//
// Examples:
//    base::safe_queue<int>* q1 = new base::safe_queue<int>(100); // queue size 100 items
//    q1->put(1);           // puts 1 on the queue
//    q1->put(2);           // puts 2 on the queue
//    int i = q1->get();    // i is equal to 1
//    int j = q1->get();    // j is equal to 2
//------------------------------------------------------------------------------
template <class T> class safe_queue
{
public:
   safe_queue(const unsigned int qsize) : SIZE(qsize)   { queue = new T[SIZE]; }
   safe_queue(const safe_queue<T> &q1) : SIZE(q1.SIZE)  { queue = new T[SIZE]; }
   ~safe_queue()                                        { delete[] queue; }

   bool isEmpty() const           { return (n == 0); }
   bool isNotEmpty() const        { return (n != 0); }
   unsigned int entries() const   { return n; }
   bool isFull() const            { return (n >= SIZE); }
   bool isNotFull() const         { return (n < SIZE); }

   // Puts an item at the back of the queue.
   bool put(T item) {
      lock( semaphore );
      bool ok = false;
      if (n < SIZE) {
         // Put item in the queue
         queue[in++] = item;
         n++;
         if (in >= SIZE) in = 0;
         ok = true;
      }
      unlock( semaphore );
      return ok;
   }

   // Gets an item from the front of the queue
   T get() {
      lock( semaphore );
      T p = 0;
      if (!isEmpty()) {
         // Get item out of the queue
         if (in >= n) {
            p = queue[in - n];
         }
         else {
            p = queue[SIZE + in - n];
         }
         n--;
      }
      unlock( semaphore );
      return p;
   }

   // Peek at the next item without removing it from the queue.
   // The optional 'idx' is zero based starting at the front of
   // the queue (i.e. at the next get()).
   T peek0(unsigned int idx = 0) {
      lock( semaphore );
      T p = 0;
      if (idx < n) {
         unsigned int j = n - idx;
         // Get item out of the queue
         if (in >= j) {
            p = queue[in - j];
         }
         else {
            p = queue[SIZE + in - j];
         }
      }
      unlock( semaphore );
      return p;
   }

   // Clears the queue
   void clear() {
      lock( semaphore );
      in = 0;
      n = 0;
      unlock( semaphore );
   }

private:
   safe_queue<T>& operator=(safe_queue<T>&) { return *this; }
   T* queue {};                // The Queue
   const unsigned int SIZE {}; // Max size of the queue
   unsigned int in {};         // In (put) Index
   unsigned int n {};          // Number of items in queue
   mutable long semaphore {};  // semaphore
};

}
}

#endif
