#include "stdafx.h"


#include "YCUtils.h"
#include "YCObject.h"
#include "YCCompletionObject.h"
#include "YCThread.h"
#include "YCMemoryBuffer.h"
#include "YCSimpleTCPConnection.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define YCTCPCLIENT_DefaultBufferSize                           8192


////////////////////////////////////////////////////
// CYCSimpleTCPClientConnection::strYCInitWinsock2
//
CYCSimpleTCPConnection::strYCInitWinsock2::strYCInitWinsock2()
{
    // Start WinSock2. If it fails, we do not need to call WSACleanup().
    WORD    LWS2Version = MAKEWORD(2, 0);
    WSADATA LWSAData;

    int LSockError = WSAStartup(LWS2Version, &LWSAData);

    if (LSockError == 0)
    {
        // Confirm that the WinSock2 DLL supports the exact version
        // we want. If not, call WSACleanup().
        if (LOBYTE(LWSAData.wVersion) != 2 || HIBYTE(LWSAData.wVersion) != 0)
        {
            goto ReturnFalse;
        }
    }
    else
    {
        goto ReturnFalse;
    }

    // Call WSAEnumProtocols to figure out how big of a buffer we need.
    DWORD   LBuffSize     = 0;
    int     LNumProtocols = WSAEnumProtocols(NULL, NULL, &LBuffSize);

    if ((LNumProtocols != SOCKET_ERROR) && (WSAGetLastError() != WSAENOBUFS))
        goto ReturnFalse;

    // Allocate a buffer, call WSAEnumProtocols to get an array of
    // WSAPROTOCOL_INFO structures.
    LPWSAPROTOCOL_INFO  LSelectedprotocol = (LPWSAPROTOCOL_INFO)malloc(LBuffSize);

    if (LSelectedprotocol == NULL)
        goto ReturnFalse;

    // Allocate memory for protocol list and define what protocols to look for.
    int *LProtos = (int *)calloc(2, sizeof(int));

    LProtos[0] = IPPROTO_TCP;
    LProtos[1] = IPPROTO_UDP;

    LNumProtocols = WSAEnumProtocols(LProtos, LSelectedprotocol, &LBuffSize);

    free(LProtos);
    LProtos = NULL;

    free(LSelectedprotocol);
    LSelectedprotocol = NULL;

    if (LNumProtocols == SOCKET_ERROR)
        goto ReturnFalse;

    return;

ReturnFalse :
    WSACleanup();
    AfxThrowNotSupportedException();

}

CYCSimpleTCPConnection::strYCInitWinsock2::~strYCInitWinsock2()
{
    WSACleanup();
}


const CYCSimpleTCPConnection::strYCInitWinsock2
/**/    CYCSimpleTCPConnection::m_InitWinsock2;
//
// CYCSimpleTCPClientConnection::strYCInitWinsock2
////////////////////////////////////////////////////


////////////////////////////////////////////////////
// CYCSimpleTCPConnection
//
IMPLEMENT_DYNAMIC(CYCSimpleTCPConnection, CYCObject)


