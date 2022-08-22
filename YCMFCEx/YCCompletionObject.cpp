#include "stdafx.h"
#include "YCUtils.h"


#include "YCObject.h"


#include "YCCompletionObject.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


////////////////////////////////////////////////////////////////////////////////////////////
// CYCCompletionObject
//
IMPLEMENT_DYNAMIC(CYCCompletionObject, CYCObject)


#ifdef _DEBUG

LONG    CYCCompletionObject::m_UniqueNoSeed = 0;
LONG    CYCCompletionObject::m_ObjectCount  = 0;

//#define __TRACE_Flow

#endif


CYCCompletionObject::CYCCompletionObject()
: CYCObject()
#ifdef _DEBUG
, m_UniqueNo(::InterlockedIncrement(&m_UniqueNoSeed))
, m_IsSetCompletion(false)
#endif
, m_Result(INT_MIN)
, m_Event(::CreateEvent(NULL, TRUE, FALSE, NULL))
{
#ifdef __TRACE_Flow

    ASSERT(m_Event && m_Event != INVALID_HANDLE_VALUE);
    TRACE("CYCCompletionObject(uid %d).m_Event = 0x%x\n", m_UniqueNo, PtrToUlong(m_Event));

    const LONG LTotalCount = InterlockedIncrement(&m_ObjectCount);

    if (LTotalCount > 20)
        TRACE("%s[%8u]---->CYCCompletionObject(uid %d)::m_ObjectCount = %d\n", CurrentTimeText(), GetCurrentThreadId(), m_UniqueNo, LTotalCount);

#endif
}

CYCCompletionObject::~CYCCompletionObject()
{
    if (m_Event)
        CloseHandle(m_Event);

#ifdef __TRACE_Flow

    const LONG LTotalCount = InterlockedDecrement(&m_ObjectCount);

    if (LTotalCount > 10)
        TRACE("%s[%8u]<----CYCCompletionObject(uid %d)::m_ObjectCount = %d\n", CurrentTimeText(), GetCurrentThreadId(), m_UniqueNo, LTotalCount);

#endif
}

const HANDLE
/**/    CYCCompletionObject::Event() const
{
    return m_Event;
}

LRESULT CYCCompletionObject::Result() const
{
    return m_Result;
}

void    CYCCompletionObject::Complete(LRESULT AResult)
{
#ifdef __TRACE_Flow

    TRACE("%s[%8u]---->CYCCompletionObject(uid %d, m_Event 0x%x)->Complete(%d)\n",
        CurrentTimeText(),
        GetCurrentThreadId(),
        m_UniqueNo,
        PtrToLong(m_Event),
        AResult);

#endif

    ASSERT(!m_IsSetCompletion);

    m_Result = AResult;

#ifdef _DEBUG

    m_IsSetCompletion = true;

    const BOOL LAPIRslt = ::SetEvent(m_Event);

    ASSERT(LAPIRslt);

#else

    ::SetEvent(m_Event);

#endif


#ifdef __TRACE_Flow
    TRACE("%s[%8u]<----CYCCompletionObject(uid %d, m_Event 0x%x)->Complete(%d)\n",
        CurrentTimeText(),
        GetCurrentThreadId(),
        m_UniqueNo,
        PtrToLong(m_Event),
        AResult,
        m_Result);
#endif
}

bool    CYCCompletionObject::WaitForCompletion(DWORD ATimeoutMSec, OUT LRESULT *AResult)
{
#ifdef __TRACE_Flow
    TRACE("%s[%8u]---->CYCCompletionObject(uid %d, m_Event 0x%x)->WaitForCompletion(%u, [0x%08X])\n",
         CurrentTimeText(),
         GetCurrentThreadId(),
         m_UniqueNo,
         PtrToLong(m_Event),
         ATimeoutMSec,
         PtrToUint(AResult));
#endif

    const DWORD LWaitRslt = ::WaitForSingleObject(m_Event, ATimeoutMSec);
    bool        LRslt     = false;

    switch (LWaitRslt)
    {
    case WAIT_OBJECT_0 :
        if (AResult)
            *AResult = m_Result;

        LRslt = true;
        break;

    case WAIT_TIMEOUT :
#ifdef __TRACE_Flow
        TRACE("%s[%8u]-----CYCCompletionObject(uid %d, m_Event 0x%x)->WaitForCompletion(%u, [0x%08X]) %s\n",
              CurrentTimeText(),
              GetCurrentThreadId(),
              m_UniqueNo,
              PtrToLong(m_Event),
              ATimeoutMSec,
              PtrToUint(AResult),
              "Timeout");
#endif
        break;

    case WAIT_FAILED :
#ifdef __TRACE_Flow

        YCTraceLastErrorText();
        ASSERT(FALSE);

#endif
        break;
    }

#ifdef __TRACE_Flow
    TRACE("%s[%8u]<----CYCCompletionObject(uid %d, m_Event 0x%x)->WaitForCompletion(%u, [0x%08X]) %s\n",
          CurrentTimeText(),
          GetCurrentThreadId(),
          m_UniqueNo,
          PtrToLong(m_Event),
          ATimeoutMSec,
          PtrToUint(AResult),
          LRslt ? "succ" : "fail");
#endif
#ifdef _DEBUG
    if (LWaitRslt != WAIT_TIMEOUT)
    {
        ASSERT(LWaitRslt == WAIT_OBJECT_0);
        ASSERT(m_IsSetCompletion);
    }
#endif

    return LRslt;
}

LRESULT CYCCompletionObject::WaitForCompletion(LRESULT ADefaultResult)
{
    LRESULT LRslt = ADefaultResult;

    VERIFY(WaitForCompletion(INFINITE, &LRslt));

    ASSERT(m_IsSetCompletion);

    return LRslt;
}

void    CYCCompletionObject::Reset(LRESULT ADefaultResult)
{
#ifdef __TRACE_Flow
    TRACE("%s[%8u]---->CYCCompletionObject(uid %d)->Reset(%d) m_Result(%d)\n", CurrentTimeText(), GetCurrentThreadId(), m_UniqueNo, ADefaultResult, m_Result);
#endif
    if (!::ResetEvent(m_Event))
    {
#ifdef __TRACE_Flow

        YCTraceLastErrorText();
        ASSERT(FALSE);

#endif
    }

    m_Result = ADefaultResult;

#ifdef _DEBUG
    m_IsSetCompletion = false;
#endif


#ifdef __TRACE_Flow
    TRACE("%s[%08X]<----CYCCompletionObject(uid %d)->Reset(%d) m_Result(%d)\n", CurrentTimeText(), GetCurrentThreadId(), m_UniqueNo, ADefaultResult, m_Result);
#endif
}
//
// CYCCompletionObject
////////////////////////////////////////////////////////////////////////////////////////////
