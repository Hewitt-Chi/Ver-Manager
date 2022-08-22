// YCDialog.cpp : implementation file
//

#include "stdafx.h"

#include <afxpriv.h>

#include "YCDialog.h"

#include "YCUtils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void    YCStretchChild(CWnd *AWnd, float AScaleRateX, float AScaleRateY)
{
    for (CWnd *LWnd = AWnd->GetTopWindow(); LWnd; LWnd = LWnd->GetNextWindow())
    {
        CRect   LRect;

        LWnd->GetWindowRect(&LRect);

        {
            ////////////////////////////////////
            // 如果子控項是ComboBox的話，要將
            // 其下拉選單的大小納入
            //
            CString LClassName;


            ::GetClassName(LWnd->m_hWnd, LClassName.GetBufferSetLength(32), 31);

            LClassName.MakeUpper();

            if (LClassName == _T("COMBOBOX"))
            {
                CRect   LDropListRect;

                LWnd->SendMessage(CB_GETDROPPEDCONTROLRECT, 0, (LPARAM)&LDropListRect);
                LRect.right  = LDropListRect.right;
                LRect.bottom = LDropListRect.bottom;
            }
            //
            // 如果子控項是ComboBox的話，要將
            // 其下拉選單的大小納入
            ////////////////////////////////////
        }

        AWnd->ScreenToClient(&LRect);

        LRect.left   = (LONG)(LRect.left   * AScaleRateX);
        LRect.top    = (LONG)(LRect.top    * AScaleRateY);
        LRect.right  = (LONG)(LRect.right  * AScaleRateX);
        LRect.bottom = (LONG)(LRect.bottom * AScaleRateY);

        // 設定控項位置尺吋
        LWnd->MoveWindow(&LRect);

        // 繼續往下做
        CYCDialog *LDlg = dynamic_cast<CYCDialog *>(LWnd);

        if (!LDlg || !LDlg->IsAutoStretchChilds())
            YCStretchChild(LWnd, AScaleRateX, AScaleRateY);
    }
}


// CYCDialog dialog
IMPLEMENT_DYNAMIC(CYCDialog, CDialog)


CYCDialog::CYCDialog(UINT AResId, CWnd* pParent/* = NULL*/)
: CDialog(AResId, pParent)
, m_BckgndOffsetX(0)
, m_BckgndOffsetY(0)
, m_IsBkBmpIncludeNCArea(true)
, m_Width(-1)
, m_Height(-1)
, m_hIcon(NULL)
, m_IsClosable(true)
, m_IsMovable(true)
, m_IsAutoStretchChilds(true)
, m_StretchDlgClientWidth(-1)
, m_StretchDlgClientHeight(-1)
, m_IsInactiveUDCsEnabled(false)
, m_IsToolTipsEnabled(false)
{
}

CYCDialog::CYCDialog(UINT AResId, WORD ABackgroundResId, WORD AIconResId, CWnd* pParent)
: CDialog(AResId, pParent)
, m_BckgndOffsetX(0)
, m_BckgndOffsetY(0)
, m_IsBkBmpIncludeNCArea(true)
, m_Width(-1)
, m_Height(-1)
, m_hIcon(AfxGetApp()->LoadIcon(AIconResId))
, m_IsClosable(true)
, m_IsMovable(true)
, m_IsAutoStretchChilds(true)
, m_StretchDlgClientWidth(-1)
, m_StretchDlgClientHeight(-1)
, m_IsInactiveUDCsEnabled(false)
, m_IsToolTipsEnabled(false)
{
    SetBackgroundResID(ABackgroundResId);
}

CYCDialog::~CYCDialog()
{
}

INT_PTR CYCDialog::DoModal()
{
    if (!m_hWnd)
    {
        return __super::DoModal();
    }
    else if (!IsWindowVisible() && !(m_nFlags & WF_MODALLOOP))
    {
        // disable parent (before creating dialog)
        HWND hWndParent     = CWnd::GetSafeOwner_(m_pParentWnd->GetSafeHwnd(), &m_hWndTop);
        BOOL bEnableParent  = FALSE;

        if (hWndParent == m_hWnd)
            hWndParent = ::GetParent(m_hWnd);

        if (hWndParent && hWndParent != ::GetDesktopWindow() && ::IsWindowEnabled(hWndParent))
        {
            ::EnableWindow(hWndParent, FALSE);
            bEnableParent = TRUE;
        }

        try
        {
            m_nFlags |= WF_CONTINUEMODAL;

            // enter modal loop
            DWORD dwFlags = MLF_SHOWONIDLE;

            if (GetStyle() & DS_NOIDLEMSG)
                dwFlags |= MLF_NOIDLEMSG;

            VERIFY(RunModalLoop(dwFlags) == m_nModalResult);

            // hide the window before enabling the parent, etc.
            if (m_hWnd != NULL)
                SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_HIDEWINDOW);
        }
        catch (CException* e)
        {
            e->Delete();
            m_nModalResult = -1;
        }

        if (bEnableParent)
            ::EnableWindow(hWndParent, TRUE);

        if (hWndParent != NULL && ::GetActiveWindow() == m_hWnd)
            ::SetActiveWindow(hWndParent);

        // destroy modal window
        if (::IsWindow(m_hWndTop))
            ::EnableWindow(m_hWndTop, TRUE);

        m_hWndTop = NULL;

        return m_nModalResult;
    }
    else
    {
        ASSERT(!IsWindowVisible());
        ASSERT(!(m_nFlags & WF_MODALLOOP));

        return -1;
    }
}

