#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")


class CYCSimpleTCPConnection;


#define   VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionConnect()                    virtual void OnTCPConnectionConnect(CYCSimpleTCPConnection *ASender)
#define IMPLEMENT_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionConnect(AClass)              void AClass::OnTCPConnectionConnect(CYCSimpleTCPConnection *ASender)
#define  OVERRIDE_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionConnect                      VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionConnect


#define   VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionDisconnect()                 virtual void OnTCPConnectionDisconnect(CYCSimpleTCPConnection *ASender)
#define IMPLEMENT_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionDisconnect(AClass)           void AClass::OnTCPConnectionDisconnect(CYCSimpleTCPConnection *ASender)
#define  OVERRIDE_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionDisconnect                   VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionDisconnect


#define   VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionRead()                       virtual void OnTCPConnectionRead(CYCSimpleTCPConnection *ASender, LPCVOID AData, int ADataSize)
#define IMPLEMENT_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionRead(AClass)                 void AClass::OnTCPConnectionRead(CYCSimpleTCPConnection *ASender, LPCVOID AData, int ADataSize)
#define  OVERRIDE_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionRead                         VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionRead


#define   VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionWrite()                      virtual void OnTCPConnectionWrite(CYCSimpleTCPConnection *ASender, LPCVOID AData, int ADataSize)
#define IMPLEMENT_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionWrite(AClass)                void AClass::OnTCPConnectionWrite(CYCSimpleTCPConnection *ASender, LPCVOID AData, int ADataSize)
#define  OVERRIDE_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionWrite                        VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionWrite


#define   VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionError()                      virtual void OnTCPConnectionError(CYCSimpleTCPConnection *ASender, int AErrorCode, LPCSTR AErrorMessage)
#define IMPLEMENT_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionError(AClass)                void AClass::OnTCPConnectionError(CYCSimpleTCPConnection *ASender, int AErrorCode, LPCSTR AErrorMessage)
#define  OVERRIDE_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionError                        VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionError



__interface IYCSimpleTCPConnectionEventSinker
{
public:
    VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionConnect()    = NULL;
    VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionDisconnect() = NULL;
    VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionRead()       = NULL;
    VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionWrite()      = NULL;
    VIRTUAL_IYCSimpleTCPConnectionEventSinker_OnTCPConnectionError()      = NULL;
};


#if 0
#define   VIRTUAL_CYCSimpleTCPConnection_OnOpen()                       virtual bool OnOpen(OUT SOCKET &ASocket)
#define IMPLEMENT_CYCSimpleTCPConnection_OnOpen(AClass)                 bool AClass::OnOpen(OUT SOCKET &ASocket)
#define  OVERRIDE_CYCSimpleTCPConnection_OnOpen                         VIRTUAL_CYCSimpleTCPConnection_OnOpen

#define   VIRTUAL_CYCSimpleTCPConnection_OnClose()                      virtual void OnClose(SOCKET ASocket)
#define IMPLEMENT_CYCSimpleTCPConnection_OnClose(AClass)                void AClass::OnClose(SOCKET ASocket)
#define  OVERRIDE_CYCSimpleTCPConnection_OnClose                        VIRTUAL_CYCSimpleTCPConnection_OnClose
#endif

#define   VIRTUAL_CYCSimpleTCPConnection_OnCreateSocket()                   virtual bool OnCreateSocket(OUT SOCKET &ASocket)
#define IMPLEMENT_CYCSimpleTCPConnection_OnCreateSocket(AClass)             bool AClass::OnCreateSocket(OUT SOCKET &ASocket)
#define  OVERRIDE_CYCSimpleTCPConnection_OnCreateSocket                     VIRTUAL_CYCSimpleTCPConnection_OnCreateSocket

#define   VIRTUAL_CYCSimpleTCPConnection_OnConnectSocket()                  virtual bool OnConnectSocket(SOCKET ASocket)
#define IMPLEMENT_CYCSimpleTCPConnection_OnConnectSocket(AClass)            bool AClass::OnConnectSocket(SOCKET ASocket)
#define  OVERRIDE_CYCSimpleTCPConnection_OnConnectSocket                    VIRTUAL_CYCSimpleTCPConnection_OnConnectSocket

#define   VIRTUAL_CYCSimpleTCPConnection_OnDisconnectSocket()               virtual void OnDisconnectSocket(SOCKET ASocket)
#define IMPLEMENT_CYCSimpleTCPConnection_OnDisconnectSocket(AClass)         void AClass::OnDisconnectSocket(SOCKET ASocket)
#define  OVERRIDE_CYCSimpleTCPConnection_OnDisconnectSocket                 VIRTUAL_CYCSimpleTCPConnection_OnDisconnectSocket

