#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


class CYCSimpleTCPServerConnection : public CYCSimpleTCPConnection 
{
    friend class CYCSimpleTCPServer;

    DECLARE_DYNAMIC(CYCSimpleTCPServerConnection)

public:
    CYCSimpleTCPServerConnection();
    virtual ~CYCSimpleTCPServerConnection();

protected:
    OVERRIDE_CYCSimpleTCPConnection_OnCreateSocket();
    OVERRIDE_CYCSimpleTCPConnection_OnConnectSocket();
    OVERRIDE_CYCSimpleTCPConnection_OnDisconnectSocket();
    OVERRIDE_CYCSimpleTCPConnection_OnDestroySocket();

private:
    SOCKET  m_ServerConnectionSocket;

};


#define   VIRTUAL_IYCSimpleTCPServerEventSinker_OnTCPServerClientConnect()                  virtual void OnTCPServerClientConnect(CObject *ASender, CYCSimpleTCPServerConnection **ACustomConnection)
#define IMPLEMENT_IYCSimpleTCPServerEventSinker_OnTCPServerClientConnect(AClass)            void AClass::OnTCPServerClientConnect(CObject *ASender, CYCSimpleTCPServerConnection **ACustomConnection)
#define  OVERRIDE_IYCSimpleTCPServerEventSinker_OnTCPServerClientConnect                    VIRTUAL_IYCSimpleTCPServerEventSinker_OnTCPServerClientConnect


#define   VIRTUAL_IYCSimpleTCPServerEventSinker_OnTCPServerListen()                         virtual void OnTCPServerListen(CObject *ASender)
#define IMPLEMENT_IYCSimpleTCPServerEventSinker_OnTCPServerListen(AClass)                   void AClass::OnTCPServerListen(CObject *ASender)
#define  OVERRIDE_IYCSimpleTCPServerEventSinker_OnTCPServerListen                           VIRTUAL_IYCSimpleTCPServerEventSinker_OnTCPServerListen


#define   VIRTUAL_IYCSimpleTCPServerEventSinker_OnTCPServerError()                          virtual void OnTCPServerError(CObject *ASender, int AErrorCode, LPCSTR AErrorMessage)
#define IMPLEMENT_IYCSimpleTCPServerEventSinker_OnTCPServerError(AClass)                    void AClass::OnTCPServerError(CObject *ASender, int AErrorCode, LPCSTR AErrorMessage)
#define  OVERRIDE_IYCSimpleTCPServerEventSinker_OnTCPServerError                            VIRTUAL_IYCSimpleTCPServerEventSinker_OnTCPServerError


__interface IYCSimpleTCPServerEventSinker
{
public:
    VIRTUAL_IYCSimpleTCPServerEventSinker_OnTCPServerClientConnect() = NULL;
    VIRTUAL_IYCSimpleTCPServerEventSinker_OnTCPServerListen()        = NULL;
    VIRTUAL_IYCSimpleTCPServerEventSinker_OnTCPServerError()         = NULL;
};


class CYCSimpleTCPServer : public CYCObject
{
    friend unsigned __stdcall YCTCPServerThreadFunc(void *AArg);

    DECLARE_DYNAMIC(CYCSimpleTCPServer)

public:
    CYCSimpleTCPServer();
    virtual ~CYCSimpleTCPServer();


    // Local IP
    LPCSTR      LocalIP() const;
    void        SetLocalIP(LPCSTR AValue);

    // Local Port
    int         LocalPort() const;
    void        SetLocalPort(int AValue);


    // Is Connected
    bool        IsListened() const;

    // Event Sinker
    IYCSimpleTCPServerEventSinker*
        /**/    EventSinker() const;
    void        SetEventSinker(IYCSimpleTCPServerEventSinker *AValue);


    // Open connection
    bool        Open();

    // Disconnection
    void        Close();


private:
    //=========================== Properties
    CString     m_LocalIP;
    int         m_LocalPort;

    IYCSimpleTCPServerEventSinker
        /**/    *m_EventSinker;

    //=========================== Working Datas
    HANDLE      m_ThreadReadyEvent;
    HANDLE      m_ThreadHandle;
    unsigned    m_ThreadId;
    bool        m_IsThreadTerminated;
    SOCKET      m_ListenSocket;


    //=========================== Functions
    UINT        ThreadExecute();

    bool        PrivOpen();
    void        PrivClose();

};