void    CYCDialog::PreSubclassWindow()
{
    //CreateBkDC();

    __super::PreSubclassWindow();
}

void    CYCDialog::DoDataExchange(CDataExchange* pDX)
{
    __super::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CYCDialog, CDialog)

    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_NCHITTEST()
    ON_WM_ERASEBKGND()
    ON_WM_WINDOWPOSCHANGED()

    ON_UPDATE_COMMAND_UI_REFLECT(&CYCDialog::WMUpdateCommandUI)
    ON_MESSAGE(WM_KICKIDLE, &CYCDialog::WMKickIdle)
    ON_NOTIFY_EX(TTN_NEEDTEXT, 0, &CYCDialog::WMNotifyTTNNeedText) 

END_MESSAGE_MAP()


BOOL    CYCDialog::OnInitDialog()
{
    __super::OnInitDialog();

    // m_IsClosable = true;

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    if (m_hIcon)
    {
        SetIcon(m_hIcon, TRUE); // Set big icon
        SetIcon(m_hIcon, FALSE); // Set small icon
    }

    if (m_Width != -1 && m_Height != -1)
    {
        CRect LWorkAreaRect, LThisRect;

        SystemParametersInfo(SPI_GETWORKAREA, 0, &LWorkAreaRect, 0);
        GetWindowRect(&LThisRect);

        LThisRect.right  = LThisRect.left + m_Width;
        LThisRect.bottom = LThisRect.top  + m_Height;

        LThisRect.left   = ((m_Width < LWorkAreaRect.Width()) ? (LWorkAreaRect.Width() - m_Width) / 2 : 0);
        LThisRect.right  = LThisRect.left + m_Width;
        LThisRect.top    = ((m_Height < LWorkAreaRect.Height()) ? (LWorkAreaRect.Height() - m_Height) / 2 : 0);
        LThisRect.bottom = LThisRect.top + m_Height;

        SetWindowPos(NULL, LThisRect.left, LThisRect.top, LThisRect.Width(), LThisRect.Height(), SWP_NOZORDER);
    }

    if (m_IsBkBmpIncludeNCArea)
    {
        if ((GetStyle() & WS_CAPTION) == WS_CAPTION)
            m_BckgndOffsetY += (GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYCAPTION));

        if ((GetStyle() & WS_BORDER) == WS_BORDER)
        {
            m_BckgndOffsetX += GetSystemMetrics(SM_CXBORDER);
            m_BckgndOffsetY += GetSystemMetrics(SM_CYBORDER);
        }
    }

    EnableToolTips(YCboolToBOOL(m_IsToolTipsEnabled));

    return TRUE; // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void    CYCDialog::OnOK()
{

    if (!m_IsClosable)
        return; // 防止按下Enter鍵關閉此對話框

    __super::OnOK();
}

void    CYCDialog::OnCancel()
{

    if (!m_IsClosable)
        return; // 防止按下Esc鍵關閉此對話框

    __super::OnCancel();
}

void    CYCDialog::PreInitDialog()
{
    __super::PreInitDialog();

    CRect   LRect;

    GetClientRect(&LRect);

    m_StretchDlgClientWidth  = LRect.Width();
    m_StretchDlgClientHeight = LRect.Height();
}

void    CYCDialog::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
    __super::OnWindowPosChanged(lpwndpos);

    // TODO: Add your message handler code here
    if (m_IsAutoStretchChilds && !IsIconic())
    {
        CRect   LRect(0, 0, 0, 0);

        AdjustWindowRect(&LRect, GetStyle(), GetMenu() ? TRUE : FALSE);

        const int   LClientWidth  = lpwndpos->cx - LRect.Width();
        const int   LClientHeight = lpwndpos->cy - LRect.Height();

        if (m_StretchDlgClientWidth != LClientWidth || m_StretchDlgClientHeight != LClientHeight)
        {
            YCStretchChild(this, LClientWidth * 1.0f / m_StretchDlgClientWidth, LClientHeight * 1.0f / m_StretchDlgClientHeight);

            m_StretchDlgClientWidth  = LClientWidth;
            m_StretchDlgClientHeight = LClientHeight;
        }
    }
}

HCURSOR CYCDialog::OnQueryDragIcon()
{
    // TODO: Add your message handler code here and/or call default
    return (HCURSOR) m_hIcon;
}

LRESULT CYCDialog::OnNcHitTest(CPoint point)
{
    LRESULT LRslt = __super::OnNcHitTest(point);

    return (LRslt == HTCAPTION && !m_IsMovable) ? HTCLIENT : LRslt;
}