LPCSTR CYCSimpleTCPConnection::YCFormatWSAErrorCodeText(int AErrorCode)
{
    struct strErrorText
    {
        int     Code;
        LPCSTR  Text;
    };

#define TextEntry(__Code, __Text)           { __Code, #__Code##" : "##__Text },

    static const strErrorText   LErrorTexts[] =
    {
        TextEntry(WSAEINTR                  , "A blocking operation was interrupted by a call to WSACancelBlockingCall.")
        TextEntry(WSAEBADF                  , "The file handle supplied is not valid.")
        TextEntry(WSAEACCES                 , "An attempt was made to access a socket in a way forbidden by its access permissions.")
        TextEntry(WSAEFAULT                 , "The system detected an invalid pointer address in attempting to use a pointer argument in a call.")
        TextEntry(WSAEINVAL                 , "An invalid argument was supplied.")
        TextEntry(WSAEMFILE                 , "Too many open sockets.")
        TextEntry(WSAEWOULDBLOCK            , "A non-blocking socket operation could not be completed immediately.")
        TextEntry(WSAEINPROGRESS            , "A blocking operation is currently executing.")
        TextEntry(WSAEALREADY               , "An operation was attempted on a non-blocking socket that already had an operation in progress.")
        TextEntry(WSAENOTSOCK               , "An operation was attempted on something that is not a socket.")
        TextEntry(WSAEDESTADDRREQ           , "A required address was omitted from an operation on a socket.")
        TextEntry(WSAEMSGSIZE               , "A message sent on a datagram socket was larger than the internal message buffer or some other network limit, or the buffer used to receive a datagram into was smaller than the datagram itself.")
        TextEntry(WSAEPROTOTYPE             , "A protocol was specified in the socket function call that does not support the semantics of the socket type requested.")
        TextEntry(WSAENOPROTOOPT            , "An unknown, invalid, or unsupported option or level was specified in a getsockopt or setsockopt call.")
        TextEntry(WSAEPROTONOSUPPORT        , "The requested protocol has not been configured into the system, or no implementation for it exists.")
        TextEntry(WSAESOCKTNOSUPPORT        , "The support for the specified socket type does not exist in this address family.")
        TextEntry(WSAEOPNOTSUPP             , "The attempted operation is not supported for the type of object referenced.")
        TextEntry(WSAEPFNOSUPPORT           , "The protocol family has not been configured into the system or no implementation for it exists.")
        TextEntry(WSAEAFNOSUPPORT           , "An address incompatible with the requested protocol was used.")
        TextEntry(WSAEADDRINUSE             , "Only one usage of each socket address (protocol/network address/port) is normally permitted.")
        TextEntry(WSAEADDRNOTAVAIL          , "The requested address is not valid in its context.")
        TextEntry(WSAENETDOWN               , "A socket operation encountered a dead network.")
        TextEntry(WSAENETUNREACH            , "A socket operation was attempted to an unreachable network.")
        TextEntry(WSAENETRESET              , "The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress.")
        TextEntry(WSAECONNABORTED           , "An established connection was aborted by the software in your host machine.")
        TextEntry(WSAECONNRESET             , "An existing connection was forcibly closed by the remote host.")
        TextEntry(WSAENOBUFS                , "An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full.")
        TextEntry(WSAEISCONN                , "A connect request was made on an already connected socket.")
        TextEntry(WSAENOTCONN               , "A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplied.")
        TextEntry(WSAESHUTDOWN              , "A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call.")
        TextEntry(WSAETOOMANYREFS           , "Too many references to some kernel object.")
        TextEntry(WSAETIMEDOUT              , "A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond.")
        TextEntry(WSAECONNREFUSED           , "No connection could be made because the target machine actively refused it.")
        TextEntry(WSAELOOP                  , "Cannot translate name.")
        TextEntry(WSAENAMETOOLONG           , "Name component or name was too long.")
        TextEntry(WSAEHOSTDOWN              , "A socket operation failed because the destination host was down.")
        TextEntry(WSAEHOSTUNREACH           , "A socket operation was attempted to an unreachable host.")
        TextEntry(WSAENOTEMPTY              , "Cannot remove a directory that is not empty.")
        TextEntry(WSAEPROCLIM               , "A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously.")
        TextEntry(WSAEUSERS                 , "Ran out of quota.")
        TextEntry(WSAEDQUOT                 , "Ran out of disk quota.")
        TextEntry(WSAESTALE                 , "File handle reference is no longer available.")
        TextEntry(WSAEREMOTE                , "Item is not available locally.")
        TextEntry(WSASYSNOTREADY            , "WSAStartup cannot function at this time because the underlying system it uses to provide network services is currently unavailable.")
        TextEntry(WSAVERNOTSUPPORTED        , "The Windows Sockets version requested is not supported.")
        TextEntry(WSANOTINITIALISED         , "Either the application has not called WSAStartup, or WSAStartup failed.")
        TextEntry(WSAEDISCON                , "Returned by WSARecv or WSARecvFrom to indicate the remote party has initiated a graceful shutdown sequence.")
        TextEntry(WSAENOMORE                , "No more results can be returned by WSALookupServiceNext.")
        TextEntry(WSAECANCELLED             , "A call to WSALookupServiceEnd was made while this call was still processing. The call has been canceled.")
        TextEntry(WSAEINVALIDPROCTABLE      , "The procedure call table is invalid.")
        TextEntry(WSAEINVALIDPROVIDER       , "The requested service provider is invalid.")
        TextEntry(WSAEPROVIDERFAILEDINIT    , "The requested service provider could not be loaded or initialized.")
        TextEntry(WSASYSCALLFAILURE         , "A system call that should never fail has failed.")
        TextEntry(WSASERVICE_NOT_FOUND      , "No such service is known. The service cannot be found in the specified name space.")
        TextEntry(WSATYPE_NOT_FOUND         , "The specified class was not found.")
        TextEntry(WSA_E_NO_MORE             , "No more results can be returned by WSALookupServiceNext.")
        TextEntry(WSA_E_CANCELLED           , "A call to WSALookupServiceEnd was made while this call was still processing. The call has been canceled.")
        TextEntry(WSAEREFUSED               , "A database query failed because it was actively refused.")
        TextEntry(WSAHOST_NOT_FOUND         , "No such host is known.")
        TextEntry(WSATRY_AGAIN              , "This is usually a temporary error during hostname resolution and means that the local server did not receive a response from an authoritative server.")
        TextEntry(WSANO_RECOVERY            , "A non-recoverable error occurred during a database lookup.")
        TextEntry(WSANO_DATA                , "The requested name is valid, but no data of the requested type was found.")
        TextEntry(WSA_QOS_RECEIVERS         , "At least one reserve has arrived.")
        TextEntry(WSA_QOS_SENDERS           , "At least one path has arrived.")
        TextEntry(WSA_QOS_NO_SENDERS        , "There are no senders.")
        TextEntry(WSA_QOS_NO_RECEIVERS      , "There are no receivers.")
        TextEntry(WSA_QOS_REQUEST_CONFIRMED , "Reserve has been confirmed.")
        TextEntry(WSA_QOS_ADMISSION_FAILURE , "Error due to lack of resources.")
        TextEntry(WSA_QOS_POLICY_FAILURE    , "Rejected for administrative reasons - bad credentials.")
        TextEntry(WSA_QOS_BAD_STYLE         , "Unknown or conflicting style.")
        TextEntry(WSA_QOS_BAD_OBJECT        , "Problem with some part of the filterspec or providerspecific buffer in general.")
        TextEntry(WSA_QOS_TRAFFIC_CTRL_ERROR, "Problem with some part of the flowspec.")
        TextEntry(WSA_QOS_GENERIC_ERROR     , "General QOS error.")
        TextEntry(WSA_QOS_ESERVICETYPE      , "An invalid or unrecognized service type was found in the flowspec.")
        TextEntry(WSA_QOS_EFLOWSPEC         , "An invalid or inconsistent flowspec was found in the QOS structure.")
        TextEntry(WSA_QOS_EPROVSPECBUF      , "Invalid QOS provider-specific buffer.")
        TextEntry(WSA_QOS_EFILTERSTYLE      , "An invalid QOS filter style was used.")
        TextEntry(WSA_QOS_EFILTERTYPE       , "An invalid QOS filter type was used.")
        TextEntry(WSA_QOS_EFILTERCOUNT      , "An incorrect number of QOS FILTERSPECs were specified in the FLOWDESCRIPTOR.")
        TextEntry(WSA_QOS_EOBJLENGTH        , "An object with an invalid ObjectLength field was specified in the QOS provider-specific buffer.")
        TextEntry(WSA_QOS_EFLOWCOUNT        , "An incorrect number of flow descriptors was specified in the QOS structure.")
        TextEntry(WSA_QOS_EUNKOWNPSOBJ      , "An unrecognized object was found in the QOS provider-specific buffer.")
        TextEntry(WSA_QOS_EPOLICYOBJ        , "An invalid policy object was found in the QOS provider-specific buffer.")
        TextEntry(WSA_QOS_EFLOWDESC         , "An invalid QOS flow descriptor was found in the flow descriptor list.")
        TextEntry(WSA_QOS_EPSFLOWSPEC       , "An invalid or inconsistent flowspec was found in the QOS provider specific buffer.")
        TextEntry(WSA_QOS_EPSFILTERSPEC     , "An invalid FILTERSPEC was found in the QOS provider-specific buffer.")
        TextEntry(WSA_QOS_ESDMODEOBJ        , "An invalid shape discard mode object was found in the QOS provider specific buffer.")
        TextEntry(WSA_QOS_ESHAPERATEOBJ     , "An invalid shaping rate object was found in the QOS provider-specific buffer.")
        TextEntry(WSA_QOS_RESERVED_PETYPE   , "A reserved policy element was found in the QOS provider-specific buffer.")
        { 0, NULL }
    };


    for (int I = 0; LErrorTexts[I].Text; I ++)
    {
        if (LErrorTexts[I].Code == AErrorCode)
            return LErrorTexts[I].Text;
    }


    if (AErrorCode)
    {
        static char LStr[64];

        sprintf_s(LStr, sizeof(LStr), "Unkown error code %d.\n", AErrorCode);

        return LStr;
    }

    return NULL;
}

