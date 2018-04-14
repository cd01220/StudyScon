/* The following code example is taken from the book
 * "C++ Templates - The Complete Guide"
 * by David Vandevoorde and Nicolai M. Josuttis, Addison-Wesley, 2002
 *
 * (C) Copyright David Vandevoorde and Nicolai M. Josuttis 2002.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 **/
#ifndef _Allocator_H_
#define _Allocator_H_

#include <stddef.h>

namespace ObjectCounter
{

    size_t* AllocCounter()
    {
        return ::new size_t;
    }

    void DeallocCounter(size_t* ptr)
    {
        ::delete ptr;
    }

}

#endif //_Allocator_H_