#define   VIRTUAL_CYCSimpleTCPConnection_OnDestroySocket()                  virtual void OnDestroySocket(SOCKET ASocket)
#define IMPLEMENT_CYCSimpleTCPConnection_OnDestroySocket(AClass)            void AClass::OnDestroySocket(SOCKET ASocket)
#define  OVERRIDE_CYCSimpleTCPConnection_OnDestroySocket                    VIRTUAL_CYCSimpleTCPConnection_OnDestroySocket


class CYCSimpleTCPConnection : public CYCObject 
{
    friend unsigned __stdcall YCTCPConnectionThreadFunc(void *AArg);

    DECLARE_DYNAMIC(CYCSimpleTCPConnection)

public:
    static LPCSTR
        /**/    YCFormatWSAErrorCodeText(int AErrorCode);


    CYCSimpleTCPConnection();
    virtual ~CYCSimpleTCPConnection();


    // Peer IP
    LPCSTR      PeerIP() const;
    void        SetPeerIP(LPCSTR AValue);

    // Peer Port
    int         PeerPort() const;
    void        SetPeerPort(int AValue);

    // Connect timeout
    DWORD       ConnectTimeoutMSec() const;
    void        SetConnectTimeoutMSec(DWORD AValue);

    // Is TCP no delay(TCP_NODELAY option)
    bool        IsTCPNoDelay() const;
    void        SetIsTCPNoDelay(bool AValue);

    // Local IP
    LPCSTR      LocalIP() const;    

    // Local Port
    int         LocalPort() const;

    // Is Connected
    bool        IsConnected() const;

    // Event Sinker
    IYCSimpleTCPConnectionEventSinker*
        /**/    EventSinker() const;
    void        SetEventSinker(IYCSimpleTCPConnectionEventSinker *AValue);


    // Open connection
    bool        Open();

    // Disconnection
    void        Close();


    // Read
    int         Read(OUT void *ABuff, int ABuffSize);

    // Write
    int         Write(const void *ABuff, int ABuffSize);

    // Purge Buffer
    void        PurgeBuffer(bool AIsPurgeSend, bool AIsPurgeRecv);

protected:
#if 0
    VIRTUAL_CYCSimpleTCPConnection_OnOpen()  = NULL;
    VIRTUAL_CYCSimpleTCPConnection_OnClose() = NULL;
#endif
    VIRTUAL_CYCSimpleTCPConnection_OnCreateSocket()     = NULL;
    VIRTUAL_CYCSimpleTCPConnection_OnConnectSocket()    = NULL;
    VIRTUAL_CYCSimpleTCPConnection_OnDisconnectSocket() = NULL;
    VIRTUAL_CYCSimpleTCPConnection_OnDestroySocket()    = NULL;

#ifdef _DEBUG
    void        DefaultHandleSocketError(LPCSTR AOperationText);
#else
    void        DefaultHandleSocketError();
#endif

private:
    struct strYCInitWinsock2
    {
        strYCInitWinsock2();
        ~strYCInitWinsock2();
    };


    // Start WinSock2.
    static const strYCInitWinsock2
        /**/    m_InitWinsock2;


    //=========================== Properties
    CString     m_PeerIP;
    int         m_PeerPort;
    DWORD       m_ConnectTimeoutMSec;
    bool        m_IsTCPNoDelay;

    IYCSimpleTCPConnectionEventSinker
        /**/    *m_EventSinker;


    //=========================== Working Datas
    HANDLE      m_ThreadHandle;
    unsigned    m_ThreadId;
    bool        m_IsThreadTerminated;
    HANDLE      m_ThreadReadyEvent;

    SOCKET      m_Socket;
    CString     m_LocalIP;
    int         m_LocalPort;


    CYCMemoryBuffer
        /**/    m_SendBuffer;

    CCriticalSection
        /**/    m_SendBufferLocker;

    CYCMemoryBuffer
        /**/    m_RecvBuffer;

    CCriticalSection
        /**/    m_RecvBufferLocker;


    CCriticalSection
        /**/    m_WorkingThreadLocker;


    //=========================== Functions
    UINT        ThreadExecute();

    bool        PrivOpen();
    void        PrivClose();
    bool        PrivTestConnection(SOCKET ASocket);
    bool        PrivRead();
    bool        PrivWrite(OUT int *AWriteCount);

};


#ifdef _DEBUG
    #define __DefaultHandleSocketError(Y)       DefaultHandleSocketError(Y)
#else
    #define __DefaultHandleSocketError(Y)       DefaultHandleSocketError()
#endif
