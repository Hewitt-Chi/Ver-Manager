#include "stdafx.h"


#include "YCUtils.h"
#include "YCObject.h"
#include "YCCompletionObject.h"
#include "YCThread.h"
#include "YCMemoryBuffer.h"
#include "YCSimpleTCPConnection.h"
#include "YCSimpleTCPServer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////////////////
// CYCSimpleTCPServerConnection
//
IMPLEMENT_DYNAMIC(CYCSimpleTCPServerConnection, CYCSimpleTCPConnection)


CYCSimpleTCPServerConnection::CYCSimpleTCPServerConnection()
: CYCSimpleTCPConnection()
, m_ServerConnectionSocket(INVALID_SOCKET)
{
}

CYCSimpleTCPServerConnection::~CYCSimpleTCPServerConnection()
{
    ASSERT(m_ServerConnectionSocket == INVALID_SOCKET);

    Close();
}

IMPLEMENT_CYCSimpleTCPConnection_OnCreateSocket(CYCSimpleTCPServerConnection)
{
    ASSERT(m_ServerConnectionSocket != INVALID_SOCKET);

    ASocket = m_ServerConnectionSocket;

    return ASocket != INVALID_SOCKET;
}

IMPLEMENT_CYCSimpleTCPConnection_OnConnectSocket(CYCSimpleTCPServerConnection)
{
    if (ASocket != INVALID_SOCKET)
    {
        sockaddr_in LSockAddrIn;
        int         LSockAddrInSize = sizeof(LSockAddrIn);

        // 取得peer的ip和port no
        if (getpeername(ASocket, reinterpret_cast<sockaddr *>(&LSockAddrIn), &LSockAddrInSize) != SOCKET_ERROR)
        {
            SetPeerIP(inet_ntoa(LSockAddrIn.sin_addr));
            SetPeerPort(LSockAddrIn.sin_port);

            return true;
        }
        else
        {
            __DefaultHandleSocketError("CYCSimpleTCPServerConnection::OnConnectSocket() getpeername() fail.");
        }
    }

    return false;
}

IMPLEMENT_CYCSimpleTCPConnection_OnDisconnectSocket(CYCSimpleTCPServerConnection)
{
}

IMPLEMENT_CYCSimpleTCPConnection_OnDestroySocket(CYCSimpleTCPServerConnection)
{
    m_ServerConnectionSocket = INVALID_SOCKET;
}
//
// CYCSimpleTCPServerConnection
////////////////////////////////////////////////////


////////////////////////////////////////////////////
// CYCSimpleTCPServer
//
IMPLEMENT_DYNAMIC(CYCSimpleTCPServer, CYCObject)


CYCSimpleTCPServer::CYCSimpleTCPServer()
: CYCObject()
, m_LocalIP("127.0.0.1")
, m_LocalPort(9979)
, m_EventSinker(NULL)
, m_ThreadReadyEvent(INVALID_HANDLE_VALUE)
, m_ThreadHandle(NULL)
, m_ThreadId(0)
, m_IsThreadTerminated(true)
, m_ListenSocket(INVALID_SOCKET)
{
}

CYCSimpleTCPServer::~CYCSimpleTCPServer()
{
    Close();
}

LPCSTR  CYCSimpleTCPServer::LocalIP() const
{
    return m_LocalIP;
}

void    CYCSimpleTCPServer::SetLocalIP(LPCSTR AValue)
{
    m_LocalIP = AValue;
}

int     CYCSimpleTCPServer::LocalPort() const
{
    return m_LocalPort;
}

void    CYCSimpleTCPServer::SetLocalPort(int AValue)
{
    m_LocalPort = AValue;
}

bool    CYCSimpleTCPServer::IsListened() const
{
    return m_ListenSocket != INVALID_SOCKET;
}

IYCSimpleTCPServerEventSinker*
/**/    CYCSimpleTCPServer::EventSinker() const
{
    return m_EventSinker;
}

void    CYCSimpleTCPServer::SetEventSinker(IYCSimpleTCPServerEventSinker *AValue)
{
    m_EventSinker = AValue;
}

bool    CYCSimpleTCPServer::Open()
{
    // 檢查之前的thread是否已結束了，如是則清除資源
    if (m_ThreadHandle && WaitForSingleObject(m_ThreadHandle, INFINITE) == WAIT_OBJECT_0)
    {
        CloseHandle(m_ThreadHandle);

        m_IsThreadTerminated = true;
        m_ThreadHandle       = NULL;
        m_ThreadId           = 0;
    }


    ASSERT(!m_ThreadHandle);

    if (!m_ThreadHandle)
    {
        m_ThreadReadyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

        m_ThreadHandle     = (HANDLE)_beginthreadex(NULL, 0, &YCTCPServerThreadFunc, this, 0, &m_ThreadId);

        WaitForSingleObject(m_ThreadReadyEvent, INFINITE);
        CloseHandle(m_ThreadReadyEvent);
        m_ThreadReadyEvent = INVALID_HANDLE_VALUE;

        if (INVALID_SOCKET == m_ListenSocket)
        {
            TRACE("Open listen socket fail.\n");

            m_IsThreadTerminated = true;
            WaitForSingleObject(m_ThreadHandle, INFINITE);

            CloseHandle(m_ThreadHandle);
            m_ThreadHandle = NULL;
            m_ThreadId     = 0;

            return false;
        }

        return true;
    }

    return false;
}