CYCSimpleTCPConnection::CYCSimpleTCPConnection()
: CYCObject()
, m_PeerIP("127.0.0.1")
, m_PeerPort(10110)
, m_ConnectTimeoutMSec(30000)
, m_IsTCPNoDelay(false)
, m_EventSinker(NULL)
, m_Socket(INVALID_SOCKET)
, m_LocalIP("")
, m_LocalPort(0)
, m_ThreadHandle(NULL)
, m_ThreadId(0)
, m_IsThreadTerminated(true)
, m_ThreadReadyEvent(INVALID_HANDLE_VALUE)
{
}

CYCSimpleTCPConnection::~CYCSimpleTCPConnection()
{
    ASSERT(m_Socket == INVALID_SOCKET);

    Close();
}

LPCSTR  CYCSimpleTCPConnection::PeerIP() const
{
    return m_PeerIP;
}

void    CYCSimpleTCPConnection::SetPeerIP(LPCSTR AValue)
{
    m_PeerIP = AValue;
}

int     CYCSimpleTCPConnection::PeerPort() const
{
    return m_PeerPort;
}

void    CYCSimpleTCPConnection::SetPeerPort(int AValue)
{
    m_PeerPort = AValue;
}

DWORD   CYCSimpleTCPConnection::ConnectTimeoutMSec() const
{
    return m_ConnectTimeoutMSec;
}

