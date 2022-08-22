#include "StdAfx.h"

#include "YCOneInstance.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


namespace nspYCOneInstance
{
    DWORD MessageID = WM_NULL;
    HHOOK Hook      = NULL;

    LRESULT CALLBACK YCOneInstanceGetMsgProc(int code, WPARAM wParam, LPARAM lParam)
    {
        if (code >= HC_ACTION)
        {
            switch (wParam)
            {
            case PM_REMOVE :
                {
                    MSG *LMsg = (MSG *)lParam;

                    if (LMsg->message == nspYCOneInstance::MessageID
                        && GetCurrentProcessId() != LMsg->wParam)
                    {
                        Sleep(50);

                        if (::IsIconic(AfxGetApp()->m_pMainWnd->m_hWnd))
                            ShowWindow(AfxGetApp()->m_pMainWnd->m_hWnd, SW_RESTORE);
                        else
                        {
                            HWND LHwnd = ::GetLastActivePopup(AfxGetApp()->m_pMainWnd->m_hWnd);

                            if (LHwnd)
                                SetForegroundWindow(LHwnd);
                        }
                    }
                }
                break;
            }
        }

        return CallNextHookEx(nspYCOneInstance::Hook, code, wParam, lParam);
    }
}


LONG CYCOneInstance::m_ReferenceCount = 0;



CYCOneInstance::CYCOneInstance(LPTSTR AName)
: m_Name(AName)
{
    if (InterlockedIncrement(&m_ReferenceCount) > 1)
    {
        InterlockedDecrement(&m_ReferenceCount);
        AfxThrowNotSupportedException();
    }
    else
    {
        nspYCOneInstance::MessageID = RegisterWindowMessage(m_Name + ".Message");

        if (!nspYCOneInstance::Hook)
            nspYCOneInstance::Hook = SetWindowsHookEx(WH_GETMESSAGE, nspYCOneInstance::YCOneInstanceGetMsgProc, NULL, AfxGetApp()->m_nThreadID);

        m_Mutex = CreateMutex(NULL, FALSE, m_Name + ".Mutex");
        m_IsPreInstanceExists = (GetLastError() == ERROR_ALREADY_EXISTS);
    }
}

CYCOneInstance::~CYCOneInstance(void)
{
    if (InterlockedDecrement(&m_ReferenceCount) == 0)
    {
        if (nspYCOneInstance::Hook)
        {
            UnhookWindowsHookEx(nspYCOneInstance::Hook);
            nspYCOneInstance::Hook = NULL;
        }

        if (m_Mutex)
            CloseHandle(m_Mutex);
    }
}

bool CYCOneInstance::TestAndActivatePreInstance()
{
    if (m_IsPreInstanceExists)
    {
        PostMessage(HWND_BROADCAST, nspYCOneInstance::MessageID, GetCurrentProcessId(), 0);
        return true;
    }

    return false;
}

