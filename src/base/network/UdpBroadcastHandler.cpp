//------------------------------------------------------------------------------
// Class: UdpBroadcastHandler
//------------------------------------------------------------------------------
//
// M$ WinSock has slightly different return types, some different calling, and
// is missing some of the calls that are standard in Berkeley and POSIX socket
// implementation.  These slight differences will be handled in setting basic
// typedefs, defines, and constants that will make each convention match for
// use later in the code.  This will save a lot of pre-processor intervention
// and make the code that much more enjoyable to read!
//
#if defined(WIN32)
    #define _WINSOCK_DEPRECATED_NO_WARNINGS
    #include <sys/types.h>
    #include <Winsock2.h>
    #define bzero(a,b) ZeroMemory( a, b )
    typedef int socklen_t;
#else
    #include <arpa/inet.h>
    #include <sys/fcntl.h>
    #include <sys/ioctl.h>
    #ifdef sun
        #include <sys/filio.h> // -- added for Solaris 10
    #endif
    static const int INVALID_SOCKET{-1}; // Always -1 and errno is set
    static const int SOCKET_ERROR{-1};
#endif

#include "mixr/base/network/UdpBroadcastHandler.hpp"

#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/String.hpp"

#include <cstdio>
#include <cstring>

namespace mixr {
namespace base {

IMPLEMENT_SUBCLASS(UdpBroadcastHandler, "UdpBroadcastHandler")

BEGIN_SLOTTABLE(UdpBroadcastHandler)
    "networkMask",       // 1) Host Net Mask   "255.255.255.255"
END_SLOTTABLE(UdpBroadcastHandler)

BEGIN_SLOT_MAP(UdpBroadcastHandler)
    ON_SLOT(1, setSlotNetworkMask, String)
END_SLOT_MAP()

UdpBroadcastHandler::UdpBroadcastHandler()
{
    STANDARD_CONSTRUCTOR()
}

void UdpBroadcastHandler::copyData(const UdpBroadcastHandler& org, const bool)
{
    BaseClass::copyData(org);

    if (networkMask != nullptr) delete[] networkMask;
    networkMask = nullptr;
    if (org.networkMask != nullptr) {
        const std::size_t len {std::strlen(org.networkMask)};
        networkMask = new char[len+1];
        utStrcpy(networkMask,(len+1),org.networkMask);
    }
}

void UdpBroadcastHandler::deleteData()
{
    if (networkMask != nullptr) delete[] networkMask;
    networkMask = nullptr;
}

//------------------------------------------------------------------------------
// init() -- init the network, the socket and the network address
//------------------------------------------------------------------------------
bool UdpBroadcastHandler::init()
{
    // ---
    // Init the base class
    // ---
    bool ok{BaseClass::init()};
    if (!ok) return false;

    // ---
    // Create our socket
    // ---
    socketNum = ::socket(AF_INET, SOCK_DGRAM, 0);
    if (socketNum == INVALID_SOCKET) {
        std::perror("UdpBroadcastHandler::init(): socket error");
        return false;
    }

    // ---
    // Set socket attribute for BROADCAST
    // ---
    {
#if defined(WIN32)
        BOOL optval{1};
        if (::setsockopt(socketNum, SOL_SOCKET, SO_BROADCAST, (const char*) &optval, sizeof(optval)) == SOCKET_ERROR) {
#else
        int optval = 1;
        if (::setsockopt(socketNum, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval)) == SOCKET_ERROR) {
#endif
            std::perror("UdpBroadcastHandler::init(): error setsockopt(SO_BROADCAST)\n");
            return false;
        }
    }

    return true;
}

// -------------------------------------------------------------
// bindSocket() -
// -------------------------------------------------------------
bool UdpBroadcastHandler::bindSocket()
{
    // ---
    // Our base class will bind the socket
    // ---
    bool ok{BaseClass::bindSocket()};

    // ---
    // Next, find and set the broadcast address
    // ---
    if (ok) {
        ok = false;
        if (networkMask != nullptr) {
            // User defined broadcast address
            const uint32_t localNetAddr{getLocalAddr()};
            const uint32_t localNetMask{::inet_addr(networkMask)};
            if (localNetAddr != INADDR_NONE && localNetMask != INADDR_NONE) {
               const uint32_t localNet{localNetAddr & localNetMask};
               const uint32_t ba{localNet | ~localNetMask};
               if (isMessageEnabled(MSG_INFO)) {
                  std::cout << std::hex << "UdpBroadcast::bindSocket() -- address: " << ba << std::dec << std::endl;
               }
               setNetAddr( ba );
               ok = true;
            }
        }
        if (!ok && isMessageEnabled(MSG_ERROR)) {
            std::cerr << "UdpBroadcast::bindSocket() -- unable to set broadcast address!" << std::endl;
        }
    }

    if (ok) {
       // ---
       // Bind the socket to the address in 'localAddr', which was configured by our derived class,
       // and the local port number
       // ---

       struct sockaddr_in addr;        // Working address structure
       bzero(&addr, sizeof(addr));
       addr.sin_family = AF_INET;
#if defined(WIN32)
       addr.sin_addr.s_addr = getLocalAddr();
#else
       addr.sin_addr.s_addr = getNetAddr();
#endif
       if (getLocalPort() != 0) addr.sin_port = htons (getLocalPort());
       else addr.sin_port = htons(getPort());

       if (bind(socketNum, reinterpret_cast<const struct sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
          std::perror("UdpBroadcast::bindSocket(): bind error");
          return false;
       }

       if (!setSendBuffSize()) return false;

       if (!setRecvBuffSize()) return false;
    }

    return ok;
}

//------------------------------------------------------------------------------
// Set slot functions
//------------------------------------------------------------------------------

// networkMask: Host Net Mask   "255.255.255.255"
bool UdpBroadcastHandler::setSlotNetworkMask(const String* const msg)
{
    bool ok{};
    if (msg != nullptr) {
        networkMask = msg->getCopyString();
        ok = true;
    }
    return ok;
}

}
}
