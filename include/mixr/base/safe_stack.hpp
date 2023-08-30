
#include "mixr/base/util/atomics.hpp"

#ifndef __mixr_base_safe_stack_H__
#define __mixr_base_safe_stack_H__

namespace mixr {
namespace base {

//------------------------------------------------------------------------------
// Template: safe_stack<T>
//
// Description: Thread-safe stack of items of type T
//
// Notes:
//    1) Use the constructor's 'ssize' parameter to set the max size of the stack.
//    2) Use push() to add items and pop() to remove items.
//    3) push(), pop() and clear() are internally protected by a semaphore
//
// Examples:
//    base::safe_stack<int>* q1 = new base::safe_stack<int>(100); // stack size 100 items
//    s1->push(1);          // pushes 1 on to the queue
//    s1->push(2);          // pushes 2 on to the queue
//    int i = s1->pop();    // i is equal to 2
//    int j = s1->pop();    // j is equal to 1
//------------------------------------------------------------------------------
template <class T> class safe_stack
{
public:
   safe_stack(const unsigned int ssize) : SIZE(ssize), sp(ssize)     { stack = new T[SIZE]; }
   safe_stack(const safe_stack<T> &s1) : SIZE(s1.SIZE), sp(s1.SIZE)  { stack = new T[SIZE]; }
   ~safe_stack()                                                     { delete[] stack; }

   unsigned int entries() const   { return (SIZE - sp); }
   bool isEmpty() const           { return (sp == SIZE); /* Empty when stack pointer equals stack size */ }
   bool isNotEmpty() const        { return !isEmpty(); }
   bool isFull() const            { return (entries() >= SIZE); }
   bool isNotFull() const         { return !isFull(); }

   // Pushes an item on to the stack
   bool push(T item) {
      lock( semaphore );
      bool ok = false;
      if (sp > 0) {
         stack[--sp] = item;
         ok = true;
      }
      unlock( semaphore );
      return ok;
   }

   // Pops an item from the top of the stack
   T pop() {
      lock( semaphore );
      T ii = 0;
      if (sp < SIZE) ii = stack[sp++];
      unlock( semaphore );
      return ii;
   }

   // Clears the stack
   void clear() {
      lock( semaphore );
      sp = SIZE;
      unlock( semaphore );
   }

private:
   safe_stack<T>& operator=(safe_stack<T>&) { return *this; }
   T* stack {};                // The Stack
   const unsigned int SIZE {}; // Max size of the stack
   unsigned int sp {};         // Stack pointer
   mutable long semaphore {};  // ref(), unref() semaphore
};

}
}

#endif

