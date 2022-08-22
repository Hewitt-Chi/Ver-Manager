#include "stdafx.h"

#include "YCUtils.h"
#include "YCBitStatic.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//==========================================================================

IMPLEMENT_DYNAMIC(CYCBitStatic, CStatic)


BEGIN_MESSAGE_MAP(CYCBitStatic, CStatic)
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_WINDOWPOSCHANGED()
END_MESSAGE_MAP()


CYCBitStatic::CYCBitStatic()
: CStatic()
, m_Text("")
, m_BitmapResourceID((DWORD)-1)
, m_IsBmpTransparent(true)
, m_BmpTransparentColor(0)
, m_BkColor(GetSysColor(COLOR_3DFACE))
, m_Layout(loLeft)
, m_FontName("Microsoft Sans Serif")
, m_FontColor(GetSysColor(COLOR_BTNTEXT))
{
}

CYCBitStatic::~CYCBitStatic()
{
}

void CYCBitStatic::PreSubclassWindow()
{
    __super::PreSubclassWindow();

    CreateBkBmp();
    CreateIconBmp();

    m_Font.CreateFont(-12, 0, 0, 0, 0, FALSE, FALSE, 0, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        DEFAULT_PITCH, m_FontName);

    GetWindowText(m_Text);
}

LRESULT CYCBitStatic::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SETTEXT :
        {
            CString LStr((char *)lParam);

            if (LStr != m_Text)
            {
                m_Text = LStr;

                Invalidate(FALSE);
                UpdateWindow();
            }

            return TRUE;
        }
        break;

    case WM_GETTEXTLENGTH :
        return m_Text.GetLength();

    case WM_GETTEXT :
        {
            if ((int)wParam > m_Text.GetLength())
            {
                strcpy_s((char *)lParam, wParam, m_Text);

                return m_Text.GetLength();
            }

            return 0;
        }
        break;

    default : return __super::DefWindowProc(message, wParam, lParam);
    }

    return TRUE;
}

