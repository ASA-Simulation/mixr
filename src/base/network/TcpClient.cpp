//------------------------------------------------------------------------------
// Class: TcpClient
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
    #include <sys/types.h>
    #include <Winsock2.h>
    #include <WS2tcpip.h>
    #define  bzero(a,b)   ZeroMemory(a,b)
    typedef int socklen_t;
#else
    #include <arpa/inet.h>  // htonl, htons, ntohl, ntohs
    #include <sys/fcntl.h>
    #include <sys/ioctl.h>
    #ifdef sun
        #include <sys/filio.h> // -- added for Solaris 10
    #endif
    static const int INVALID_SOCKET{-1}; // Always -1 and errno is set
    static const int SOCKET_ERROR{-1};
#endif

#include "mixr/base/network/TcpClient.hpp"

#include "mixr/base/numeric/Number.hpp"
#include "mixr/base/Pair.hpp"
#include "mixr/base/PairStream.hpp"
#include "mixr/base/String.hpp"
#include <cstring>

namespace mixr {
namespace base {

IMPLEMENT_SUBCLASS(TcpClient, "TcpClient")

BEGIN_SLOTTABLE(TcpClient)
    "ipAddress",    // 1) String containing the IP address in
                    //    the Internet standard "." (dotted) notation.
END_SLOTTABLE(TcpClient)

BEGIN_SLOT_MAP(TcpClient)
    ON_SLOT(1, setSlotIpAddress, String)
END_SLOT_MAP()

TcpClient::TcpClient()
{
    STANDARD_CONSTRUCTOR()
}

//------------------------------------------------------------------------------
// copyData() -- copy member data
//------------------------------------------------------------------------------
void TcpClient::copyData(const TcpClient& org, const bool)
{
    BaseClass::copyData(org);

    if (ipAddr != nullptr) delete[] ipAddr;
    ipAddr = nullptr;
    if (org.ipAddr != nullptr) {
        const std::size_t len {std::strlen(org.ipAddr)};
        ipAddr = new char[len+1];
        utStrcpy(ipAddr, (len+1), org.ipAddr);
    }
}

//------------------------------------------------------------------------------
// deleteData() -- delete member data
//------------------------------------------------------------------------------
void TcpClient::deleteData()
{
    if (ipAddr != nullptr) delete[] ipAddr;
    ipAddr = nullptr;
}

//------------------------------------------------------------------------------
// Initialize this multicast handler --
//------------------------------------------------------------------------------
bool TcpClient::initNetwork(const bool noWaitFlag)
{
    noWait = noWaitFlag;
    bool ok {BaseClass::initNetwork(false)};
    if (ok) {
        ok = connectToServer();
        if (!ok && isMessageEnabled(MSG_ERROR)) {
           std::cerr << "initNetwork(): connectToServer() FAILED" << std::endl;
        }
    }
    return ok;
}

//------------------------------------------------------------------------------
// init() -- init the network, the socket and the network address
//------------------------------------------------------------------------------
bool TcpClient::init()
{
   // Init the base class
   bool success {BaseClass::init()};
   if (!success) return false;

   // Find our network address
   success = setNetAddr(ipAddr);

   return success;
}


// -------------------------------------------------------------
// bindSocket() -- bind the socket to an address, and configure
// the send and receive buffers.
// -------------------------------------------------------------
bool TcpClient::bindSocket()
{
   // ---
   // Our base class will bind the socket
   // ---
   bool ok {BaseClass::bindSocket()};

   if (ok) {
      if (!setSendBuffSize()) return false;

      if (!setRecvBuffSize()) return false;
   }

   return ok;
}

//------------------------------------------------------------------------------
// connectToServer() -- attempt to connect to the server
//------------------------------------------------------------------------------
bool TcpClient::connectToServer()
{
   connected = false;
   connectionTerminated = false;

   if (ipAddr == nullptr) return false;

   if (socketNum == INVALID_SOCKET) return false;

   struct sockaddr_in addr;        // Working address structure
   bzero(&addr, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = getNetAddr();
   addr.sin_port = htons(getPort());

   if (isMessageEnabled(MSG_INFO)) {
      std::cout << "Connecting to TCP server at " << ipAddr << ":" << getPort() << " ... " << std::flush;
   }

   if (::connect(socketNum, reinterpret_cast<const struct sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
      if (isMessageEnabled(MSG_INFO)) {
          std::cout << "Failed!" << std::endl;
      }
   } else {
      if (isMessageEnabled(MSG_INFO)) {
          std::cout << "Connected!" << std::endl;
      }
      connected = true;
   }

   if (isMessageEnabled(MSG_INFO)) {
      std::cout << "TcpClient::connectToServer: socketNum = " << socketNum << std::endl;
   }

   // Set blocked or no-wait
   if (noWait) setNoWait();
   else setBlocked();

   return connected;
}

//------------------------------------------------------------------------------
// Set slot functions
//------------------------------------------------------------------------------

// ipAddress: String containing the IP address
bool TcpClient::setSlotIpAddress(const String* const msg)
{
    bool ok{};
    if (msg != nullptr) {
        ipAddr = msg->getCopyString();
        ok = true;
    }
    return ok;
}

}
}
