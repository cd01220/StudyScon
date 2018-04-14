#ifndef _StdArrayPolicy_H_
#define _StdArrayPolicy_H_

namespace ObjectCounter
{

    class StandardArrayPolicy
    {
    public:
        template<typename T> void Dispose(T* array)
        {
            delete[] array;
        }
    };

}

#endif