void CYCBitStatic::OnPaint()
{
    if (!m_hWnd || !IsWindowVisible())
        return;

    TRACE("CYCBitStatic::OnPaint();\n");

    CPaintDC    LPaintDC(this); // 控件的設備文件
    CDC         LBuffDC;
    CBitmap     LBuffBitmap;
    CRect       LClientRect;

    // 取得位置
    GetClientRect(LClientRect);

    // 建立暫存影像
    LBuffDC.CreateCompatibleDC(&LPaintDC);
    LBuffBitmap.CreateCompatibleBitmap(&LPaintDC, LClientRect.Width(), LClientRect.Height());
    CBitmap * const LOldBuffBitmap = LBuffDC.SelectObject(&LBuffBitmap);

    CDC     LBkDC;

    LBkDC.CreateCompatibleDC(&LBuffDC);

    DECLARE_GdiSelectBitmap(LBkDC, &m_BkBmp);

    // 畫底圖
    LBuffDC.BitBlt(LClientRect.left, LClientRect.top, LClientRect.Width(), LClientRect.Height(), &LBkDC, LClientRect.left, LClientRect.top, SRCCOPY);

    // 畫icon
    if (m_IconBmp.m_hObject)
    {
        BITMAP  LBMP;

        m_IconBmp.GetBitmap(&LBMP);

        CRect LBmpRect(0, 0, LBMP.bmWidth, LBMP.bmHeight);

        LBmpRect.OffsetRect(LClientRect.left, LClientRect.top);

        switch (m_Layout)
        {
        case loLeft :
            LBmpRect.OffsetRect(0, (LClientRect.Height() - LBmpRect.Height()) / 2);
            LClientRect.left += (LBmpRect.Width() + 2);
            break;

        case loTop  : 
            LBmpRect.OffsetRect((LClientRect.Width() - LBmpRect.Width()) / 2, 0); 
            LClientRect.top += (LBmpRect.Height() + 2);
            break;

        case loRight :
            LBmpRect.OffsetRect(LClientRect.Width() - LBmpRect.Width(),
                (LClientRect.Height() - LBmpRect.Height()) / 2);
            LClientRect.right -= (LBmpRect.Width() + 2);
            break;

        case loBottom :
            LBmpRect.OffsetRect((LClientRect.Width() - LBmpRect.Width()) / 2,
                LClientRect.Height() - LBmpRect.Height());
            LClientRect.bottom -= (LBmpRect.Height() + 2);
            break;

        }


        CDC LIconDC;

        LIconDC.CreateCompatibleDC(&LBuffDC);

        DECLARE_GdiSelectBitmap(LIconDC, &m_IconBmp);

        if (m_IsBmpTransparent)
        {
            if (!::TransparentBlt(LBuffDC.m_hDC, LBmpRect.left, LBmpRect.top, LBmpRect.Width(), LBmpRect.Height(),
                LIconDC.m_hDC, 0, 0, LBMP.bmWidth, LBMP.bmHeight, LIconDC.GetPixel(1, 1)))
            {
                TRACE("Fail transparentblt() error = %d\n", GetLastError());            
            }
        }
        else
        {
            LBuffDC.BitBlt(LBmpRect.left, LBmpRect.top, LBmpRect.Width(), LBmpRect.Height(),
                &LIconDC, 0, 0, SRCCOPY);
        }    
    }



    // 畫出文字
    {
        const LONG_PTR  LWS         = GetWindowLongPtr(m_hWnd, GWL_STYLE);
        int             LTextFormat = DT_WORDBREAK;

        if (IsIncluded(LWS, SS_CENTER))
        {
            LTextFormat |= DT_CENTER;
        }
        else if (IsIncluded(LWS, SS_RIGHT))
        {
            LTextFormat |= DT_RIGHT;
        }
        else
        {
            LTextFormat |= DT_LEFT;

            if (IsIncluded(LWS, SS_LEFTNOWORDWRAP))
                LTextFormat &= ~DT_WORDBREAK;
        }

        // 取得字體，並選入設備文件
        CFont * const LOldFont = LBuffDC.SelectObject(&m_Font);

        // 用透明背景填充設備文件
        LBuffDC.SetBkMode(TRANSPARENT);

        TRACE("CYCBitStatic text area left %d top %d right %d bottom %d\n",
            LClientRect.left, LClientRect.top, LClientRect.right, LClientRect.bottom);

        // 顯示文字
        CRect LTextRect = LClientRect;

        // 設定文字顯示顏色
        LBuffDC.SetTextColor(m_FontColor);

        // 計算出要畫出這些文字其區域的大小
        LBuffDC.DrawText(m_Text, &LTextRect, DT_CALCRECT | LTextFormat);

        if (IsIncluded(LWS, SS_CENTER))
        {
            switch (m_Layout)
            {
            case loLeft :
            case loRight :
                LTextRect.OffsetRect((LClientRect.Width() - LTextRect.Width()) / 2, (LClientRect.Height() - LTextRect.Height()) / 2);
                break;

            case loTop :
                LTextRect.OffsetRect((LClientRect.Width() - LTextRect.Width()) / 2, 0);
                break;

            case loBottom :
                LTextRect.OffsetRect((LClientRect.Width() - LTextRect.Width()) / 2, LClientRect.Height() - LTextRect.Height());
                break;
            }
        }
        else if (IsIncluded(LWS, SS_RIGHT))
        {
            switch (m_Layout)
            {
            case loLeft :
            case loRight :
                LTextRect.OffsetRect(LClientRect.Width() - LTextRect.Width(), (LClientRect.Height() - LTextRect.Height()) / 2);
                break;

            case loTop :
                LTextRect.OffsetRect(LClientRect.Width() - LTextRect.Width(), 0);
                break;

            case loBottom :
                LTextRect.OffsetRect(LClientRect.Width() - LTextRect.Width(), LClientRect.Height() - LTextRect.Height());
                break;
            }
        }
        else
        {
            switch (m_Layout)
            {
            case loLeft :
            case loRight :
                LTextRect.OffsetRect(0, (LClientRect.Height() - LTextRect.Height()) / 2);
                break;

            case loTop :
                LTextRect.OffsetRect(0, 0);
                break;

            case loBottom :
                LTextRect.OffsetRect(0, LClientRect.Height() - LTextRect.Height());
                break;
            }
        }

        // 畫出文字
        LBuffDC.DrawText(m_Text, LTextRect, LTextFormat);
        LBuffDC.SelectObject(LOldFont);
    }

    GetClientRect(&LClientRect);

    // 畫到控件上
    LPaintDC.BitBlt(LClientRect.left, LClientRect.top, LClientRect.Width(), LClientRect.Height(),
        &LBuffDC, LClientRect.left, LClientRect.top, SRCCOPY);

    LBuffDC.SelectObject(LOldBuffBitmap);
}

