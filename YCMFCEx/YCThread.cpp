#include "StdAfx.h"

#include "YCObject.h"
#include "YCUtils.h"
#include "YCCompletionObject.h"
#include "YCThread.h"
#include <typeinfo.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#ifdef _DEBUG
LONG    strYCThreadICD::TotalCount = 0;
#endif


#define RS_ThreadCreated                "This thread is created."
#define RS_ThreadNotCreated             "This thread is not created."
#define RS_CreateThreadFail             "Create thread fail."


///////////////////////////////////////////
// CYCThreadProc
//
UINT __stdcall CYCThreadProc(void *AThreadObj)
{
    // 取出執行序物件
    CYCThread   *LThrdObj   = (CYCThread *)AThreadObj;
#if 0
    CString     LStr        = typeid(*LThrdObj).name();


    LStr.Delete(0, 6);
#else
    CString     LStr        = LThrdObj->GetRuntimeClass()->m_lpszClassName;
#endif

    TRACE("%s(%s).Execute().\n", LStr, LThrdObj->Name());

    try
    {
        // 執行執行序內容
        LThrdObj->m_ThreadReturnCode = LThrdObj->Execute();
    }
    catch (...) 
    {        
        TRACE("%s(%s).Execute() exception.\n", LStr, LThrdObj->Name());
    }

    // 終結執行緒
    LThrdObj->Terminate();
    TRACE("%s(%s).Execute() return.\n", LStr, LThrdObj->Name());

    // 取得執行序回傳碼
    const UINT LRslt = LThrdObj->m_ThreadReturnCode;

    return LRslt;
}
//
// CACThreadControllerThreadProc
///////////////////////////////////////////



///////////////////////////////////////////
// CYCThread
//
IMPLEMENT_DYNAMIC(CYCThread, CObject)


CYCThread::CYCThread(void)
: CObject()
, m_ThreadHandle(NULL)
, m_ThreadId(0)
, m_IsTerminated(true)
, m_IsGracefulStop(false)
, m_IsSuspended(true)
, m_ThreadReturnCode(0)
, m_Name("")
{
}

CYCThread::~CYCThread(void)
{
    Delete();
}

bool    CYCThread::Create(LPCSTR AName/* = NULL*/, bool AIsCreateSuspended/* = true*/)
{
    ASSERT(!m_ThreadHandle);

    if (!m_ThreadHandle) 
    {
        m_Name          = AName;
        m_IsTerminated  = false;
        m_IsSuspended   = AIsCreateSuspended;
        m_ThreadHandle  = (HANDLE)(ULONG_PTR)_beginthreadex(NULL, 0, CYCThreadProc, this, AIsCreateSuspended ? CREATE_SUSPENDED : 0, &m_ThreadId);

        if (!m_ThreadHandle)
        {
            m_Name          = "";
            m_IsTerminated  = true;
            m_IsSuspended   = true;
        }
    }

    return m_ThreadHandle != NULL;
}

void    CYCThread::Delete()
{
    OnDelete();

    if (m_ThreadHandle)
    {
        TerminateAndWaitFor();
        CloseHandle(m_ThreadHandle);
    }

    m_ThreadHandle = NULL;
    m_ThreadId     = 0;
}

LPCSTR  CYCThread::Name() const
{
    return m_Name;
}

HANDLE  CYCThread::ThreadHandle() const
{
    return m_ThreadHandle;
}

UINT    CYCThread::ThreadId() const
{
    return m_ThreadId;
}

UINT    CYCThread::ThreadReturnCode() const
{
    return m_ThreadReturnCode;
}

void    CYCThread::Terminate()
{
    m_IsTerminated = true;

    this->PostThreadMessage(WM_QUIT, 0, 0);

    if (IsSuspended())
        Resume();
}

bool    CYCThread::IsTerminated() const
{
    return m_IsTerminated;
}

void    CYCThread::Suspend()
{
    m_IsSuspended = true;

    if (m_ThreadHandle)
        ::SuspendThread(m_ThreadHandle);
}

bool    CYCThread::IsSuspended() const
{
    return m_IsSuspended;
}

void    CYCThread::StopGracefully()
{
    m_IsGracefulStop = true;
}

bool    CYCThread::IsGracefulStop() const
{
    return m_IsGracefulStop;
}

bool    CYCThread::IsThreadExit() const
{
    return !m_ThreadHandle || ::WaitForSingleObject(m_ThreadHandle, 0) == WAIT_OBJECT_0;
}

void    CYCThread::Resume()
{
    if (m_ThreadHandle)
        m_IsSuspended = ::ResumeThread(m_ThreadHandle) < 2;
}

bool    CYCThread::PostThreadMessage(UINT AMessage, WPARAM AWParam, LPARAM ALParam)
{
    if (m_ThreadHandle
        && WaitForSingleObject(m_ThreadHandle, 0) == WAIT_TIMEOUT
        && (AMessage == WM_QUIT || AMessage == WM_NULL || !m_IsTerminated))
    {
        return ::PostThreadMessage(m_ThreadId, AMessage, AWParam, ALParam) != 0;
    }

    return false;
}

bool    CYCThread::WaitForTerminated(DWORD ATimeoutMSec)
{
    ASSERT(::GetCurrentThreadId() != m_ThreadId);

    if (::GetCurrentThreadId() == m_ThreadId)
        return false;

    if (m_ThreadHandle)
        return WaitForSingleObject(m_ThreadHandle, ATimeoutMSec) == WAIT_OBJECT_0;

    return true;
}   

bool    CYCThread::TerminateAndWaitFor(DWORD ATimeoutMSec)
{
    Terminate();

    return WaitForTerminated(ATimeoutMSec);
}

bool    CYCThread::HandleMessage()
{
    MSG LMsg;

    if (::PeekMessage(&LMsg, 0, 0, 0, PM_REMOVE))
    {
        if (LMsg.message == WM_QUIT)
        {
            if (GetCurrentThreadId() == m_ThreadId && !IsTerminated())
                Terminate();

            return false;
        }
        else
        {
            ::TranslateMessage(&LMsg);
            ::DispatchMessage(&LMsg);
        }

        return true;
    }

    return false;
}

bool    CYCThread::ProcessMessage()
{
    MSG LMsg;

    if (::GetMessage(&LMsg, 0, 0, 0))
    {
        ::TranslateMessage(&LMsg);
        ::DispatchMessage(&LMsg);

        return true;
    }
    else 
    {
        if (GetCurrentThreadId() == m_ThreadId && !IsTerminated())
            Terminate();

        return false;
    }
}

void    CYCThread::ProcessMessages()
{
    while (HandleMessage()) ;
}

IMPLEMENT_CYCThread_OnDelete(CYCThread)
{
}
//
// CYCThread
///////////////////////////////////////////