void    CYCSimpleTCPConnection::SetConnectTimeoutMSec(DWORD AValue)
{
    m_ConnectTimeoutMSec = AValue;
}

bool    CYCSimpleTCPConnection::IsTCPNoDelay() const
{
    return m_IsTCPNoDelay;
}

void    CYCSimpleTCPConnection::SetIsTCPNoDelay(bool AValue)
{
    m_IsTCPNoDelay = AValue;
}

LPCSTR  CYCSimpleTCPConnection::LocalIP() const
{
    return m_LocalIP;
}

int     CYCSimpleTCPConnection::LocalPort() const
{
    return m_LocalPort;
}

bool    CYCSimpleTCPConnection::IsConnected() const
{
    return INVALID_SOCKET != m_Socket;
}

IYCSimpleTCPConnectionEventSinker*
/**/    CYCSimpleTCPConnection::EventSinker() const
{
    return m_EventSinker;
}

void    CYCSimpleTCPConnection::SetEventSinker(IYCSimpleTCPConnectionEventSinker *AValue)
{
    m_EventSinker = AValue;
}

unsigned __stdcall
/**/    YCTCPConnectionThreadFunc(void *AArg)
{
    CYCSimpleTCPConnection
        /**/    *LArg = reinterpret_cast<CYCSimpleTCPConnection *>(AArg);

    UINT    LRslt = 0;

    if (LArg)
        LRslt = LArg->ThreadExecute();

    return LRslt;
} 

