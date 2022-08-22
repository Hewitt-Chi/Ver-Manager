// mysheet.cpp : implementation file
//
#include "stdafx.h"


#include "YCPropertySheet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define CM_ResizePage       (WM_USER + 93)


#if 0
enum { CDF_CENTER, CDF_TOPLEFT, CDF_NONE };


// helper function which sets the font for a window and all its children
// and also resizes everything according to the new font
void YCChangeDialogFont(CWnd *AWnd, CFont *AFont, int AFlag)
{
    CRect LWindowRect;

    // grab old and new text metrics
    TEXTMETRIC  LOldTextMetric;
    TEXTMETRIC  LNewTextMetric;
    CDC         *LDC = AWnd->GetDC();
    CFont       *LOldFont = LDC->SelectObject(AWnd->GetFont());

    LDC->GetTextMetrics(&LOldTextMetric);

    LDC->SelectObject(AFont);
    LDC->GetTextMetrics(&LNewTextMetric);

    LDC->SelectObject(LOldFont);

    AWnd->ReleaseDC(LDC);

    long LOldHeight = LOldTextMetric.tmHeight + LOldTextMetric.tmExternalLeading;
    long LNewHeight = LNewTextMetric.tmHeight + LNewTextMetric.tmExternalLeading;

    if (AFlag != CDF_NONE)
    {
        // calculate new dialog window rectangle
        CRect LClientRect, LNewClientRect, LNewWindowRect;

        AWnd->GetWindowRect(LWindowRect);
        AWnd->GetClientRect(LClientRect);


        long LDiffX = LWindowRect.Width()  - LClientRect.Width();
        long LDiffY = LWindowRect.Height() - LClientRect.Height();

        LNewClientRect.left   = LNewClientRect.top = 0;
        LNewClientRect.right  = LClientRect.right  * LNewTextMetric.tmAveCharWidth / LOldTextMetric.tmAveCharWidth;
        LNewClientRect.bottom = LClientRect.bottom * LNewHeight / LOldHeight;

        switch (AFlag)
        {
        case CDF_TOPLEFT : // resize with origin at top/left of window
            LNewWindowRect.left   = LWindowRect.left;
            LNewWindowRect.top    = LWindowRect.top;
            LNewWindowRect.right  = LWindowRect.left + LNewClientRect.right  + LDiffX;
            LNewWindowRect.bottom = LWindowRect.top  + LNewClientRect.bottom + LDiffY;
            break;

        case CDF_CENTER : // resize with origin at center of window
            LNewWindowRect.left   = LWindowRect.left - (LNewClientRect.right  - LClientRect.right)  / 2;
            LNewWindowRect.top    = LWindowRect.top  - (LNewClientRect.bottom - LClientRect.bottom) / 2;
            LNewWindowRect.right  = LNewWindowRect.left + LNewClientRect.right  + LDiffX;
            LNewWindowRect.bottom = LNewWindowRect.top  + LNewClientRect.bottom + LDiffY;
            break;
        }

        AWnd->MoveWindow(LNewWindowRect);
    }

    AWnd->SetFont(AFont);

    // iterate through and move all child windows and change their font.
    for (CWnd    *LChildWnd = AWnd->GetWindow(GW_CHILD); LChildWnd; LChildWnd = LChildWnd->GetWindow(GW_HWNDNEXT))
    {
        LChildWnd->SetFont(AFont);
        LChildWnd->GetWindowRect(LWindowRect);

        CString LClassName;

        ::GetClassName(LChildWnd->m_hWnd, LClassName.GetBufferSetLength(32), 31);

        LClassName.MakeUpper();

        if (LClassName == _T("COMBOBOX"))
        {
            CRect LRect;

            LChildWnd->SendMessage(CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)&LRect);

            LWindowRect.right  = LRect.right;
            LWindowRect.bottom = LRect.bottom;
        }

        AWnd->ScreenToClient(LWindowRect);

        LWindowRect.left   = LWindowRect.left   * LNewTextMetric.tmAveCharWidth / LOldTextMetric.tmAveCharWidth;
        LWindowRect.right  = LWindowRect.right  * LNewTextMetric.tmAveCharWidth / LOldTextMetric.tmAveCharWidth;
        LWindowRect.top    = LWindowRect.top    * LNewHeight / LOldHeight;
        LWindowRect.bottom = LWindowRect.bottom * LNewHeight / LOldHeight;

        LChildWnd->MoveWindow(LWindowRect);
    }
}
#endif

void    YCChangeDialogFont(CWnd *AWnd, CFont *AFont)
{
    AWnd->SetFont(AFont);

    for (CWnd    *LChildWnd = AWnd->GetWindow(GW_CHILD); LChildWnd; LChildWnd = LChildWnd->GetWindow(GW_HWNDNEXT))
        YCChangeDialogFont(LChildWnd, AFont);
}

/////////////////////////////////////////////////////////////////////////////
// CYCPropertySheet
//
IMPLEMENT_DYNAMIC(CYCPropertySheet, CPropertySheet)


