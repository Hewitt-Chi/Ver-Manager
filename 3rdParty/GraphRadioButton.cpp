// GraphRadioButton.cpp : implementation file
//

#include "stdafx.h"
#include "ButtonST.h"
#include "GraphRadioButton.h"


// CGraphRadioButton

IMPLEMENT_DYNAMIC(CGraphRadioButton, CButton)

CGraphRadioButton::CGraphRadioButton()
{

}

CGraphRadioButton::~CGraphRadioButton()
{
}


BEGIN_MESSAGE_MAP(CGraphRadioButton, CButton)
END_MESSAGE_MAP()

void CGraphRadioButton::PreSubclassWindow() 
{
    UINT nBS;

    nBS = GetButtonStyle();

    // Set initial control type
    DWORD LnTypeStyle = nBS & BS_TYPEMASK;    

    // You should not set the Owner Draw before this call
    // (don't use the resource editor "Owner Draw" or
    // ModifyStyle(0, BS_OWNERDRAW) before calling PreSubclassWindow() )
    ASSERT(LnTypeStyle != BS_OWNERDRAW);

    // Switch to owner-draw
    ModifyStyle(LnTypeStyle, BS_OWNERDRAW, SWP_FRAMECHANGED);

    CButton::PreSubclassWindow();
} // End of PreSubclassWindow

// This function assigns icons to the button.
// Any previous icon or bitmap will be removed.
//
// Parameters:
//        [IN]    nIconIn
//                ID number of the icon resource to show when the mouse is over the button.
//                Pass NULL to remove any icon from the button.
//        [IN]    nIconOut
//                ID number of the icon resource to show when the mouse is outside the button.
//                Can be NULL.
//
// Return value:
//        BTNST_OK
//            Function executed successfully.
//        BTNST_INVALIDRESOURCE
//            Failed loading the specified resource.
//
DWORD CGraphRadioButton::SetIcon(int nIconIn, int nIconOut,int nIconDisable)
{
    HICON        hIconIn            = NULL;
    HICON        hIconOut        = NULL;
    HICON        hIconDisable    = NULL;
    HINSTANCE    hInstResource    = NULL;

    // Find correct resource handle
    hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nIconIn), RT_GROUP_ICON);

    // Set icon when the mouse is IN the button
    hIconIn = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconIn), IMAGE_ICON, 0, 0, 0);

      // Set icon when the mouse is OUT the button
    if (nIconOut)
    {
        if (nIconOut == (int)PtrToInt(BTNST_AUTO_GRAY))
            hIconOut = BTNST_AUTO_GRAY;
        else
            hIconOut = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconOut), IMAGE_ICON, 0, 0, 0);
    } // if
    if (nIconDisable)
    {
        hIconDisable = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconDisable), IMAGE_ICON, 0, 0, 0);
    }

    return SetIcon(hIconIn, hIconOut,hIconDisable);
} // End of SetIcon

