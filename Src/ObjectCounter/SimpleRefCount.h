/* The following code example is taken from the book
 * "C++ Templates - The Complete Guide"
 * by David Vandevoorde and Nicolai M. Josuttis, Addison-Wesley, 2002
 *
 * (C) Copyright David Vandevoorde and Nicolai M. Josuttis 2002.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 */
#ifndef _SimpleRefCount_H_
#define _SimpleRefCount_H_

#include <stddef.h>  // for the definition of size_t
#include "Allocator.h"

namespace ObjectCounter
{

    class SimpleReferenceCount
    {
    private:
        size_t* counter;    // the allocated counter
    public:
        SimpleReferenceCount()
        {
            counter = NULL;
        }

        // default copy constructor and copy-assignment operator
        // are fine in that they just copy the shared counter

    public:
        // allocate the counter and initialize its value to one:
        template<typename T> void Init(T*)
        {
            counter = AllocCounter();
            *counter = 1;
        }

        // dispose of the counter:
        template<typename T> void Dispose(T*)
        {
            DeallocCounter(counter);
        }

        // increment by one:
        template<typename T> void Increment(T*)
        {
            ++*counter;
        }

        // decrement by one:
        template<typename T> void Decrement(T*)
        {
            --*counter;
        }

        // test for zero:
        template<typename T> bool IsZero(T*)
        {
            return *counter == 0;
        }
    };

}

#endif

