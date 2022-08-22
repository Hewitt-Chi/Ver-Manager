#include "StdAfx.h"

#include "YCApplicationMainWnd.h"
#include "YCUtils.h"
#include <afxpriv.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CYCApplicationMainWnd, CDialog)


CYCApplicationMainWnd::CYCApplicationMainWnd(void)
: CDialog()
, m_IsDoModaling(false)
, m_IsRequestDoModal(false)
{
    int LDlgTemplateSize = sizeof(DLGTEMPLATE) + sizeof(WORD) * 4;

    LDlgTemplateSize = LDlgTemplateSize / 4 * 4 + (((LDlgTemplateSize % 4) == 0) ? 0 : 4);
    m_DlgTemplate = new BYTE[LDlgTemplateSize];
    ZeroMemory(m_DlgTemplate, LDlgTemplateSize);

    //LONG    LDlgBaseUnit = GetDialogBaseUnits();
    DLGTEMPLATE *LDlgTemplate = (DLGTEMPLATE*)m_DlgTemplate;

    LDlgTemplate->style             = DS_SETFONT | DS_FIXEDSYS | WS_POPUP | WS_SYSMENU | WS_VISIBLE;
    LDlgTemplate->dwExtendedStyle   = WS_EX_APPWINDOW;
    LDlgTemplate->cdit              = 0;
    LDlgTemplate->x                 = 0;
    LDlgTemplate->y                 = 0;
    LDlgTemplate->cx                = 0;
    LDlgTemplate->cy                = 0;

    m_lpDialogTemplate = LDlgTemplate;
}

CYCApplicationMainWnd::~CYCApplicationMainWnd(void)
{
    delete [] m_DlgTemplate;
}

void CYCApplicationMainWnd::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    if (!pDX->m_bSaveAndValidate)
        SetWindowText(m_Caption);
}

#define CM_DoModal               (WM_USER  + 1)

BEGIN_MESSAGE_MAP(CYCApplicationMainWnd, CDialog)
    ON_WM_WINDOWPOSCHANGED()
    ON_WM_SHOWWINDOW()
    ON_MESSAGE(CM_DoModal , &CYCApplicationMainWnd::CMDoModal)
    ON_MESSAGE(WM_SETTEXT , &CYCApplicationMainWnd::WMSetText)
    ON_MESSAGE(WM_KICKIDLE, &CYCApplicationMainWnd::WMKickIdle)
END_MESSAGE_MAP()


// CYCApplicationMainWnd message handlers

BOOL CYCApplicationMainWnd::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    if (m_Caption.IsEmpty())
        GetWindowText(m_Caption);
    else
        SetWindowText(m_Caption);

    return TRUE;
}

LRESULT CYCApplicationMainWnd::CMDoModal(WPARAM, LPARAM)
{
    if (!m_IsDoModaling)
    {
        m_IsDoModaling = true;

        INT_PTR LRslt = IDCANCEL;

        if (m_dlgMain)
            LRslt = m_dlgMain->DoModal();

        this->EndDialog(PtrToInt(LRslt));
    }

    return 0;
}

LRESULT CYCApplicationMainWnd::WMSetText(WPARAM wParam, LPARAM AText)
{
    if (m_Caption != (char *)AText)
        m_Caption = (char *)AText;

    return DefWindowProc(WM_SETTEXT, wParam, AText);;
}

LRESULT CYCApplicationMainWnd::WMKickIdle(WPARAM wParam, LPARAM AText)
{
    if (!m_IsDoModaling && !m_IsRequestDoModal)
    {
        PostMessage(CM_DoModal, 0, 0);
        m_IsRequestDoModal = true;
    }

    return 0;
}

void CYCApplicationMainWnd::SetCaption(LPCSTR AValue)
{
    if (m_hWnd)
        SetWindowText(m_Caption);
    else if (m_Caption.Compare(AValue) != 0)
        m_Caption = AValue;
}

void CYCApplicationMainWnd::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
    CDialog::OnWindowPosChanged(lpwndpos);

    // TODO: Add your message handler code here
    if (m_IsDoModaling && m_dlgMain && m_dlgMain->m_hWnd)
    {
        if (IsIncluded(lpwndpos->flags, SWP_SHOWWINDOW))
        {
            m_dlgMain->SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);
            m_dlgMain->BringWindowToTop();
        }
        else if (IsIncluded(lpwndpos->flags, SWP_HIDEWINDOW))
        {
            m_dlgMain->SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_HIDEWINDOW);
        }
    }
}

void CYCApplicationMainWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    // TODO: Add your message handler code here
    if (m_IsDoModaling && m_dlgMain && m_dlgMain->m_hWnd)
    {
        if (bShow)
        {
            m_dlgMain->SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_SHOWWINDOW);
            m_dlgMain->BringWindowToTop();
        }
        else
        {
            m_dlgMain->SetWindowPos(this, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_HIDEWINDOW);
        }
    }
}