bool    CYCSimpleTCPConnection::Open()
{
    CSingleLock LWorkingThreadLocker(&m_WorkingThreadLocker, TRUE);

    if (INVALID_SOCKET == m_Socket)
    {
        TRACE("CYCSimpleTCPConnection::Open() %s.\n",  (INVALID_SOCKET == m_Socket) ? "fail" : "succ"); 

        if (m_ThreadHandle)
        {
            m_IsThreadTerminated = true;
            WaitForSingleObject(m_ThreadHandle, INFINITE);

            CloseHandle(m_ThreadHandle);
            m_ThreadHandle = NULL;
            m_ThreadId     = 0;
        }


        m_ThreadReadyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

        m_ThreadHandle     = (HANDLE)_beginthreadex(NULL, 0, &YCTCPConnectionThreadFunc, this, 0, &m_ThreadId);

        WaitForSingleObject(m_ThreadReadyEvent, INFINITE);
        CloseHandle(m_ThreadReadyEvent);
        m_ThreadReadyEvent = INVALID_HANDLE_VALUE;

        if (INVALID_SOCKET == m_Socket)
        {
            m_IsThreadTerminated = true;
            WaitForSingleObject(m_ThreadHandle, INFINITE);

            CloseHandle(m_ThreadHandle);
            m_ThreadHandle = NULL;
            m_ThreadId     = 0;
        }
    }

    return INVALID_SOCKET != m_Socket;
}

void    CYCSimpleTCPConnection::Close()
{
    CSingleLock LWorkingThreadLocker(&m_WorkingThreadLocker, TRUE);

    if (m_ThreadHandle)
    {
        TRACE("CYCSimpleTCPConnection::Close().\n");
        ASSERT(m_ThreadId != GetCurrentThreadId());

        HANDLE  LThreadHandle = m_ThreadHandle;

        m_IsThreadTerminated = true;
        m_ThreadHandle       = NULL;
        m_ThreadId           = 0;

        LWorkingThreadLocker.Unlock();

        WaitForSingleObject(LThreadHandle, INFINITE);
        CloseHandle(LThreadHandle);
    }
}

int     CYCSimpleTCPConnection::Read(OUT void *ABuff, int ABuffSize)
{
    if (INVALID_SOCKET != m_Socket)
    {
        CSingleLock LLocker(&m_RecvBufferLocker, TRUE);

        if (ABuff && ABuffSize > 0)
            return m_RecvBuffer.ReadFront(ABuff, ABuffSize, true);

        return m_RecvBuffer.BufferSize();
    }

    return 0;
}

int     CYCSimpleTCPConnection::Write(const void *ABuff, int ABuffSize)
{
    if (INVALID_SOCKET != m_Socket && ABuff && ABuffSize > 0)
    {
        CSingleLock LLocker(&m_SendBufferLocker, TRUE);

        return m_SendBuffer.WriteBack(ABuff, ABuffSize);
    }

    return 0;
}

void    CYCSimpleTCPConnection::PurgeBuffer(bool AIsPurgeSend, bool AIsPurgeRecv)
{
    if (AIsPurgeSend)
    {
        CSingleLock LLocker(&m_SendBufferLocker, TRUE);

        m_SendBuffer.Clear();
    }

    if (AIsPurgeRecv)
    {
        CSingleLock LLocker(&m_RecvBufferLocker, TRUE);

        m_RecvBuffer.Clear();
    }
}