CYCPropertySheet::CYCPropertySheet(UINT AIDCaption, CWnd* AParentWnd, UINT ASelectPage)
: CPropertySheet(AIDCaption, AParentWnd, ASelectPage)
{
}

CYCPropertySheet::CYCPropertySheet(LPCTSTR ACaption, CWnd* AParentWnd, UINT ASelectPage)
: CPropertySheet(ACaption, AParentWnd, ASelectPage)
{
}

CYCPropertySheet::~CYCPropertySheet()
{
    if (m_fntPage.m_hObject)
        VERIFY (m_fntPage.DeleteObject());
}


BEGIN_MESSAGE_MAP(CYCPropertySheet, CPropertySheet)

    ON_WM_WINDOWPOSCHANGED()
    ON_MESSAGE (CM_ResizePage, CMResizePage)

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CYCPropertySheet message handlers
void CYCPropertySheet::BuildPropPageArray()
{
    __super::BuildPropPageArray();

    // get first page
    CPropertyPage   *LPage = GetPage(0);

    ASSERT(LPage);

    // dialog template class in afxpriv.h
    CDialogTemplate LDialogTemplate;

    // load the dialog template
    VERIFY(LDialogTemplate.Load(LPage->m_psp.pszTemplate));

    // get the font information
    CString LFontFace;
    WORD    LFontSize;

    VERIFY(LDialogTemplate.GetFont(LFontFace, LFontSize));

    if (m_fntPage.m_hObject)
        VERIFY(m_fntPage.DeleteObject());

    // create a font using the info from first page
    VERIFY(m_fntPage.CreatePointFont(LFontSize * 10, LFontFace));
}

BOOL CYCPropertySheet::OnInitDialog() 
{
    __super::OnInitDialog();

    // get the font for the first active page
    CPropertyPage   *LActivePage = GetActivePage();

    ASSERT(LActivePage);

    // change the font for the sheet
    YCChangeDialogFont(this, &m_fntPage);

    // change the font for each page
    for (int I = 0; I < GetPageCount(); I++)
    {
        VERIFY(SetActivePage(I));

        CPropertyPage   *LPage = GetActivePage();

        ASSERT(LPage);

        YCChangeDialogFont(LPage, &m_fntPage);
    }

    VERIFY (SetActivePage(LActivePage));


    CTabCtrl    *LTabCtrl = GetTabControl();

    ASSERT (LTabCtrl);

    if (m_psh.dwFlags & PSH_WIZARD)
        LTabCtrl->ShowWindow(SW_HIDE);

    return TRUE;
}

BOOL CYCPropertySheet::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
    NMHDR* LNMHdr = (LPNMHDR) lParam;

    // the sheet resizes the page whenever it is activated so we need to size it correctly
    if (TCN_SELCHANGE == LNMHdr->code)
        PostMessage(CM_ResizePage);

    return __super::OnNotify(wParam, lParam, pResult);
}

BOOL CYCPropertySheet::OnCommand(WPARAM wParam, LPARAM lParam) 
{
    // the sheet resizes the page whenever the Apply button is clicked so we need to size it correctly
    if (ID_APPLY_NOW == wParam ||
        ID_WIZNEXT == wParam ||
        ID_WIZBACK == wParam)
    {
        PostMessage(CM_ResizePage);
    }

    return __super::OnCommand(wParam, lParam);
}

void CYCPropertySheet::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
    __super::OnWindowPosChanged(lpwndpos);

    // TODO: Add your message handler code here
    // set and save the size of the page
    if (m_psh.dwFlags & PSH_WIZARD)
    {
        GetClientRect(&m_rctPage);

        CWnd    *LButton = GetDlgItem(ID_WIZBACK);

        ASSERT(LButton);

        CRect LRect;

        LButton->GetWindowRect(&LRect);
        ScreenToClient(&LRect);

        m_rctPage.bottom = LRect.top - 2;
    }
    else
    {
        CTabCtrl    *LTabCtrl = GetTabControl();

        if (LTabCtrl)
        {
            CRect   LClientRect;

            GetClientRect(&LClientRect);

            CTabCtrl    *LTabCtrl = GetTabControl();

#if 0
            LTabCtrl->ModifyStyle(TCS_MULTILINE, TCS_SINGLELINE | TCS_SCROLLOPPOSITE, 0);
#endif
            LTabCtrl->MoveWindow(&LClientRect);
            LTabCtrl->AdjustRect(FALSE, &LClientRect);
            m_rctPage = LClientRect;

            for (int I = 0; I < GetPageCount(); I ++)
            {
                if (GetPage(I)->m_hWnd)
                    GetPage(I)->MoveWindow(&LClientRect);
            }
        }
    }
}

LONG CYCPropertySheet::CMResizePage(UINT, LONG)
{
    // resize the page
    CPropertyPage   *LPage = GetActivePage();

    ASSERT(LPage);

    LPage->MoveWindow(&m_rctPage);

    return 0;
}


