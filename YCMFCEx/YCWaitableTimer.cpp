#include "StdAfx.h"

#include "YCWaitableTimer.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CYCWaitableTimer, CSyncObject)


CYCWaitableTimer::CYCWaitableTimer(LPSECURITY_ATTRIBUTES    ATimerAttributes/* = NULL*/,
                                   BOOL                     AManualReset/* = FALSE*/,
                                   LPCTSTR                  ATimerName/* = NULL*/)
: CSyncObject(ATimerName)
{
    m_hObject = CreateWaitableTimer(ATimerAttributes, AManualReset, ATimerName);
}

CYCWaitableTimer::CYCWaitableTimer(LPSECURITY_ATTRIBUTES    ATimerAttributes,
                                   BOOL                     AManualReset,
                                   LPCTSTR                  ATimerName,
                                   LONGLONG                 ADueTime,
                                   DWORD                    APeriod,
                                   BOOL                     AResume)
: CSyncObject(ATimerName)
{
    m_hObject = CreateWaitableTimer(ATimerAttributes, AManualReset, ATimerName);

    SetWaitableTimer(ADueTime, APeriod, AResume);
}

CYCWaitableTimer::~CYCWaitableTimer(void)
{
    if (m_hObject)
        CancelWaitableTimer();
}

BOOL    CYCWaitableTimer::Unlock()
{
    return FALSE;
}

BOOL    CYCWaitableTimer::SetWaitableTimer(const LARGE_INTEGER* ADueTime, LONG APeriod, BOOL AResume)
{
    return ::SetWaitableTimer(m_hObject, ADueTime, APeriod, NULL, NULL, AResume);
}

BOOL    CYCWaitableTimer::SetWaitableTimer(LONGLONG ADueTime, LONG APeriod, BOOL AResume)
{
    ASSERT(m_hObject);

    if (!m_hObject)
        return FALSE;

    LARGE_INTEGER   LDueTime;

    LDueTime.QuadPart = ADueTime;

    return SetWaitableTimer(&LDueTime, APeriod, AResume);
}

BOOL    CYCWaitableTimer::CancelWaitableTimer()
{
    ASSERT(m_hObject);

    if (!m_hObject)
        return FALSE;

    return ::CancelWaitableTimer(m_hObject);
}
