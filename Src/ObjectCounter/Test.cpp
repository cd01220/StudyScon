#include "SystemInclude.h"

#include "Allocator.h"
#include "CountingPtr.h"
#include "SimpleRefCount.h"
#include "StdObjPolicy.h"

#include "Test.h"

namespace ObjectCounter
{
    class IpPacket
    {
    public:
        IpPacket() : ipHeader(new IpHeader)
        {
        }

        void SetSrcAddress(char const* srcAddr)
        {
            memcpy(ipHeader->srcAddr, srcAddr, 16);
        }

    private:
        struct IpHeader
        {
            char srcAddr[16];
            char dstAddr[16];
        };
        CountingPtr<IpHeader> ipHeader;
    };
}

using namespace ObjectCounter;

void Test(DebugObjCnter const&)
{
    IpPacket ipPacket1;
    IpPacket ipPacket2;
    char ipAddr[16] = "10.0.0.1";

    ipPacket2.SetSrcAddress(ipAddr);
    ipPacket1 = ipPacket2;
}

