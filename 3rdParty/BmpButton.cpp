//=================================================================//
//
//    CBmpButton 
//    Version : 0.1
//    Date : 2008.03.05
//    Author : Andre Kao
//    Email :  andre521@gmail.com
//
//
//=================================================================//

#include "stdafx.h"
#include "BmpButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma comment( lib, "Msimg32.lib" )

/////////////////////////////////////////////////////////////////////////////
// CBmpButton

CBmpButton::CBmpButton()
{
    DisableBitmapLoad = false;
    EnableBitmapLoad = false;
    ClickShift = 0;
    Transparent = false;
    EdgeOff = false;
}

CBmpButton::~CBmpButton()
{
}


BEGIN_MESSAGE_MAP(CBmpButton, CButton)
    //{{AFX_MSG_MAP(CBmpButton)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_ERASEBKGND()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

bool CBmpButton::LoadBitmap(UINT ID)
{
    EnableBmpID = ID;
    if (EnableBitmapLoad)
    {
        Ebitmap.DeleteObject();
    }

    Ebitmap.LoadBitmap(ID);
    Ebitmap.GetBitmap(&Ebmp);

    EbmpWidth = Ebmp.bmWidth;
    EbmpHeight = Ebmp.bmHeight;
    EnableBitmapLoad = true;
    this->RedrawWindow();
    return true;
}

bool CBmpButton::LoadBitmap(LPCSTR lpCursorName)
{    
    HBITMAP LhBitmap = (HBITMAP)LoadImage(NULL, lpCursorName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    if (Ebitmap.m_hObject)
        Ebitmap.DeleteObject();
    if (!LhBitmap)    
        return false;    
    Ebitmap.Attach(LhBitmap);

    Ebitmap.GetBitmap(&Ebmp);

    EbmpWidth = Ebmp.bmWidth;
    EbmpHeight = Ebmp.bmHeight;
    EnableBitmapLoad = true;

    this->RedrawWindow();
    return true;
}

bool CBmpButton::LoadDisableBitmap(UINT ID)
{
    DisableBmpID = ID;
    if (DisableBitmapLoad)
    {
        Dbitmap.DeleteObject();
    }

    Dbitmap.LoadBitmap(ID);
    Dbitmap.GetBitmap(&Dbmp);

    DbmpWidth = Dbmp.bmWidth;
    DbmpHeight = Dbmp.bmHeight;

    DisableBitmapLoad = true;
    this->RedrawWindow();
    return true;
}

bool CBmpButton::ReDrawBitmap(CDC *pDC, bool disable)
{
    CDC dc;
    CBitmap* pOldBitmap;
    dc.CreateCompatibleDC(pDC);

    CRect rect;
    ::GetClientRect(this->m_hWnd, &rect);

    CSize BmpShift;

    if (disable) //draw disable bitmap
    {
        pOldBitmap = dc.SelectObject(&Dbitmap);

        BmpShift.cx = (rect.Width() - 2 - DbmpWidth) / 2;
        BmpShift.cy = (rect.Height() - 2 - DbmpHeight) / 2;
        pDC->BitBlt(2 + ClickShift + BmpShift.cx, 2 + ClickShift + BmpShift.cy, DbmpWidth, DbmpHeight, &dc, 0, 0, SRCCOPY);
    }
    else    //draw enable bitmap
    {
        pOldBitmap = dc.SelectObject(&Ebitmap);

        BmpShift.cx = (rect.Width() - 2 -  EbmpWidth) / 2;
        BmpShift.cy = (rect.Height() - 2 - EbmpHeight) / 2;

#if 0
        if (Transparent)
            TransparentBlt(pDC->m_hDC, 2 + ClickShift + BmpShift.cx, 2 + ClickShift + BmpShift.cy, EbmpWidth, EbmpHeight, dc.m_hDC, 1, 1, EbmpWidth, EbmpHeight, dc.GetPixel(1, 1));
        else
#endif
        pDC->BitBlt(2 + ClickShift + BmpShift.cx, 2 + ClickShift + BmpShift.cy, EbmpWidth, EbmpHeight, &dc, 1, 1, SRCCOPY);
    }

    dc.SelectObject(pOldBitmap);
    dc.DeleteDC();
    return true;
}

void CBmpButton::PreSubclassWindow() 
{
    //set owndraw property
    CButton::PreSubclassWindow();
    ModifyStyle(0, BS_OWNERDRAW);

#if 0
    //設置按鈕的有效區域
    CRgn rgn;
    CRect rc;
    GetClientRect(&rc);

    rgn.CreateRectRgn(rc.left,rc.top,rc.right,rc.bottom);
    SetWindowRgn(rgn,TRUE);
    rgn.DeleteObject();
#endif
}

void CBmpButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    CRect rect =  lpDrawItemStruct->rcItem;

    CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
    const int nSaveDC=pDC->SaveDC();

    //CClientDC pDC(this);
    UINT state = lpDrawItemStruct->itemState;
    CPen pen, pen2, pen3;

    bool btn_disable = ((state & ODS_DISABLED) == ODS_DISABLED);

    //pDC->SetBkMode(TRANSPARENT);

    //button disable
    if (btn_disable && DisableBitmapLoad)
    {
        pen.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
        ReDrawBitmap(pDC, true);
    }
    else if (!btn_disable && EnableBitmapLoad)
    {
        pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
        ReDrawBitmap(pDC, false);
    }

    CGdiObject * const LOldGdiObject = pDC->SelectStockObject(NULL_BRUSH);

    CPen * const hOldPen = pDC->SelectObject(&pen);

    if (!EdgeOff)
    {
        //draw outside
        pDC->Rectangle(&rect);

        //draw button 3D face
        if (!btn_disable)
        {
            if (ClickShift == 0) //button up
            {
                pen2.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
                pDC->SelectObject(&pen2);
                pDC->MoveTo(rect.left + 1, rect.top + 1);
                pDC->LineTo(rect.left + 1, rect.bottom - 2);
                pDC->LineTo(rect.right - 2, rect.bottom - 2);

                pen3.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
                pDC->SelectObject(&pen3);
                pDC->LineTo(rect.right - 2, rect.top + 1);
                pDC->LineTo(rect.left + 1, rect.top + 1);
            }
            else //button down
            {
                pen2.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
                pDC->SelectObject(&pen2);
                pDC->MoveTo(rect.left + 1, rect.top + 1);
                pDC->LineTo(rect.left + 1, rect.bottom - 2);
                pDC->LineTo(rect.right - 2, rect.bottom - 2);

                pen3.CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
                pDC->SelectObject(&pen3);
                pDC->LineTo(rect.right - 2, rect.top + 1);
                pDC->LineTo(rect.left + 1, rect.top + 1);
            }
        }
    }

    pDC->SelectObject(hOldPen);
    pDC->SelectObject(LOldGdiObject);

    //int nMode = pDC->SetBkMode(TRANSPARENT);
    //pDC->SetBkMode(nMode);

    pDC->RestoreDC(nSaveDC);
}

void CBmpButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    ClickShift = 1;
    CButton::OnLButtonDown(nFlags, point);
}

void CBmpButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    ClickShift = 0;
    CButton::OnLButtonUp(nFlags, point);
}

BOOL CBmpButton::OnEraseBkgnd(CDC* pDC) 
{
    // TODO: Add your message handler code here and/or call default
    return true;
    return CButton::OnEraseBkgnd(pDC);
}

void CBmpButton::SetTransparentColor(COLORREF color)
{
    crMask = color;
    Transparent = true;
}

void CBmpButton::SetEdgeOff()
{
    EdgeOff = true;
}