#ifdef _DEBUG
void    CYCSimpleTCPConnection::DefaultHandleSocketError(LPCSTR AOperationText)
#else
void    CYCSimpleTCPConnection::DefaultHandleSocketError()
#endif
{
    const int   LSocketErrorCode = WSAGetLastError();
    LPCSTR      LSocketErrorMsg  = YCFormatWSAErrorCodeText(LSocketErrorCode);


    if (LSocketErrorCode)
    {
        if (m_EventSinker)
            m_EventSinker->OnTCPConnectionError(this, LSocketErrorCode, LSocketErrorMsg);

#ifdef _DEBUG
        TRACE("%s %s\n", AOperationText, LSocketErrorMsg);
#endif
    }
}

UINT    CYCSimpleTCPConnection::ThreadExecute()
{
    // SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);

    m_IsThreadTerminated = false;


    bool LIsSucc = true;

    //========================= 連線
    const bool LIsConnected = PrivOpen();


    // 設定連線完成通知事件
    if (INVALID_HANDLE_VALUE != m_ThreadReadyEvent)
        ::SetEvent(m_ThreadReadyEvent);


    if (LIsConnected)
    {
        while (!m_IsThreadTerminated && LIsSucc)
        {
            fd_set  LFDSetWrite;
            fd_set  LFDSetRead;
            fd_set  LFDSetError;

            FD_ZERO(&LFDSetRead);
            FD_ZERO(&LFDSetWrite);
            FD_ZERO(&LFDSetError);

            FD_SET(m_Socket, &LFDSetRead);
            FD_SET(m_Socket, &LFDSetWrite);
            FD_SET(m_Socket, &LFDSetError);

            timeval     LTimeout;

            LTimeout.tv_sec  = 0;
            LTimeout.tv_usec = 0;


            if (select(NULL, &LFDSetRead, &LFDSetWrite, &LFDSetError, &LTimeout) == SOCKET_ERROR)
            {
                LIsSucc = false;
                __DefaultHandleSocketError("CYCSimpleTCPConnection::ThreadExecute() select() fail.");
            }
            else
            {
                bool LIsNeedSleep = true;


                if (FD_ISSET(m_Socket, &LFDSetRead))
                {
                    LIsSucc &= PrivRead();
                    LIsNeedSleep = false;
                }

                if (LIsSucc && FD_ISSET(m_Socket, &LFDSetWrite))
                {
                    int LWriteCount = 0;

                    LIsSucc &= PrivWrite(&LWriteCount);

                    if (LIsSucc && LWriteCount)
                        LIsNeedSleep = false;
                }

                if (LIsSucc && FD_ISSET(m_Socket, &LFDSetError))
                {
                    LIsSucc = false;
                    __DefaultHandleSocketError("");
                    LIsNeedSleep = false;
                }

                if (LIsSucc && LIsNeedSleep)
                    Sleep(1);
            }

        } // while (!m_IsThreadTerminated && LIsSucc)

        //========================= 斷線
        PrivClose();

    } // if (LIsConnected)
    else
    {
        LIsSucc = false;
        TRACE("CYCSimpleTCPConnection is not connected.\n");
    }

    m_IsThreadTerminated = true;

    return LIsSucc ? TRUE : FALSE;
}