void    CYCSimpleTCPServer::Close()
{
    if (m_ThreadHandle)
    {
        TRACE("CYCSimpleTCPServer::Close().\n");
        ASSERT(m_ThreadId != GetCurrentThreadId());

        HANDLE  LThreadHandle = m_ThreadHandle;

        m_IsThreadTerminated = true;
        m_ThreadHandle       = NULL;
        m_ThreadId           = 0;

        WaitForSingleObject(LThreadHandle, INFINITE);
        CloseHandle(LThreadHandle);
    }
}

unsigned __stdcall
/**/    YCTCPServerThreadFunc(void *AArg)
{
    CYCSimpleTCPServer  *LArg = reinterpret_cast<CYCSimpleTCPServer *>(AArg);

    UINT    LRslt = 0;

    if (LArg)
        LRslt = LArg->ThreadExecute();

    return LRslt;
}

UINT    CYCSimpleTCPServer::ThreadExecute()
{
    // SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
    m_IsThreadTerminated = false;


    bool LIsSucc = true;

    //========================= 連線
    const bool LIsListen = PrivOpen();


    // 設定連線完成通知事件
    if (m_ThreadReadyEvent != INVALID_HANDLE_VALUE)
        SetEvent(m_ThreadReadyEvent);

    TRACE("CYCSimpleTCPServer::ThreadExecute() thread ready.\n");


    if (LIsListen)
    {
        do
        {
            //========================== check acceptable
            for (bool LIsAcceptable = false; !LIsAcceptable && !m_IsThreadTerminated; )
            {
                fd_set  LReadSet;

                FD_ZERO(&LReadSet);
                FD_SET(m_ListenSocket, &LReadSet);

                timeval LTimeoutVal;

                LTimeoutVal.tv_sec  = 0; // Zero LTimeoutVal (poll)
                LTimeoutVal.tv_usec = 1000;

                if (select(NULL, &LReadSet, NULL, NULL, &LTimeoutVal) == 1)
                    LIsAcceptable = true;
            }

            TRACE("A client connection is came in.\n");

            //========================== accept
            if (!m_IsThreadTerminated)
            {
                // Accept a client socket
                SOCKET LConnectionSocket = accept(m_ListenSocket, NULL, NULL);

                if (LConnectionSocket != INVALID_SOCKET)
                {
                    // 取得connection物件
                    CYCSimpleTCPServerConnection    *LConnection = NULL;

                    if (m_EventSinker)
                        m_EventSinker->OnTCPServerClientConnect(this, &LConnection);

                    if (LConnection)
                    {
                        LConnection->m_ServerConnectionSocket = LConnectionSocket;
                        LConnection->Open();
                    }
                    else
                    {
                        shutdown(LConnectionSocket, SD_SEND);
                        closesocket(LConnectionSocket);

                        TRACE("A client connection is refused.\n");
                    }
                }
            }
        }
        while (!m_IsThreadTerminated);


        // No longer need server socket
        PrivClose();
    }

    m_IsThreadTerminated = true;

    return LIsSucc ? TRUE : FALSE;
}

bool    CYCSimpleTCPServer::PrivOpen()
{
    SOCKET      LListenSocket = INVALID_SOCKET;
    addrinfo    *LAddrInfoResult = NULL;
    addrinfo    LAddrInfoHints;
    int         LResultInt;


    ZeroMemory(&LAddrInfoHints, sizeof(LAddrInfoHints));
    LAddrInfoHints.ai_family   = AF_INET;
    LAddrInfoHints.ai_socktype = SOCK_STREAM;
    LAddrInfoHints.ai_protocol = IPPROTO_TCP;
    LAddrInfoHints.ai_flags    = AI_PASSIVE;

    CString LPortText;

    LPortText.Format("%d", m_LocalPort);

    // Resolve the server address and port
    LResultInt = getaddrinfo(NULL, LPortText, &LAddrInfoHints, &LAddrInfoResult);

    if (LResultInt != 0)
    {
        TRACE("getaddrinfo failed: %d\n", LResultInt);
        return false;
    }

    // Create a SOCKET for connecting to server
    LListenSocket = socket(LAddrInfoResult->ai_family, LAddrInfoResult->ai_socktype, LAddrInfoResult->ai_protocol);

    if (LListenSocket == INVALID_SOCKET)
    {
        TRACE("socket failed: %ld\n", WSAGetLastError());
        freeaddrinfo(LAddrInfoResult);
        return false;
    }


    // Setup the TCP listening socket
    LResultInt = bind(LListenSocket, LAddrInfoResult->ai_addr, (int)LAddrInfoResult->ai_addrlen);

    if (LResultInt == SOCKET_ERROR)
    {
        TRACE("bind failed: %d\n", WSAGetLastError());
        freeaddrinfo(LAddrInfoResult);
        closesocket(LListenSocket);
        return false;
    }

    freeaddrinfo(LAddrInfoResult);

    //========================== listen
    LResultInt = listen(LListenSocket, SOMAXCONN);

    if (LResultInt == SOCKET_ERROR)
    {
        TRACE("listen failed: %d\n", WSAGetLastError());
        closesocket(LListenSocket);
        return false;
    }

    m_ListenSocket = LListenSocket;

    if (m_EventSinker)
        m_EventSinker->OnTCPServerListen(this);

    return true;
}

void    CYCSimpleTCPServer::PrivClose()
{
    if (INVALID_SOCKET != m_ListenSocket)
        ::closesocket(m_ListenSocket);

    m_ListenSocket = INVALID_SOCKET;
}
//
// CYCSimpleTCPServer
////////////////////////////////////////////////////
