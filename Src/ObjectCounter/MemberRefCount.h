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
#ifndef _MemberRefCount_h_
#define _MemberRefCount_h_

namespace ObjectCounter
{

    template<typename ObjectT,        // the class type containing the counter
    typename CountT,         // the type of the counter
    CountT ObjectT::*CountP> // the location of the counter
    class MemberReferenceCount
    {
    public:
        // the default constructor and destructor are fine

        // initialize the counter to one:
        void Init(ObjectT* object)
        {
            object->*CountP = 1;
        }

        // no action is needed to dispose of the counter:
        void Dispose(ObjectT*)
        {
        }

        // increment by one:
        void Increment(ObjectT* object)
        {
            ++object->*CountP;
        }

        // decrement by one:
        void Decrement(ObjectT* object)
        {
            --object->*CountP;
        }

        // test for zero:
        template<typename T> bool IsZero(ObjectT* object)
        {
            return object->*CountP == 0;
        }
    };

}

#endif