bool    CYCSimpleTCPConnection::PrivOpen()
{
    ASSERT(INVALID_SOCKET == m_Socket);

    bool LRslt = false; 

    if (INVALID_SOCKET == m_Socket)
    {
        LRslt = true;

        SOCKET  LSocket = INVALID_SOCKET;

        // Create socket
        LRslt = OnCreateSocket(LSocket) && LSocket != INVALID_SOCKET;

        // Set socket to non-blocking mode
        if (LRslt)
        {
            u_long  LNonBlocking = 1;

            LRslt = ioctlsocket(LSocket, FIONBIO, &LNonBlocking) != SOCKET_ERROR;

            if (!LRslt)
                __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivOpen() ioctlsocket() fail.");
        }

        // Set socket option handshake
        if (LRslt)
        {
            linger LLinger;

            LLinger.l_onoff  = 1;
            LLinger.l_linger = 3; // wait 3 seconds for TCP handshake

            LRslt = setsockopt(LSocket, SOL_SOCKET, SO_LINGER, (char*)&LLinger, sizeof(LLinger)) != SOCKET_ERROR;

            if (!LRslt)
                __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivOpen() setsockopt(SO_LINGER) fail.");
        }

        // Set socket TCP_NODELAY
        if (LRslt)
        {
            const BOOL LIsTCPNoDelay = (m_IsTCPNoDelay ? TRUE : FALSE);

            LRslt = setsockopt(LSocket, IPPROTO_TCP, TCP_NODELAY, (char *)&LIsTCPNoDelay, sizeof(LIsTCPNoDelay)) != SOCKET_ERROR;

            if (!LRslt)
                __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivOpen() setsockopt(TCP_NODELAY) fail.");
        }

        // connect
        if (LRslt)
            LRslt = OnConnectSocket(LSocket);

        // test
        if (LRslt)
            LRslt = PrivTestConnection(LSocket);


        if (LRslt)
        {
            sockaddr_in LSockAddrIn;
            int         LSockAddrInSize = sizeof(LSockAddrIn);

            LRslt = getsockname(LSocket, reinterpret_cast<sockaddr *>(&LSockAddrIn), &LSockAddrInSize) != SOCKET_ERROR;

            if (LRslt)
            {
                m_LocalIP   = inet_ntoa(LSockAddrIn.sin_addr);
                m_LocalPort = LSockAddrIn.sin_port;
            }
            else
            {
                __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivOpen() getsockname() fail.");
            }
        }

        if (LRslt)
        {
            m_Socket = LSocket;

            if (m_EventSinker)
                m_EventSinker->OnTCPConnectionConnect(this);
        }
        else if (INVALID_SOCKET != LSocket)
        {
            if (closesocket(LSocket) == SOCKET_ERROR)
                __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivOpen() closesocket() fail.");
        }
    }

    return LRslt;
}

void    CYCSimpleTCPConnection::PrivClose()
{
    TRACE("CYCSimpleTCPConnection::PrivClose().\n");

    SOCKET  LSocket = m_Socket;

    m_Socket = INVALID_SOCKET;


    const bool LIsCallEventSinker = (INVALID_SOCKET != LSocket);

    if (INVALID_SOCKET != LSocket)
    {
        if (::shutdown(LSocket, SD_SEND) == SOCKET_ERROR)
            __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivClose() shutdown() fail.");

        OnDisconnectSocket(LSocket);

        if (::closesocket(LSocket) == SOCKET_ERROR)
            __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivClose() closesocket() fail.");

        OnDestroySocket(LSocket);
    }

    if (LIsCallEventSinker && m_EventSinker)
        m_EventSinker->OnTCPConnectionDisconnect(this);
}

bool    CYCSimpleTCPConnection::PrivTestConnection(SOCKET ASocket)
{
    bool LRslt = true;

    timeval LTimeout;

    LTimeout.tv_sec  = m_ConnectTimeoutMSec / 1000;
    LTimeout.tv_usec = (m_ConnectTimeoutMSec % 1000) * 1000;

    fd_set  LFDSetRead;
    fd_set  LFDSetWrite;
    fd_set  LFDSetError;

    FD_ZERO(&LFDSetRead);
    FD_ZERO(&LFDSetWrite);
    FD_ZERO(&LFDSetError);

    FD_SET(ASocket, &LFDSetRead);
    FD_SET(ASocket, &LFDSetWrite);
    FD_SET(ASocket, &LFDSetError);

    switch (select(NULL, &LFDSetRead, &LFDSetWrite, &LFDSetError, &LTimeout))
    {
    case 0 : // Timeout
        TRACE("CYCSimpleTCPConnection::PrivRead() select() timeout.\n");

    case SOCKET_ERROR :
        LRslt = false;
        __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivRead() select() fail.");
        break;
    }


    if (LRslt)
    {
        LRslt = false;

        if (FD_ISSET(ASocket, &LFDSetError))
        {
            __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivRead() select() succ. exceptfds is set.");
        }

        if (FD_ISSET(ASocket, &LFDSetRead))
        {
            TRACE("CYCSimpleTCPConnection::PrivRead() select() succ. readfds is set.\n");
        }

        if (FD_ISSET(ASocket, &LFDSetWrite))
        {
            LRslt = true;
            TRACE("CYCSimpleTCPConnection::PrivRead() select() succ. writefds is set.\n");
        }
    }

    TRACE("CYCSimpleTCPConnection::PrivTestConnection() %s.\n", LRslt ? "succ" : "false");

    return LRslt;
}

