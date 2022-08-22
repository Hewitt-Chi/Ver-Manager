#include "stdafx.h"

#include "YCMessageOnlyWnd.h"
#include "YCUtils.h"
#include "YCTrayIcon.h"
#include <afxpriv.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CYCTrayIcon, CWnd)


BEGIN_MESSAGE_MAP(CYCTrayIcon, CWnd)
    ON_MESSAGE(CM_TrayIconNotification, &CYCTrayIcon::CMTrayIconNotification)
    ON_MESSAGE(CM_ShowHideApplication , &CYCTrayIcon::CMShowHideApplication)
    ON_WM_DESTROY()
END_MESSAGE_MAP()


CYCTrayIcon::CYCTrayIcon() : CWnd()
{
    char LPath[MAX_PATH];

    GetModuleFileName(NULL, LPath, sizeof(LPath));

    m_TipText           = PathFindFileName(LPath);
    m_Icon              = NULL;
    m_IsVisible         = false;
    m_DefaultActions    = daNone;
    m_PopupMenu         = NULL;
    m_IsAdded           = false;
}

CYCTrayIcon::~CYCTrayIcon()
{
    Free();
}

bool CYCTrayIcon::Create(bool AIsInitShow)
{
    if (!m_hWnd)
    {
        CString LStr = ::AfxRegisterWndClass(NULL);

        __super::CreateEx(0, LStr, "CYCTrayIcon",0 ,0 ,0 ,0 ,0 , HWND_MESSAGE, 0);

        if (AIsInitShow)
            Show();

        return true;
    }

    return false;
}

void CYCTrayIcon::Free()
{
    if (m_hWnd)
    {
        Hide();
        __super::DestroyWindow();
    }
}

void CYCTrayIcon::ShowApplication()
{
    YCShowApplication();

    if (IsIncluded(m_DefaultActions, daHideTrayWhenShowApp))
        Hide();
}

void CYCTrayIcon::HideApplication()
{
    // 隱藏Application
    YCHideApplication();

    if (IsIncluded(m_DefaultActions, daHideTrayWhenShowApp))
        Show();
}

void CYCTrayIcon::Show()
{
    UpdateTrayIcon(NIM_ADD);
}

void CYCTrayIcon::Hide()
{
    UpdateTrayIcon(NIM_DELETE);
}

bool CYCTrayIcon::UpdateTrayIcon(DWORD AMessage)
{
    //////////////////
    // Common Setup for all overloads.
    //
    if (m_hWnd)
    {
        NOTIFYICONDATA  LNID;

        ZeroMemory(&LNID, sizeof(LNID));
        LNID.cbSize = sizeof(LNID);
        LNID.hWnd   = m_hWnd;
        LNID.uID    = PtrToUint(this);

        if (AMessage == NIM_DELETE)
        {
            const BOOL LAPIRslt = Shell_NotifyIcon(NIM_DELETE, &LNID);

            m_IsAdded = false;

            return LAPIRslt == TRUE;
        }
        else
        {
            if (AMessage == NIM_ADD && m_IsAdded)
                AMessage = NIM_MODIFY;
            else if (AMessage == NIM_MODIFY && !m_IsAdded)
                AMessage = NIM_ADD;

            // Set Callback Message
            LNID.uCallbackMessage  = CM_TrayIconNotification;
            LNID.uFlags            = NIF_MESSAGE;

            // Set icon
            if (m_Icon)
            {
                // Add or replace icon in system tray
                LNID.hIcon  = m_Icon;
                LNID.uFlags |= NIF_ICON;
            }

            // Use the tip, if any
            strncpy_s(LNID.szTip, sizeof(LNID.szTip), (LPCSTR)m_TipText, sizeof(LNID.szTip));
            LNID.uFlags |= NIF_TIP;

            // 是否可見
            if (!m_IsVisible)
                LNID.dwState = NIS_HIDDEN;

            LNID.dwStateMask = NIS_HIDDEN;

            //LNID.uVersion = NOTIFYICON_VERSION;

            // Do it
            const BOOL LAPIRslt = ::Shell_NotifyIcon(AMessage, &LNID);

            m_IsAdded = true;

            return LAPIRslt == TRUE;
        }
    }

    return false;
}

LRESULT CYCTrayIcon::CMTrayIconNotification(WPARAM ATrayIconID, LPARAM ATrayIconAction)
{
    if (ATrayIconID == PtrToUint(this))
    {
        switch (ATrayIconAction)
        {
        case WM_LBUTTONUP :
            if (IsIncluded(m_DefaultActions, daClickShowHideApp))
            {
                if (AfxGetMainWnd())
                {
                    if (!AfxGetMainWnd()->IsWindowVisible())
                        PostMessage(CM_ShowHideApplication, TRUE);
                    else
                        PostMessage(CM_ShowHideApplication, FALSE);
                }
            }
            break;

        case WM_LBUTTONDBLCLK :
            if (IsIncluded(m_DefaultActions, daDoubleClickShowHideApp))
            {
                if (AfxGetMainWnd())
                {
                    if (!AfxGetMainWnd()->IsWindowVisible())
                        PostMessage(CM_ShowHideApplication, TRUE);
                    else
                        PostMessage(CM_ShowHideApplication, FALSE);
                }
            }
            break;

        case WM_RBUTTONUP :
            // If there's a resource LMenu with the same ID as the icon, use it as
            // the right-button popup LMenu. CYCTrayIcon will interprets the first
            // item in the LMenu as the default command for WM_LBUTTONDBLCLK
            //
            if (m_PopupMenu)
            {
                // Make first LMenu item the default (bold font)
                ::SetMenuDefaultItem(m_PopupMenu->m_hMenu, 0, TRUE);

                // Display the LMenu at the current LMousePoint location. There's a "bug"
                // (Microsoft calls it a feature) in Windows 95 that requires calling
                // SetForegroundWindow. To find out more, search for Q135788 in MSDN.
                //
                CPoint LMousePoint;

                GetCursorPos(&LMousePoint);
                //::SetForegroundWindow(LNID->hWnd);   
                ::TrackPopupMenu(m_PopupMenu->m_hMenu, 0, LMousePoint.x, LMousePoint.y, 0, m_hWnd, NULL);
            }
            break;
        }

        // handled
        m_OnTrayIconMouseAction(this, ATrayIconAction);

        return 1;
    }

    return 0;
}

LRESULT CYCTrayIcon::CMShowHideApplication(WPARAM AIsShowApp, LPARAM lParam)
{
    if (AIsShowApp)
        ShowApplication();
    else
        HideApplication();

    return 0;
}


//最重要的地方：LNID->uCallbackMessage = uCbMsg;
void CYCTrayIcon::OnDestroy()
{
    CWnd::OnDestroy();

    // TODO: Add your message handler code here
    UpdateTrayIcon(NIM_DELETE);
}
