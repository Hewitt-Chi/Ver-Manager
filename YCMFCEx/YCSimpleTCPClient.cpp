#include "stdafx.h"


#include "YCUtils.h"
#include "YCObject.h"
#include "YCCompletionObject.h"
#include "YCThread.h"
#include "YCMemoryBuffer.h"
#include "YCSimpleTCPConnection.h"
#include "YCSimpleTCPClient.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////////////////
// CYCSimpleTCPClient
//
IMPLEMENT_DYNAMIC(CYCSimpleTCPClient, CYCSimpleTCPConnection)


CYCSimpleTCPClient::CYCSimpleTCPClient()
: CYCSimpleTCPConnection()
{
}

CYCSimpleTCPClient::~CYCSimpleTCPClient()
{
    Close();
}

IMPLEMENT_CYCSimpleTCPConnection_OnCreateSocket(CYCSimpleTCPClient)
{
    bool    LRslt = true;
    SOCKET  LSocket = INVALID_SOCKET;


    // Create a TCP socket.
    if (LRslt)
    {
        LSocket = socket(AF_INET, SOCK_STREAM, 0);
        LRslt   = INVALID_SOCKET != LSocket;

        if (!LRslt)
            __DefaultHandleSocketError("CYCSimpleTCPConnection::InternalOpen() socket() fail.");
    }

    ASocket = LSocket;

    return LRslt;
}

IMPLEMENT_CYCSimpleTCPConnection_OnConnectSocket(CYCSimpleTCPClient)
{
    bool    LRslt = true;

    // Create the Internet address from the APeerIP number
    sockaddr_in     LSockAddrIn;

    ZeroMemory(&LSockAddrIn, sizeof(LSockAddrIn));

    LSockAddrIn.sin_family      = AF_INET;
    LSockAddrIn.sin_port        = htons((u_short)PeerPort());
    LSockAddrIn.sin_addr.s_addr = inet_addr(PeerIP());


    // Connect
    if (connect(ASocket, (const sockaddr*)&LSockAddrIn, sizeof(LSockAddrIn)) == SOCKET_ERROR)
    {
        // nonblocking connect
        const int LSocketErrorCode = WSAGetLastError();

        if (LSocketErrorCode != WSAEWOULDBLOCK)
        {
            LRslt = false;
            WSASetLastError(LSocketErrorCode);
        }
    }

    if (!LRslt)
        __DefaultHandleSocketError("CYCSimpleTCPConnection::InternalOpen() connect() fail.");

    return LRslt;
}

IMPLEMENT_CYCSimpleTCPConnection_OnDisconnectSocket(CYCSimpleTCPClient)
{
}

IMPLEMENT_CYCSimpleTCPConnection_OnDestroySocket(CYCSimpleTCPClient)
{
}
//
// CYCSimpleTCPClient
////////////////////////////////////////////////////