bool    CYCSimpleTCPConnection::PrivRead()
{
    bool LRslt = INVALID_SOCKET != m_Socket;

    if (LRslt)
    {
        const int   LBufferSize = YCTCPCLIENT_DefaultBufferSize;
        char* const LBuffer     = new char[LBufferSize];

        if (LBuffer)
        {
            ZeroMemory(LBuffer, LBufferSize);

            // 謮取資料
            const int LRecvLen = recv(m_Socket, LBuffer, LBufferSize, 0);

            // 檢查讀取結果
            //
            // 1. 平順的斷線
            if (0 == LRecvLen) // gracefully disconnected
            {
                LRslt = false;
                TRACE("CYCSimpleTCPConnection::PrivRead() recv() fail. Disconnect gracefully.\n");
            }
            // 2. 發生錯誤
            else if (SOCKET_ERROR == LRecvLen)
            {
                LRslt = false;
                __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivRead() recv() fail.");
            }
            // 3. 成功讀取
            else
            {
                TRACE("CYCSimpleTCPConnection::PrivRead() recv() %d bytes.\n", LRecvLen);

                CSingleLock LLocker(&m_RecvBufferLocker, TRUE);

                TRACE("\n LBuffer = %s \n", LBuffer);

                m_RecvBuffer.WriteBack(LBuffer, LRecvLen);

                LLocker.Unlock();

                if (LRecvLen > 0 && m_EventSinker)
                    m_EventSinker->OnTCPConnectionRead(this, LBuffer, LRecvLen);
            }

            delete [] LBuffer;
        }
    }

    return LRslt;
}

bool    CYCSimpleTCPConnection::PrivWrite(OUT int *AWriteCount)
{
    bool LRslt = INVALID_SOCKET != m_Socket;

    if (LRslt)
    {
        if (AWriteCount)
            *AWriteCount = 0;

        CSingleLock LLocker(&m_SendBufferLocker, TRUE);
        const int   LBufferSize = min(YCTCPCLIENT_DefaultBufferSize, m_SendBuffer.BufferSize());

        if (LBufferSize > 0)
        {
            char *LBuffer = new char[LBufferSize];

            if (LBuffer)
            {
                m_SendBuffer.ReadFront(LBuffer, LBufferSize, false);

                LLocker.Unlock();


                // 送出資料
                const int LSendLen = send(m_Socket, LBuffer, LBufferSize, 0);


                // 檢查送出資料的結果
                //
                // 1. 平順的斷線
                if (0 == LSendLen)
                {
                    LRslt = false;
                    TRACE("CYCSimpleTCPConnection::PrivRead() send() fail. Disconnect gracefully.\n");
                }
                // 2. 發生錯誤
                else if (SOCKET_ERROR == LSendLen)
                {
                    LRslt = false;
                    __DefaultHandleSocketError("CYCSimpleTCPConnection::PrivRead() send() fail.");
                }
                // 3. 成功送出
                else
                {
                    TRACE("CYCSimpleTCPConnection::PrivRead() send() %d bytes.\n", LSendLen);

                    LLocker.Lock();

                    m_SendBuffer.RemoveFront(LSendLen);

                    LLocker.Unlock();

                    if (LSendLen > 0 && m_EventSinker)
                        m_EventSinker->OnTCPConnectionWrite(this, LBuffer, LSendLen);

                    if (AWriteCount)
                        *AWriteCount = LSendLen;

                }

                delete [] LBuffer;
            }
        }

        return LRslt;
    }

    return LRslt;
}
//
// CYCSimpleTCPClientConnection
////////////////////////////////////////////////////