BOOL    CYCDialog::OnEraseBkgnd(CDC* pDC)
{
    // TODO: Add your message handler code here and/or call default
    if (m_BkBmp.m_hObject && m_hWnd)
    {
        PaintToDC(pDC);

        return TRUE;
    }

    return __super::OnEraseBkgnd(pDC);
}

void    CYCDialog::OnPaint()
{
    TRACE("CYCDialog::OnPaint\n");

    if (IsIconic()) 
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);

        CRect rect;

        GetClientRect(&rect);

        int x = (rect.Width()  - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else 
    {
        // TODO: Add your message handler code here
        // Do not call __super::OnPaint() for painting messages
        if (m_BkBmp.m_hObject && m_hWnd)
        {
            CPaintDC    dc(this); // device context for painting

            PaintToDC(&dc);
        }
        else
        {
            __super::OnPaint();
        }
    }
}

void    CYCDialog::WMUpdateCommandUI(CCmdUI *ACmdUI)
{
    if (IsWindowVisible())
    {
        OnUpdateCommandUI(ACmdUI);

        UpdateDialogControls(this, FALSE);
    }
}

LRESULT CYCDialog::WMKickIdle(WPARAM wParam, LPARAM lParam)
{
    const LRESULT LRslt = OnKickIdle(wParam, lParam);

    if (IsWindowVisible() && (::GetActiveWindow() == m_hWnd || m_IsInactiveUDCsEnabled))
        UpdateDialogControls(this, FALSE);

    return LRslt;
}

BOOL    CYCDialog::WMNotifyTTNNeedText(UINT AId, NMHDR *ANMHDR, LRESULT *AResult)
{
    TOOLTIPTEXT* const 
        /**/    LTTT = (TOOLTIPTEXT*)ANMHDR;

    if (LTTT->uFlags & TTF_IDISHWND)
    {
        const UINT_PTR  LId = ::GetDlgCtrlID((HWND)ANMHDR->idFrom);

        if (LId)
        {
            GetDlgItemText(PtrToInt(LId), LTTT->szText, sizeof(LTTT->szText));

            return TRUE;
        }
    }

    return FALSE;
} 

IMPLEMENT_CYCDialog_OnUpdateCommandUI(CYCDialog)
{
}

IMPLEMENT_CYCDialog_OnKickIdle(CYCDialog)
{
    return 0;
}

bool    CYCDialog::IsClosable() const
{
    return m_IsClosable;
}

void    CYCDialog::SetIsClosable(bool AValue)
{
    m_IsClosable = AValue;
}

bool    CYCDialog::IsMovable() const
{
    return m_IsMovable;
}

void    CYCDialog::SetIsMovable(bool AValue)
{
    m_IsMovable = AValue;
}

bool    CYCDialog::IsAutoStretchChilds() const
{
    return m_IsAutoStretchChilds;
}

void    CYCDialog::SetIsAutoStretchChilds(bool AValue)
{
    m_IsAutoStretchChilds = AValue;
}

void    CYCDialog::SetBackgroundResID(WORD AValue)
{
    if (m_BkBmp.m_hObject)
        m_BkBmp.DeleteObject();

    m_BkBmp.LoadBitmap(AValue);

    if (m_hWnd)
    {
        //CreateBkDC();
        Invalidate();
        UpdateWindow();
    }
}

bool    CYCDialog::LoadBackgroundImageFile(LPCSTR AFileName)
{
    return false;
}

bool    CYCDialog::IsInactiveUDCsEnabled() const
{
    return m_IsInactiveUDCsEnabled;
}

void    CYCDialog::SetIsInactiveUDCsEnabled(bool AValue)
{
    m_IsInactiveUDCsEnabled = AValue;
}

bool    CYCDialog::IsToolTipsEnabled() const
{
    return m_IsToolTipsEnabled;
}

void    CYCDialog::SetIsToolTipsEnabled(bool AValue)
{
    if (m_IsToolTipsEnabled ^ AValue)
    {
        m_IsToolTipsEnabled = AValue;

        if (m_hWnd)
            EnableToolTips(YCboolToBOOL(m_IsToolTipsEnabled));
    }
}

bool    CYCDialog::PaintToDC(CDC *ADC)
{
    ASSERT(ADC);

    if (ADC && m_hWnd)
    {
        CRect   LClientRect;
        CDC     LBkDC;

        LBkDC.CreateCompatibleDC(ADC);

        DECLARE_GdiSelectBitmap(LBkDC, &m_BkBmp);

        GetClientRect(&LClientRect);

        ADC->BitBlt(LClientRect.left,
            /**/    LClientRect.top,
            /**/    LClientRect.Width(),
            /**/    LClientRect.Height(),
            /**/    &LBkDC,
            /**/    m_BckgndOffsetX,
            /**/    m_BckgndOffsetY,
            /**/    SRCCOPY);

        return true;
    }

    return false;
}