// This function assigns icons to the button.
// Any previous icon or bitmap will be removed.
//
// Parameters:
//        [IN]    hIconIn
//                Handle fo the icon to show when the mouse is over the button.
//                Pass NULL to remove any icon from the button.
//        [IN]    hIconOut
//                Handle to the icon to show when the mouse is outside the button.
//                Can be NULL.
//
// Return value:
//        BTNST_OK
//            Function executed successfully.
//        BTNST_INVALIDRESOURCE
//            Failed loading the specified resource.
//
DWORD CGraphRadioButton::SetIcon(HICON hIconIn, HICON hIconOut, HICON hIconDisable)
{
    BOOL        bRetValue;
    ICONINFO    ii;

    // Free any loaded resource
    FreeResources();

    if (hIconIn)
    {
        // Icon when mouse over button?
        m_csIcons[0].hIcon = hIconIn;
        // Get icon dimension
        ::ZeroMemory(&ii, sizeof(ICONINFO));
        bRetValue = ::GetIconInfo(hIconIn, &ii);
        if (bRetValue == FALSE)
        {
            FreeResources();
            return BTNST_INVALIDRESOURCE;
        } // if

        m_csIcons[0].dwWidth    = (DWORD)(ii.xHotspot * 2);
        m_csIcons[0].dwHeight    = (DWORD)(ii.yHotspot * 2);
        ::DeleteObject(ii.hbmMask);
        ::DeleteObject(ii.hbmColor);

        // Icon when mouse outside button?
        if (hIconOut)
        {
            if (hIconOut == BTNST_AUTO_GRAY)
            {
                hIconOut = CreateGrayscaleIcon(hIconIn);
            } // if

            m_csIcons[1].hIcon = hIconOut;
            // Get icon dimension
            ::ZeroMemory(&ii, sizeof(ICONINFO));
            bRetValue = ::GetIconInfo(hIconOut, &ii);
            if (bRetValue == FALSE)
            {
                FreeResources();
                return BTNST_INVALIDRESOURCE;
            } // if

            m_csIcons[1].dwWidth    = (DWORD)(ii.xHotspot * 2);
            m_csIcons[1].dwHeight    = (DWORD)(ii.yHotspot * 2);
            ::DeleteObject(ii.hbmMask);
            ::DeleteObject(ii.hbmColor);
        } // if
        if (hIconDisable)
        {
            // Icon when mouse over button?
            m_csIcons[2].hIcon = hIconDisable;
            // Get icon dimension
            ::ZeroMemory(&ii, sizeof(ICONINFO));
            bRetValue = ::GetIconInfo(hIconDisable, &ii);
            if (bRetValue == FALSE)
            {
                FreeResources();
                return BTNST_INVALIDRESOURCE;
            } // if

            m_csIcons[2].dwWidth    = (DWORD)(ii.xHotspot * 2);
            m_csIcons[2].dwHeight    = (DWORD)(ii.yHotspot * 2);
            ::DeleteObject(ii.hbmMask);
            ::DeleteObject(ii.hbmColor);
        }

    } // if

    Invalidate();

    return BTNST_OK;
} // End of SetIcon

void CGraphRadioButton::FreeResources(BOOL bCheckForNULL)
{
    if (bCheckForNULL)
    {
        // Destroy icons
        // Note: the following two lines MUST be here! even if
        // BoundChecker says they are unnecessary!
        if (m_csIcons[0].hIcon)    ::DestroyIcon(m_csIcons[0].hIcon);
        if (m_csIcons[1].hIcon)    ::DestroyIcon(m_csIcons[1].hIcon);
        
    } // if

    ::ZeroMemory(&m_csIcons, sizeof(m_csIcons));
} // End of FreeResources

// This function creates a grayscale icon starting from a given icon.
// The resulting icon will have the same size of the original one.
//
// Parameters:
//        [IN]    hIcon
//                Handle to the original icon.
//
// Return value:
//        If the function succeeds, the return value is the handle to the newly created
//        grayscale icon.
//        If the function fails, the return value is NULL.
//
HICON CGraphRadioButton::CreateGrayscaleIcon(HICON hIcon)
{
    HICON        hGrayIcon = NULL;
    HDC            hMainDC = NULL, hMemDC1 = NULL, hMemDC2 = NULL;
    BITMAP        bmp;
    HBITMAP        hOldBmp1 = NULL, hOldBmp2 = NULL;
    ICONINFO    csII, csGrayII;
    BOOL        bRetValue = FALSE;

    bRetValue = ::GetIconInfo(hIcon, &csII);
    if (bRetValue == FALSE)    return NULL;

    hMainDC = ::GetDC(m_hWnd);
    hMemDC1 = ::CreateCompatibleDC(hMainDC);
    hMemDC2 = ::CreateCompatibleDC(hMainDC);
    if (hMainDC == NULL || hMemDC1 == NULL || hMemDC2 == NULL)    return NULL;
  
    if (::GetObject(csII.hbmColor, sizeof(BITMAP), &bmp))
    {
        csGrayII.hbmColor = ::CreateBitmap(csII.xHotspot*2, csII.yHotspot*2, bmp.bmPlanes, bmp.bmBitsPixel, NULL);
        if (csGrayII.hbmColor)
        {
            hOldBmp1 = (HBITMAP)::SelectObject(hMemDC1, csII.hbmColor);
            hOldBmp2 = (HBITMAP)::SelectObject(hMemDC2, csGrayII.hbmColor);

            ::BitBlt(hMemDC2, 0, 0, csII.xHotspot*2, csII.yHotspot*2, hMemDC1, 0, 0, SRCCOPY);

            DWORD        dwLoopY = 0, dwLoopX = 0;
            COLORREF    crPixel = 0;
            BYTE        byNewPixel = 0;

            for (dwLoopY = 0; dwLoopY < csII.yHotspot*2; dwLoopY++)
            {
                for (dwLoopX = 0; dwLoopX < csII.xHotspot*2; dwLoopX++)
                {
                    crPixel = ::GetPixel(hMemDC2, dwLoopX, dwLoopY);

                    byNewPixel = (BYTE)((GetRValue(crPixel) * 0.299) + (GetGValue(crPixel) * 0.587) + (GetBValue(crPixel) * 0.114));
                    if (crPixel)    ::SetPixel(hMemDC2, dwLoopX, dwLoopY, RGB(byNewPixel, byNewPixel, byNewPixel));
                } // for
            } // for

            ::SelectObject(hMemDC1, hOldBmp1);
            ::SelectObject(hMemDC2, hOldBmp2);

            csGrayII.hbmMask = csII.hbmMask;

            csGrayII.fIcon = TRUE;
            hGrayIcon = ::CreateIconIndirect(&csGrayII);
        } // if

        ::DeleteObject(csGrayII.hbmColor);
        //::DeleteObject(csGrayII.hbmMask);
    } // if

    ::DeleteObject(csII.hbmColor);
    ::DeleteObject(csII.hbmMask);
    ::DeleteDC(hMemDC1);
    ::DeleteDC(hMemDC2);
    ::ReleaseDC(m_hWnd, hMainDC);

    return hGrayIcon;
} // End of CreateGrayscaleIcon

void CGraphRadioButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
    CDC*    pDC = CDC::FromHandle(lpDIS->hDC);
    //CPen*    pOldPen;    

    pDC->SetBkMode(TRANSPARENT);

    CRect captionRect = lpDIS->rcItem;

    // Read the button's title
    CString sTitle;
    GetWindowText(sTitle);

    __super::DrawItem(lpDIS);
    // Draw the icon
    if (m_csIcons[0].hIcon)
    {
        DrawTheIcon(pDC, !sTitle.IsEmpty(), &lpDIS->rcItem, &captionRect);
    } // if
    
}

void CGraphRadioButton::DrawTheIcon(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpTitle)
{
    BYTE        byIndex        = 0;

    // Select the icon to use
    byIndex = 0;
    
    CRect    rImage;
    PrepareImageRect(bHasTitle, rpItem, rpTitle, m_csIcons[byIndex].dwWidth, m_csIcons[byIndex].dwHeight, &rImage);

    // Ole'!
    pDC->DrawState(    rImage.TopLeft(),
                    rImage.Size(), 
                    m_csIcons[IsWindowEnabled()? 2 : byIndex].hIcon,
                    (DSS_NORMAL), 
                    (CBrush*)NULL);
} // End of DrawTheIcon

//
// Parameters:
//        [IN]    bHasTitle
//                TRUE if the button has a text
//        [IN]    rpItem
//                A pointer to a RECT structure indicating the allowed paint area
//        [IN/OUT]rpTitle
//                A pointer to a CRect object indicating the paint area reserved for the
//                text. This structure will be modified if necessary.
//        [IN]    bIsPressed
//                TRUE if the button is currently pressed
//        [IN]    dwWidth
//                Width of the image (icon or bitmap)
//        [IN]    dwHeight
//                Height of the image (icon or bitmap)
//        [OUT]    rpImage
//                A pointer to a CRect object that will receive the area available to the image

void CGraphRadioButton::PrepareImageRect(BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, DWORD dwWidth, DWORD dwHeight, CRect* rpImage)
{
    CRect rBtn;

    rpImage->CopyRect(rpItem);

    if (bHasTitle == FALSE)
    {
        // Center image horizontally
        rpImage->left += ((rpImage->Width() - (long)dwWidth)/2);
    }
    else
    {
        // Image must be placed just inside the focus rect
        rpImage->left += 3;  
        rpTitle->left += dwWidth + 3;
    }
    // Center image vertically
    rpImage->top += ((rpImage->Height() - (long)dwHeight)/2);    
        
    // If button is pressed then press image also
    rpImage->OffsetRect(1, 1);
} // End of PrepareImageRect

afx_msg void CGraphRadioButton::OnPaint()
{
    __super::OnPaint();

}