void CYCBitStatic::SetBitmapResourceID(WORD AId)
{
    if (AId != m_BitmapResourceID)
    {
        DestroyIconBmp();
        m_BitmapResourceID = AId;
        CreateIconBmp();

        if (m_hWnd)
            Invalidate();
    }
}

void CYCBitStatic::SetIsBmpTransparent(bool AValue)
{
    if (m_IsBmpTransparent != AValue)
    {
        m_IsBmpTransparent = AValue;

        if (m_hWnd)
            Invalidate();
    }
}

void CYCBitStatic::SetBmpTransparentColor(COLORREF AValue)
{
    if (m_BmpTransparentColor != AValue)
    {
        m_BmpTransparentColor = AValue;

        if (m_hWnd)
            Invalidate();
    }
}

void CYCBitStatic::SetBkColor(COLORREF AValue)
{
    if (m_BkColor != AValue)
    {
        m_BkColor = AValue;

        if (m_hWnd)
            Invalidate();
    }
}

void CYCBitStatic::SetLayout(enmYCLayout AValue)
{
    if (m_Layout != AValue)
    {
        m_Layout = AValue;

        if (m_hWnd)
            Invalidate();
    }
}

void CYCBitStatic::CreateIconBmp()
{
    if (!m_IconBmp.m_hObject && m_hWnd)
    {
        m_IconBmp.LoadBitmap(m_BitmapResourceID);
    }
}

void CYCBitStatic::DestroyIconBmp()
{
    m_IconBmp.DeleteObject();
}

BOOL CYCBitStatic::OnEraseBkgnd(CDC* pDC)
{
    // TODO: Add your message handler code here and/or call default
    if (!m_hWnd)
        return __super::OnEraseBkgnd(pDC);

    CDC     LDC;
    CBitmap LBitmap;
    CWnd    *LParent = GetParent();

    ASSERT(LParent);

    CRect LClientRect;

    // 取出自已的client rect並轉換成parent的座標
    GetClientRect(&LClientRect);

    CDC     LBkDC;

    LBkDC.CreateCompatibleDC(&LDC);

    DECLARE_GdiSelectBitmap(LBkDC, &m_BkBmp);

    if (LParent && IsIncluded(::GetWindowLongPtr(m_hWnd, GWL_EXSTYLE), WS_EX_TRANSPARENT))
    {
        CRect   LParentClientRect;

        // 取出Parent的 client rect
        LParent->GetClientRect(LParentClientRect);

        // 建立parent的影像buffer
        LDC.CreateCompatibleDC(&CClientDC(LParent));
        LBitmap.CreateCompatibleBitmap(&CClientDC(LParent), LParentClientRect.Width(), LParentClientRect.Height());
        CBitmap * const LOldBitmap = LDC.SelectObject(&LBitmap);

        // 轉換自已的client rect成為parent的座標
        ClientToScreen(&LClientRect);
        LParent->ScreenToClient(&LClientRect);

        CRgn    LClipRgn;

        // 在parent的影像buffer上建立clip rgn
        LClipRgn.CreateRectRgn(LClientRect.left, LClientRect.top, LClientRect.right, LClientRect.bottom);
        LDC.SelectClipRgn(&LClipRgn);

        // 要求parent重繪
        LParent->SendMessage(WM_ERASEBKGND, (WPARAM)LDC.m_hDC, 0);


        // 把parent重繪的結果畫到自已的背景buffer上
        LBkDC.BitBlt(0, 0, LClientRect.Width(), LClientRect.Height(), &LDC, LClientRect.left, LClientRect.top, SRCCOPY);
        LDC.SelectObject(LOldBitmap);
    }
    else
    {
        LBkDC.FillRect(&LClientRect, &CBrush(m_BkColor));
    }

    return TRUE;

    return __super::OnEraseBkgnd(pDC);
}

void CYCBitStatic::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
    CStatic::OnWindowPosChanged(lpwndpos);

    // TODO: Add your message handler code here
    CreateBkBmp();
}

void CYCBitStatic::CreateBkBmp()
{
    if (!m_hWnd)
        return;


    CRect       LClientRect;

    GetClientRect(&LClientRect);

    m_BkBmp.DeleteObject();
    m_BkBmp.CreateCompatibleBitmap(&CClientDC(this), LClientRect.Width(), LClientRect.Height());
}
