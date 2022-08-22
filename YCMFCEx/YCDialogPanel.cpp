// YCDialogWnd.cpp : implementation file
//

#include "stdafx.h"

#include "YCDialogPanel.h"

#include <afxpriv.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CYCDialogPanel
LPCSTR CYCDialogPanel::m_ClassName           = "CYCDialogPanel";
bool   CYCDialogPanel::m_IsRegisterThisClass = CYCDialogPanel::RegisterThisClass();


bool CYCDialogPanel::RegisterThisClass()
{
    WNDCLASS    LWndClass;

    LWndClass.hInstance = (HINSTANCE)::GetModuleHandle(NULL);

    if (!::GetClassInfo(LWndClass.hInstance, m_ClassName, &LWndClass))
    {
        // otherwise we need to register a new class
        LWndClass.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        LWndClass.lpfnWndProc      = ::DefWindowProc;
        LWndClass.cbClsExtra       = LWndClass.cbWndExtra = 0;
        //LWndClass.hInstance        = LhInstance;
        LWndClass.hIcon            = NULL;
        LWndClass.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        LWndClass.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
        LWndClass.lpszMenuName     = NULL;
        LWndClass.lpszClassName    = m_ClassName;

        if (!AfxRegisterClass(&LWndClass))
        {
            AfxThrowResourceException();
            return false;
        }
    }

    return true;
}


IMPLEMENT_DYNAMIC(CYCDialogPanel, CWnd)


CYCDialogPanel::CYCDialogPanel()
: m_Dialog(NULL)
, m_Layout(dlCenter)
{
}

CYCDialogPanel::~CYCDialogPanel()
{
}


BEGIN_MESSAGE_MAP(CYCDialogPanel, CWnd)

    ON_WM_WINDOWPOSCHANGED()

    ON_UPDATE_COMMAND_UI_REFLECT(&CYCDialogPanel::WMUpdateCommandUI)

END_MESSAGE_MAP()


// CYCDialogPanel message handlers
void    CYCDialogPanel::PreSubclassWindow()
{

    ModifyStyleEx(0, WS_EX_CONTROLPARENT/* | WS_EX_STATICEDGE*/);

    UpdateDialogDisplay();

    __super::PreSubclassWindow();
}

void CYCDialogPanel::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
    __super::OnWindowPosChanged(lpwndpos);

    // TODO: Add your message handler code here
    if ((lpwndpos->flags & (SWP_NOSIZE | SWP_NOMOVE)) != (SWP_NOSIZE | SWP_NOMOVE))
        UpdateDialogDisplay();
}

void    CYCDialogPanel::WMUpdateCommandUI(CCmdUI* ACmdUI)
{
    if (IsWindowVisible())
        UpdateDialogControls(this, FALSE);
}

//LRESULT CYCDialogPanel::WMKickIdle(WPARAM wParam, LPARAM lParam)
//{
//    if (m_Dialog && m_Dialog->m_hWnd)
//        return m_Dialog->SendMessage(WM_KICKIDLE, wParam, lParam);
//
//    return 0;
//}

CDialog*
/**/    CYCDialogPanel::Dialog()
{
    return m_Dialog;
}

void    CYCDialogPanel::SetDialog(CDialog *ADialog, enmDialogLayout ALayout)
{
    if (ADialog != m_Dialog || m_Layout != ALayout)
    {
        m_Layout = ALayout;

        if (m_Dialog)
        {
            if (m_Dialog->m_hWnd)
            {
                m_Dialog->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_HIDEWINDOW);
                m_Dialog->SetParent(NULL);
            }
        }

        m_Dialog = ADialog;

        UpdateDialogDisplay();
    }
}

void    CYCDialogPanel::UpdateDialogDisplay()
{
    if (m_hWnd && m_Dialog && m_Dialog->m_hWnd)
    {
        CRect   LDialogRect;
        CRect   LThisClientRect;

        m_Dialog->ModifyStyle(0, WS_CHILD);
        m_Dialog->SetParent(this);

        m_Dialog->GetWindowRect(&LDialogRect);
        GetClientRect(&LThisClientRect);

        switch (m_Layout)
        {
        case dlNone :
            // 顯示指定的Dialog
            m_Dialog->SetWindowPos(NULL, LThisClientRect.left, LThisClientRect.top, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
            break;

        case dlCenter :
            // 顯示指定的Dialog
            m_Dialog->CenterWindow();
            m_Dialog->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);
            break;

        case dlDialogFitPanel :
            // 調整Dialog的大小同自已的大小
            m_Dialog->SetWindowPos(NULL, LThisClientRect.left, LThisClientRect.top, LThisClientRect.Width(), LThisClientRect.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
            break;

        case dlPanelFitDialog :
            CalcWindowRect(&LDialogRect);
            // 調整自已的大小同指定Dialog的大小
            SetWindowPos(NULL, 0, 0, LDialogRect.Width(), LDialogRect.Height(), SWP_NOMOVE | SWP_NOZORDER);

            // 顯示指定的Dialog
            m_Dialog->SetWindowPos(NULL, LThisClientRect.left, LThisClientRect.top, 0, 0, SWP_NOSIZE | SWP_SHOWWINDOW);
            break;
        }
    }
}
