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
#ifndef _CountingPtr_H_
#define _CountingPtr_H_

namespace ObjectCounter
{

    class SimpleReferenceCount;
    class StandardObjectPolicy;

    template<typename T,
    typename CounterPolicy = SimpleReferenceCount,
    typename ObjectPolicy = StandardObjectPolicy>
    class CountingPtr: private CounterPolicy, private ObjectPolicy
    {
    private:
        // shortcuts:
        typedef CounterPolicy CP;
        typedef ObjectPolicy OP;

        T* pointer;      // the object referred to (or NULL if none)

    public:
        // default constructor (no explicit initialization):
        CountingPtr() : pointer(NULL)
    {
    }

        // a converting constructor (from a built-in pointer):
        explicit CountingPtr(T* p) : pointer(NULL)
        {
            Init(p);         // init with ordinary pointer
        }

        // copy constructor:
        CountingPtr(CountingPtr<T, CP, OP> const& inst) :
            CP((CP const&) inst),      // Init private base class.
            OP((OP const&) inst),      // Init private base class.
            pointer(NULL)
        {
            Attach(inst);      // copy pointer and increment counter
        }

        // destructor:
        ~CountingPtr()
        {
            Detach();        // decrement counter
            //  (and dispose counter if last owner)
        }

        // assignment of a built-in pointer
        CountingPtr<T, CP, OP>& operator=(T* p)
        {
            // no counting pointer should point to *p yet:
            assert(p != pointer);
            Detach();        // decrement counter
            //  (and dispose counter if last owner)
            Init(p);         // init with ordinary pointer
            return *this;
        }

        // copy assignment (beware of self-assignment):
        CountingPtr<T, CP, OP>&
        operator=(CountingPtr<T, CP, OP> const& cp)
        {
            if (pointer != cp.pointer)
            {
                // decrement counter (and dispose counter if last owner)
                Detach();
                // CP, OP is CountingPtr's base class. Call base's operator=();
                CP::operator=((CP const&) cp);  // assign policies
                OP::operator=((OP const&) cp);
                Attach(cp);  // copy pointer and increment counter
            }
            return *this;
        }

        // the operators that make this a smart pointer:
        T* operator->() const
        {
            return pointer;
        }

        T& operator*() const
        {
            return *pointer;
        }

        // additional interfaces will be added later
        //...

    private:
        // helpers:
        // - init with ordinary pointer (if any)
        void Init(T* p)
        {
            if (p != NULL)
            {
                CounterPolicy::Init(p);
            }
            pointer = p;
        }

        // - copy pointer and increment counter (if any)
        void Attach(CountingPtr<T, CP, OP> const& cp)
        {
            pointer = cp.pointer;
            if (cp.pointer != NULL)
            {
                CounterPolicy::Increment(cp.pointer);
            }
        }

        // - decrement counter (and dispose counter if last owner)
        void Detach()
        {
            if (pointer != NULL)
            {
                CounterPolicy::Decrement(pointer);
                if (CounterPolicy::IsZero(pointer))
                {
                    // dispose counter, if necessary:
                    CounterPolicy::Dispose(pointer);
                    // use object policy to dispose the object pointed to:
                    ObjectPolicy::Dispose(pointer);
                }
            }
        }
    };

}

#endif
