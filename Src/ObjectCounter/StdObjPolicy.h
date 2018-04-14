#ifndef _StdObjPolicy_H_
#define _StdObjPolicy_H_

namespace ObjectCounter
{

    class StandardObjectPolicy
    {
    public:
        template<typename T> void Dispose(T* object)
        {
            delete object;
        }
    };

}

#endif

