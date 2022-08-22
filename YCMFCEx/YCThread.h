#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

// Exception
enum enmYCThreadException
{
    YCT_Exception_Base = 100,
    YCT_Exception_ThreadCreated,
    YCT_Exception_ThreadNotCreated,
    YCT_Exception_CreateThreadFail,
    YCT_Exception_User = YCT_Exception_Base + 100
};



// 用來和執行緒溝通的Windows Message(If the thread has a message queue).
enum enmYCThreadICDMessage
{
    ////////////////////////////////////////////
    CM_ThreadICD = (WM_USER + 1997),
    // wParam : strYCThreadICD *
    // lParam : Reserved
    // return : Reserved
    //

    ////////////////////////////////////////////
    CM_NotifyThreadICD
    // wParam : ICD code
    // lParam : CYCCompletionObject
    // return : Reserved
    //
};


//////////////////////////////////////////////
// strYCThreadICD :
//   用來和執行緒溝通的基本資訊
//
struct strYCThreadICD
{
    // 碼
    const DWORD Code;

    // 完成此ICD
    const CYCCompletionHandle
        /**/    CompletionHandle;

    // 如果是動態生成的，則把此屬性設為true
    bool        IsAutoDelete;

    // 呼叫的執行緒id
    const DWORD CallingThreadId;


#ifdef _DEBUG
    // 維一編號(除錯用)
    const DWORD UID;

    static  LONG
        /**/    TotalCount;
#endif


    strYCThreadICD(DWORD ACode, CYCCompletionObject *ACompletionObject)
        : Code(ACode)
        , CompletionHandle(ACompletionObject)
        , IsAutoDelete(true)
#ifdef _DEBUG
        , UID(NewUID())
#endif
        , CallingThreadId(GetCurrentThreadId())
    {
#ifdef _DEBUG
        const LONG LTotalCount = InterlockedIncrement(&TotalCount);

        if (LTotalCount > 20)
            TRACE("---->static strYCThreadICD::TotalCount = %d\n", LTotalCount);
#endif
    }


    virtual ~strYCThreadICD()
    {
#ifdef _DEBUG
        const LONG LTotalCount = InterlockedDecrement(&TotalCount);

        if (LTotalCount > 20)
            TRACE("<----static strYCThreadICD::TotalCount = %d\n", LTotalCount);
#endif
    }

    inline void Delete()
    {
        if (IsAutoDelete)
            delete this;
    }

#ifdef _DEBUG
    inline DWORD NewUID()
    {
        static LONG LUIDSeed = 0;

        return static_cast<DWORD>(InterlockedIncrement(&LUIDSeed));
    }
#endif

    inline void Complete(LRESULT AResult)
    {
        if (CompletionHandle.IsNotNull())
            CompletionHandle->Complete(AResult);
    }
};


typedef std::deque<strYCThreadICD *>      TTreadICDDeque;
//
// strYCThreadICD :
//   用來和執行緒溝通的基本資訊
//////////////////////////////////////////////




//////////////////////////////////////////////
// CYCThread :
//   執行緒物件
//
#define   VIRTUAL_CYCThread_Execute()                           virtual UINT Execute()
#define IMPLEMENT_CYCThread_Execute(AClass)                     UINT AClass::Execute()
#define  OVERRIDE_CYCThread_Execute                             VIRTUAL_CYCThread_Execute

#define   VIRTUAL_CYCThread_OnDelete()                          virtual void OnDelete()
#define IMPLEMENT_CYCThread_OnDelete(AClass)                    void AClass::OnDelete()
#define  OVERRIDE_CYCThread_OnDelete                            VIRTUAL_CYCThread_OnDelete


class CYCThread : public CObject
{
    friend UINT __stdcall CYCThreadProc(void *AThreadObj);

    DECLARE_DYNAMIC(CYCThread)

public:
    CYCThread(void);
    virtual ~CYCThread(void);

    bool Create(LPCSTR AName = NULL, bool AIsCreateSuspended = true);
    void Delete();


    LPCSTR  Name() const;

    // Thread Handle
    HANDLE  ThreadHandle() const;

    // Thread Id
    UINT    ThreadId() const;

    // Thread return code
    UINT    ThreadReturnCode() const;

    // Terminate
    void    Terminate();
    bool    IsTerminated() const;

    // Suspend
    void    Suspend();
    bool    IsSuspended() const;

    // Graceful stop
    void    StopGracefully();
    bool    IsGracefulStop() const;

    //
    bool    IsThreadExit() const;

    // resume
    void    Resume();

    // post thread message
    bool    PostThreadMessage(UINT AMessage, WPARAM AWParam, LPARAM ALParam);

    // Wait for thread terminated
    bool    WaitForTerminated(DWORD ATimeoutMSec = INFINITE);

    // Terminate thread and wait it.
    bool    TerminateAndWaitFor(DWORD ATimeoutMSec = INFINITE);

    // peak a message and process
    bool    HandleMessage();

    // get a message and process
    bool    ProcessMessage();

    // process all messages
    void    ProcessMessages();


protected:

    VIRTUAL_CYCThread_Execute() = NULL;
    VIRTUAL_CYCThread_OnDelete();

private:
    HANDLE          m_ThreadHandle;
    UINT            m_ThreadId;
    bool volatile   m_IsTerminated;
    bool volatile   m_IsGracefulStop;
    bool volatile   m_IsSuspended;
    UINT            m_ThreadReturnCode;
    CString         m_Name;

};
//
// CYCThread :
//   執行緒物件
//////////////////////////////////////////////