///////////////////////////////////////////////////////
// CYCPropertyPage dialog
//
void StretchWnd(CWnd *AWnd, const CRect &ADisplayRect)
{
    CRect   LRect;

    AWnd->GetWindowRect(&LRect);

    const float LScaleRateX = (ADisplayRect.Width()  * 1.0f) / LRect.Width();
    const float LScaleRateY = (ADisplayRect.Height() * 1.0f) / LRect.Height();

    AWnd->MoveWindow(&ADisplayRect);

    for (CWnd    *LChildWnd = AWnd->GetWindow(GW_CHILD); LChildWnd; LChildWnd = LChildWnd->GetWindow(GW_HWNDNEXT))
    {
        CRect   LChildWindowRect;

        LChildWnd->GetWindowRect(LChildWindowRect);

        CString LClassName;

        ::GetClassName(LChildWnd->m_hWnd, LClassName.GetBufferSetLength(32), 31);

        LClassName.MakeUpper();

        if (LClassName == _T("COMBOBOX"))
        {
            CRect LRect;

            LChildWnd->SendMessage(CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)&LRect);

            LChildWindowRect.right  = LRect.right;
            LChildWindowRect.bottom = LRect.bottom;
        }

        AWnd->ScreenToClient(LChildWindowRect);

        LChildWindowRect.left   = (LONG)(LChildWindowRect.left   * LScaleRateX);
        LChildWindowRect.right  = (LONG)(LChildWindowRect.right  * LScaleRateX);
        LChildWindowRect.top    = (LONG)(LChildWindowRect.top    * LScaleRateY);
        LChildWindowRect.bottom = (LONG)(LChildWindowRect.bottom * LScaleRateY);

        StretchWnd(LChildWnd, LChildWindowRect);
    }
}


IMPLEMENT_DYNAMIC(CYCPropertyPage, CPropertyPage)


CYCPropertyPage::CYCPropertyPage(UINT AIDTemplate, UINT AIDCaption/* = 0*/, DWORD ASize/* = sizeof(PROPSHEETPAGE)*/)
: CPropertyPage(AIDTemplate, AIDCaption, ASize)
{
}

CYCPropertyPage::~CYCPropertyPage()
{
}

void CYCPropertyPage::DoDataExchange(CDataExchange* pDX)
{
    __super::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CYCPropertyPage, CPropertyPage)

    ON_WM_WINDOWPOSCHANGED()

    ON_UPDATE_COMMAND_UI_REFLECT(&CYCPropertyPage::DoOnUpdateCommandUI)

END_MESSAGE_MAP()


BOOL CYCPropertyPage::OnInitDialog()
{
    __super::OnInitDialog();

    // TODO:  Add extra initialization here
    CRect   LRect;

    GetWindowRect(&LRect);

    m_OrgWidth  = LRect.Width();
    m_OrgHeight = LRect.Height();

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CYCPropertyPage::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
    __super::OnWindowPosChanged(lpwndpos);

    // TODO: Add your message handler code here
    CRect   LRect;

    GetWindowRect(&LRect);

    if (m_OrgWidth != LRect.Width() || m_OrgHeight != LRect.Height())
    {
        const float LScaleRateX = LRect.Width()  * 1.0f / m_OrgWidth;
        const float LScaleRateY = LRect.Height() * 1.0f / m_OrgHeight;

        m_OrgWidth  = LRect.Width();
        m_OrgHeight = LRect.Height();

        for (CWnd    *LChildWnd = GetWindow(GW_CHILD); LChildWnd; LChildWnd = LChildWnd->GetWindow(GW_HWNDNEXT))
        {
            CRect   LChildWindowRect;

            LChildWnd->GetWindowRect(LChildWindowRect);

            CString LClassName;

            ::GetClassName(LChildWnd->m_hWnd, LClassName.GetBufferSetLength(32), 31);

            LClassName.MakeUpper();

            if (LClassName == _T("COMBOBOX"))
            {
                CRect LRect;

                LChildWnd->SendMessage(CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)&LRect);

                LChildWindowRect.right  = LRect.right;
                LChildWindowRect.bottom = LRect.bottom;
            }

            ScreenToClient(LChildWindowRect);

            LChildWindowRect.left   = (LONG)(LChildWindowRect.left   * LScaleRateX);
            LChildWindowRect.right  = (LONG)(LChildWindowRect.right  * LScaleRateX);
            LChildWindowRect.top    = (LONG)(LChildWindowRect.top    * LScaleRateY);
            LChildWindowRect.bottom = (LONG)(LChildWindowRect.bottom * LScaleRateY);

            StretchWnd(LChildWnd, LChildWindowRect);
        }
    }
}

void CYCPropertyPage::DoOnUpdateCommandUI(CCmdUI *ACmdUI)
{
    if (IsWindowVisible())
    {
        UpdateDialogControls(this, FALSE);

        OnUpdateCommandUI(ACmdUI);
    }
}

void CYCPropertyPage::OnUpdateCommandUI(CCmdUI *ACmdUI)
{
}
//
// CYCPropertyPage dialog
///////////////////////////////////////////////////////
