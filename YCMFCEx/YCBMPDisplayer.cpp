#include "StdAfx.h"

#include "YCUtils.h"
#include "YCObject.h"
#include "YCException.h"
#include "YCBMPDisplayer.h"

#include <shlwapi.h>
#include <afxdlgs.h>

#include <GdiplusImaging.h>

#pragma comment(lib, "Vfw32.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define CoorYToMemY(H, Y)                   (H - Y - 1)


BOOL CYCBMPDisplayer::m_IsClassRegistered = CYCBMPDisplayer::RegisterThisClass();
char *CYCBMPDisplayer::m_ClassName = "CYCBMPDisplayer";


BOOL CYCBMPDisplayer::RegisterThisClass()
{
    WNDCLASS LWndClass;

    LWndClass.style         = 0;                                                 
    LWndClass.lpfnWndProc   = ::DefWindowProc; // must be this value
    LWndClass.cbClsExtra    = 0;                         
    LWndClass.cbWndExtra    = 0;                               
    LWndClass.hInstance     = (HINSTANCE)::GetModuleHandle(NULL);        
    LWndClass.hIcon         = NULL;     // child window has no icon         
    LWndClass.hCursor       = NULL;   // we use OnSetCursor                  
    LWndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);                
    LWndClass.lpszMenuName  = NULL;  // no menu                             
    LWndClass.lpszClassName = m_ClassName;                          

    return AfxRegisterClass(&LWndClass);
}

IMPLEMENT_DYNAMIC(CYCBMPDisplayer, CWnd)


BEGIN_MESSAGE_MAP(CYCBMPDisplayer, CWnd)
    ON_WM_CONTEXTMENU()
    ON_WM_DESTROY()
    ON_WM_SIZE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDBLCLK()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()
    ON_WM_MOUSEWHEEL()
    ON_WM_MOUSEMOVE()
    ON_WM_PAINT()
END_MESSAGE_MAP()


CYCBMPDisplayer::CYCBMPDisplayer()
: CWnd()
, m_Options(opZoomable)
, m_VisibleMenuItems(miAll)
, m_ZoomRate(1.0)
, m_ZoomRateStep(0.2)
, m_MaxSelectedAreasCount(1)
, m_MaxSelectedLinesCount(1)
, m_UpdateCount(0)
, m_IsUIBuffChanged(false)
, m_ActiveUserOperation(uoNone)
, m_ActiveMouseAction(maNone)
, m_EventSinker(NULL)
, m_ShowMousePointOption(smpNone)
{
    m_ReticleFeature.m_Displayer = this;
    m_ReticleFeature.SetIsOwnedByDisplayer(false);
    m_ReticleFeature.SetIsVisible(false);
    m_PrivateFeatures.push_back(&m_ReticleFeature);

    m_MousePointTextFeature.m_Displayer = this;
    m_MousePointTextFeature.SetIsOwnedByDisplayer(false);
    m_MousePointTextFeature.SetIsVisible(false);
    m_MousePointTextFeature.SetCoorType(m_MousePointTextFeature.ctDisp);
    m_PrivateFeatures.push_back(&m_MousePointTextFeature);
}

CYCBMPDisplayer::~CYCBMPDisplayer(void)
{
    while (m_Features.size() > 0)
        DeleteFeature(0);
}

void CYCBMPDisplayer::PreSubclassWindow()
{


    // TODO:  Add extra initialization here
#ifdef _DEBUG
    m_ShowBMPCount = 0;
#endif
    m_UIBuff.DibHandle = DrawDibOpen();
    SyncUIBuff();


    CRect   LRect;

    GetClientRect(&LRect);

    if (m_BMP.RawHeight() == 0 && m_BMP.RawWidth() == 0)
        SetBMPSize(LRect.Width(), LRect.Height());

    __super::PreSubclassWindow();
}

void CYCBMPDisplayer::SetOptions(enmOptions AValue)
{
    if (m_Options != AValue)
    {
        BeginUpdate();

        if (IsExcluded(AValue, opBMPVisibleAreaMovable) &&
            (m_ActiveUserOperation == uoMoveBMPVisibleArea))
            SetActiveUserOperation(uoNone);

        if (IsExcluded(AValue, opAreaSelectable) &&
            (m_ActiveUserOperation == uoSelectArea))
            SetActiveUserOperation(uoNone);

        if (IsExcluded(AValue, opLineSelectable) &&
            (m_ActiveUserOperation == uoSelectLine))
            SetActiveUserOperation(uoNone);

        m_ReticleFeature.SetIsVisible(IsIncluded(AValue, opReticleVisible));

        m_Options = AValue;

        EndUpdate();
    }
}

void CYCBMPDisplayer::SetIsReticleVisible(bool AValue)
{
    if (IsReticleVisible() != AValue)
    {
        if (AValue)
            SetOptions(m_Options | opReticleVisible);
        else SetOptions(m_Options & ~opReticleVisible);

        UpdateUIBuff();
    }
}

void CYCBMPDisplayer::SetIsSelectedAreaReticleVisible(bool AValue)
{
    if (IsSelectedAreaReticleVisible() != AValue)
    {
        if (AValue)
            SetOptions(m_Options | opSelectedAreaReticleVisible);
        else SetOptions(m_Options & ~opSelectedAreaReticleVisible);

        UpdateUIBuff();
    }
}

void CYCBMPDisplayer::SetIsBMPVisibleAreaMovable(bool AValue)
{
    if (AValue)
        SetOptions(m_Options | opBMPVisibleAreaMovable);
    else SetOptions(m_Options & ~opBMPVisibleAreaMovable);
}

void CYCBMPDisplayer::SetIsAreaSelectable(bool AValue)
{
    if (AValue)
        SetOptions(m_Options | opAreaSelectable);
    else SetOptions(m_Options & ~opAreaSelectable);
}

void CYCBMPDisplayer::SetIsLineSelectable(bool AValue)
{
    if (AValue)
        SetOptions(m_Options | opLineSelectable);
    else SetOptions(m_Options & ~opLineSelectable);
}

void CYCBMPDisplayer::SetIsZoomable(bool AValue)
{
    if (AValue)
        SetOptions(m_Options | opZoomable);
    else SetOptions(m_Options & ~opZoomable);
}

void CYCBMPDisplayer::SetMaxSelectedAreasCount(int AValue)
{
    ASSERT(AValue >= 0);

    if (m_MaxSelectedAreasCount != AValue)
    {
        m_MaxSelectedAreasCount = AValue;

        while ((INT64)m_BMP.SelectedAreas.size() > AValue)
            m_BMP.SelectedAreas.pop_back();
    }
}

void CYCBMPDisplayer::SetMaxSelectedLinesCount(int AValue)
{
    ASSERT(AValue >= 0);

    if (m_MaxSelectedLinesCount != AValue)
    {
        m_MaxSelectedAreasCount = AValue;

        while ((INT64)m_BMP.SelectedLines.size() > m_MaxSelectedAreasCount)
            m_BMP.SelectedLines.pop_back();
    }
}

void CYCBMPDisplayer::SetBMPSize(int AWidth, int AHeight)
{
    if (!m_BMP.Info)
        InitBMPInfoRW8();

    if ((m_BMP.RawWidth() != AWidth) || (m_BMP.RawHeight() != AHeight))
    {
        m_BMP.Info->bmiHeader.biWidth = AWidth;
        m_BMP.Info->bmiHeader.biHeight = AHeight;

        // 重新配置影像資料暫存區
        m_BMP.DataBMP = static_cast<BYTE *>(YCrealloc(m_BMP.DataBMP    , YCWidthToBmpWidth(AWidth) * AHeight));
        ZeroMemory(m_BMP.DataBMP , YCWidthToBmpWidth(AWidth) * AHeight);

        // 清除相關參數
        m_BMP.SelectedAreas.clear();
        m_BMP.SelectedLines.clear();

        // 把顯示區域調整到BMP範圍內
        YCAdjRectToInsideAnother(m_BMP.VisibleArea, CRect(0, 0, m_BMP.RawWidth(), m_BMP.RawHeight()), false);

        // 重新調整顯示區域
        AdjAreaByZoomRate();
    }
}

void CYCBMPDisplayer::SetPixelRealWidthuM(double AValue)
{
    if (m_BMP.PixelRealWidthuM != AValue)
    {
        m_BMP.PixelRealWidthuM = AValue;

        // 如果有show 刻度的話，重繪
    }
}

SIZE CYCBMPDisplayer::ClientSize() const
{
    CRect LRect;

    this->GetClientRect(&LRect);

    return LRect.Size();
}

void CYCBMPDisplayer::SetPixelRealHeightuM(double AValue)
{
    if (m_BMP.PixelRealHeightuM != AValue)
    {
        m_BMP.PixelRealHeightuM = AValue;

        // 如果有show 刻度的話，重繪
    }
}

void CYCBMPDisplayer::SetActiveUserOperation(enmUserOperation AValue)
{
    if (m_ActiveUserOperation != AValue)
    {
        enmUserOperation LNewValue = AValue;

        switch (AValue)
        {
        case uoMoveBMPVisibleArea :
            if (IsExcluded(m_Options, opBMPVisibleAreaMovable))
                LNewValue = m_ActiveUserOperation;
            break;

        case uoSelectArea : 
            if (IsExcluded(m_Options, opAreaSelectable))
                LNewValue = m_ActiveUserOperation;
            break;

        case uoSelectLine :
            if (IsExcluded(m_Options, opLineSelectable))
                LNewValue = m_ActiveUserOperation;
            break;
        }

        m_ActiveUserOperation = LNewValue;
    }
}

void CYCBMPDisplayer::SetZoomRate(double AValue)
{
    ASSERT(AValue > 0);

    if ((AValue != m_ZoomRate) && (AValue > 0) && (IsIncluded(m_Options, opZoomable)))
    {
        m_ZoomRate = AValue;

        AdjAreaByZoomRate();
        DoOnZoom();
    }
}

void CYCBMPDisplayer::SetShowMousePointOption(enmShowMousePointOption AValue)
{
    if (m_ShowMousePointOption != AValue)
    {
        m_ShowMousePointOption = AValue;

        if (m_ShowMousePointOption != smpNone)
        {
            CString LPntText;

            LPntText.Format("(% 4d, % 4d)", m_MousePointTextFeature.Point().x, m_MousePointTextFeature.Point().y);

            int     LTextFormat = DT_SINGLELINE;
            CRect   LTextRect(0, 0, 0, 0);

            // 計算出要畫出這些文字其區域的大小
            m_UIBuff.DC.DrawText(LPntText, &LTextRect, DT_CALCRECT | LTextFormat);

            switch (m_ShowMousePointOption)
            {
            case smpLeftTop :
                LTextRect.OffsetRect(10, 10);
                break;

            case smpTop :
                LTextRect.OffsetRect((m_UIBuff.ClientWidth() - LTextRect.Width()) / 2, 10);
                break;

            case smpRightTop :
                LTextRect.OffsetRect(m_UIBuff.ClientWidth() - LTextRect.Width() - 10, 10);
                break;

            case smpLeftBottom :
                LTextRect.OffsetRect(10, m_UIBuff.ClientHeight() - LTextRect.Height() - 10);
                break;

            case smpBottom :
                LTextRect.OffsetRect((m_UIBuff.ClientWidth() - LTextRect.Width()) / 2, m_UIBuff.ClientHeight() - LTextRect.Height() - 10);
                break;

            case smpRightBottom :
                LTextRect.OffsetRect(m_UIBuff.ClientWidth() - LTextRect.Width() - 10, m_UIBuff.ClientHeight() - LTextRect.Height() - 10);
                break;
            }

            m_MousePointTextFeature.SetRect(LTextRect);
            m_MousePointTextFeature.SetIsVisible(true);
        }
        else m_MousePointTextFeature.SetIsVisible(false);

        UpdateUIBuff();
    }
}

void CYCBMPDisplayer::EndUpdate()
{
    ASSERT(m_UpdateCount > 0);

    m_UpdateCount --;

    if (m_UpdateCount == 0)
    {
        if (m_IsUIBuffChanged)
        {
            UpdateUIBuff();
        }
    }
}

void CYCBMPDisplayer::BMPFitUISize()
{
    if (m_BMP.Info && m_hWnd)
    {   
        double LZoomRate, LZoomRateY;

        LZoomRate  = m_UIBuff.ClientWidth()  * 1.0 / m_BMP.RawWidth();
        LZoomRateY = m_UIBuff.ClientHeight() * 1.0 / m_BMP.RawHeight();

        LZoomRate = min(LZoomRate, LZoomRateY);

        SetZoomRate(LZoomRate);
    }
}

void CYCBMPDisplayer::UIFitBMPSize()
{
    ASSERT(m_hWnd);
    ASSERT(m_BMP.Info);

    if (m_hWnd && m_BMP.Info)
    {
        CRect LWinRect;
        CRect LClientRect;

        GetWindowRect(&LWinRect);
        GetClientRect(&LClientRect);

        SetWindowPos(
            NULL,
            0,
            0,
            m_BMP.RawWidth()  + (LWinRect.Width()  - LClientRect.Width()),
            m_BMP.RawHeight() + (LWinRect.Height() - LClientRect.Height()),
            SWP_NOMOVE | SWP_NOZORDER);
    }
}

void CYCBMPDisplayer::MoveBMPVisibleAreaCenterTo(enmYCLayout ALayout)
{
    if (IsBMPVisibleAreaMovable() || ALayout == loCenter)
    {
        ASSERT(m_BMP.Info);

        if (m_BMP.Info)
        {

            long LXs[3] = 
            {
                0, 
                m_BMP.RawWidth() / 2 - m_BMP.VisibleArea.Width() / 2,
                m_BMP.RawWidth()     - m_BMP.VisibleArea.Width()
            };

            long LYs[3] = 
            {
                0, 
                m_BMP.RawHeight() / 2 - m_BMP.VisibleArea.Height() / 2,
                m_BMP.RawHeight()     - m_BMP.VisibleArea.Height()
            };

            switch (ALayout)
            {
            case (loLeftTop)    : m_BMP.VisibleArea.MoveToXY(LXs[0], LYs[0]); break;
            case (loTop)        : m_BMP.VisibleArea.MoveToXY(LXs[1], LYs[0]); break;
            case (loRightTop)   : m_BMP.VisibleArea.MoveToXY(LXs[2], LYs[0]); break;
            case (loLeft)       : m_BMP.VisibleArea.MoveToXY(LXs[0], LYs[1]); break;
            case (loCenter)     : m_BMP.VisibleArea.MoveToXY(LXs[1], LYs[1]); break;
            case (loRight)      : m_BMP.VisibleArea.MoveToXY(LXs[2], LYs[1]); break;
            case (loLeftBottom) : m_BMP.VisibleArea.MoveToXY(LXs[0], LYs[2]); break;
            case (loBottom)     : m_BMP.VisibleArea.MoveToXY(LXs[1], LYs[2]); break;
            case (loRightBottom): m_BMP.VisibleArea.MoveToXY(LXs[2], LYs[2]); break;
            }

            UpdateUIBuff();
        }
    }
}

void CYCBMPDisplayer::MoveBMPVisibleAreaCenterTo(const POINT &APoint)
{
    MoveBMPVisibleAreaCenterTo(APoint.x, APoint.y);
}

void CYCBMPDisplayer::MoveBMPVisibleAreaCenterTo(long AX, long AY)   
{
    if (IsBMPVisibleAreaMovable() || (AX == m_BMP.RawWidth() / 2 && AY == m_BMP.RawHeight() / 2))
    {
        m_BMP.VisibleArea.MoveToXY(AX - m_BMP.VisibleArea.Width() / 2, AY - m_BMP.VisibleArea.Height() / 2);

        if (m_BMP.VisibleArea.left < 0)
        {
            m_BMP.VisibleArea.MoveToX(0);
        }

        if (m_BMP.VisibleArea.top < 0)
        {
            m_BMP.VisibleArea.MoveToY(0);
        }

        if (m_BMP.VisibleArea.right > m_BMP.RawWidth())
        {
            m_BMP.VisibleArea.MoveToX(m_BMP.RawWidth() - m_BMP.VisibleArea.Width());
        }

        if (m_BMP.VisibleArea.bottom > m_BMP.RawHeight())
        {
            m_BMP.VisibleArea.MoveToY(m_BMP.RawHeight() - m_BMP.VisibleArea.Height());
        }

        UpdateUIBuff();
    }
}

void CYCBMPDisplayer::ShowBMPBMP(void *ABMP, int ABMPSize)
{
    const int LBMPWidth = YCWidthToBmpWidth(m_BMP.RawWidth());

    ASSERT(m_BMP.Info);
    ASSERT(m_BMP.DataBMP);
    ASSERT(ABMPSize == LBMPWidth * m_BMP.RawHeight());

    if (m_BMP.DataBMP && ABMPSize == LBMPWidth * m_BMP.RawHeight())
    {
        memcpy_s(m_BMP.DataBMP, LBMPWidth * m_BMP.RawHeight(), ABMP, ABMPSize);

        m_BMP.DataValid = true;

#ifdef _DEBUG
        m_ShowBMPCount ++;
#endif
        UpdateUIBuff();
    }
}

void CYCBMPDisplayer::ShowBMPRaw(void *ABMP, int ABMPSize)
{
    ASSERT(m_BMP.Info);
    ASSERT(m_BMP.DataBMP);
    ASSERT(ABMPSize == m_BMP.RawWidth() * m_BMP.RawHeight());

    if (m_BMP.DataBMP && ABMPSize == m_BMP.RawWidth() * m_BMP.RawHeight())
    {
        const int LRawWidth = m_BMP.RawWidth();
        const int LBMPWidth = YCWidthToBmpWidth(LRawWidth);

        if (LBMPWidth == LRawWidth)
        {
            // 原始寬度即為4的倍數，不用一行一行搬資料
            ShowBMPBMP(ABMP, ABMPSize);
        }
        else
        {
            BYTE *LSrc     = static_cast<BYTE *>(ABMP);
            BYTE *LDestRaw = m_BMP.DataBMP;

            ZeroMemory(m_BMP.DataBMP, LBMPWidth * m_BMP.RawHeight());

            for (int I = 0; I < m_BMP.RawHeight(); I ++)
            {
                memcpy_s(LDestRaw, LRawWidth, LSrc, LRawWidth);

                LSrc     += LRawWidth;
                LDestRaw += LBMPWidth;
            }

            m_BMP.DataValid = true;

#ifdef _DEBUG
            m_ShowBMPCount ++;
#endif
            UpdateUIBuff();
        }
    }
}

void CYCBMPDisplayer::ClearBMPData()
{
    m_BMP.DataValid = false;
}

void CYCBMPDisplayer::ReadBMPBMP(OUT void *ABMP, IN int ABMPSize) const
{
    const int LBMPWidth = YCWidthToBmpWidth(m_BMP.RawWidth());

    ASSERT(m_BMP.Info);
    ASSERT(m_BMP.DataBMP);
    ASSERT(ABMP);
    ASSERT(ABMPSize >= LBMPWidth * m_BMP.RawHeight());

    if (m_BMP.DataBMP && m_BMP.DataValid && ABMPSize >= LBMPWidth * m_BMP.RawHeight())
    {        
        memcpy_s(ABMP, ABMPSize, m_BMP.DataBMP, LBMPWidth * m_BMP.RawHeight());
    }
    else ZeroMemory(ABMP, ABMPSize);
}

void CYCBMPDisplayer::ReadBMPRaw(OUT void *ABMP, IN int ABMPSize) const
{
    ASSERT(m_BMP.Info);
    ASSERT(m_BMP.DataBMP);
    ASSERT(ABMP);
    ASSERT(ABMPSize >= m_BMP.RawWidth() * m_BMP.RawHeight());

    const int LBMPWidth = YCWidthToBmpWidth(m_BMP.RawWidth());

    if (LBMPWidth == m_BMP.RawWidth())
        ReadBMPBMP(ABMP, ABMPSize);
    else if (ABMPSize >= m_BMP.RawWidth() * m_BMP.RawHeight())
    {
        ZeroMemory(ABMP, ABMPSize);

        if (m_BMP.DataBMP && m_BMP.DataValid)
        {

            BYTE *LSrc = static_cast<BYTE *>(m_BMP.DataBMP);
            BYTE *LDst = static_cast<BYTE *>(ABMP);

            for (int I = 0; I < m_BMP.RawHeight(); I ++)
            {
                memcpy_s(LDst, m_BMP.RawWidth(), LSrc, m_BMP.RawWidth());

                LSrc += LBMPWidth;
                LDst += m_BMP.RawWidth();
            }
        }
    }
}

int CYCBMPDisplayer::AppendSelectedArea(const CRect &AArea)
{
    InsertSelectedArea(SelectedAreasCount(), AArea);

    return SelectedAreasCount() - 1;
}

void CYCBMPDisplayer::InsertSelectedArea(int AIdx, const CRect &AArea)
{
    if (((m_Options & opAreaSelectable) == opAreaSelectable) &&
        ((INT64)m_BMP.SelectedAreas.size() < m_MaxSelectedAreasCount))
    {
        CRect LNewArea = AArea;

        YCAdjRectToInsideAnother(LNewArea, CRect(0, 0, m_BMP.RawWidth(), m_BMP.RawHeight()), true);

        if (AIdx == SelectedAreasCount())
            m_BMP.SelectedAreas.push_back(AArea);
        else if ((AIdx < 0) || (AIdx > SelectedAreasCount()))
            YCThrowOutOfRangeException(0, SelectedAreasCount(), AIdx);
        else
        {
            m_BMP.SelectedAreas.insert(m_BMP.SelectedAreas.begin() + AIdx, LNewArea);
        }

        UpdateUIBuff();
    }
}

void CYCBMPDisplayer::SetSelectedArea(int AIdx, const CRect &AArea)
{
    if (AIdx == SelectedAreasCount())
    {
        InsertSelectedArea(AIdx, AArea);
    }
    else if ((AIdx < 0) || (AIdx > SelectedAreasCount()))
    {
        AfxThrowInvalidArgException();
    }
    else
    {
        CRect LNewArea = AArea;

        YCAdjRectToInsideAnother(LNewArea, CRect(0, 0, m_BMP.RawWidth(), m_BMP.RawHeight()), true);
        m_BMP.SelectedAreas[AIdx] = LNewArea;

        UpdateUIBuff();
    }
}


long CYCBMPDisplayer::ReadSelectedDataBMP(OUT void *ABuff, int ABuffSize, int ASelectedIdx/* = 0*/) const
{
    const CRect LSelectedArea       = m_BMP.SelectedAreas[ASelectedIdx];
    const int   LBMPWidth           = YCWidthToBmpWidth(m_BMP.RawWidth());
    const int   LSelectedBMPWidth   = YCWidthToBmpWidth(LSelectedArea.Width());
    long        LRslt               = 0;
    BYTE        *LDest              = static_cast<BYTE *>(ABuff);

    ASSERT(ABuffSize >= LSelectedBMPWidth * LSelectedArea.Height());

    if (ABuffSize >= LSelectedBMPWidth * LSelectedArea.Height())
    {
        // 清空資料    
        ZeroMemory(ABuff, LSelectedBMPWidth * LSelectedArea.Height());

        for (int LY = LSelectedArea.bottom; LY > LSelectedArea.top; LY --)
        {
            memcpy_s(
                LDest,
                LSelectedArea.Width(),
                &m_BMP.DataBMP[CoorYToMemY(m_BMP.RawHeight(), LY) * LBMPWidth + LSelectedArea.left],
                LSelectedArea.Width());

            LDest += LSelectedBMPWidth;
            LRslt += LSelectedArea.Width();
        }
    }

    return LRslt;
}

long CYCBMPDisplayer::ReadSelectedDataRaw(OUT void *ABuff, int ABuffSize, int ASelectedIdx/* = 0*/) const
{
    const CRect LSelectedArea       = m_BMP.SelectedAreas[ASelectedIdx];
    const int   LBMPWidth           = YCWidthToBmpWidth(m_BMP.RawWidth());
    long        LRslt               = 0;
    BYTE        *LDest              = static_cast<BYTE *>(ABuff);

    ASSERT(ABuffSize >= LSelectedArea.Width() * LSelectedArea.Height());

    if (ABuffSize >= LSelectedArea.Width() * LSelectedArea.Height())
    {
        // 清空資料
        ZeroMemory(ABuff, LSelectedArea.Width() * LSelectedArea.Height());

        for (int LY = LSelectedArea.bottom; LY > LSelectedArea.top; LY --)
        {
            memcpy_s(
                LDest,
                LSelectedArea.Width(),
                &m_BMP.DataBMP[CoorYToMemY(m_BMP.RawHeight(), LY) * LBMPWidth + LSelectedArea.left],
                LSelectedArea.Width());

            LDest += LSelectedArea.Width();
            LRslt += LSelectedArea.Width();
        }
    }

    return LRslt;
}

long CYCBMPDisplayer::ReadRow(OUT void *ABuff, int ABuffSize, int ARowIdx) const
{
    ASSERT(ARowIdx >= 0 && ARowIdx < m_BMP.RawHeight());
    ASSERT(ABuffSize >= m_BMP.RawWidth());

    if (ARowIdx >= 0 && ARowIdx < m_BMP.RawHeight() && ABuffSize >= m_BMP.RawWidth())
    {
        const int   LBMPWidth = YCWidthToBmpWidth(m_BMP.RawWidth());
        long        LRslt     = m_BMP.RawWidth();
        BYTE        *LSrc     = m_BMP.DataBMP + ARowIdx * LBMPWidth;

        memcpy_s(ABuff, ABuffSize, LSrc, LRslt);

        return LRslt;
    }

    return 0;
}

long CYCBMPDisplayer::ReadCol(OUT void *ABuff, int ABuffSize, int AColIdx) const
{
    ASSERT(AColIdx >= 0 && AColIdx < m_BMP.RawWidth());
    ASSERT(ABuffSize >= m_BMP.RawHeight());

    if (AColIdx >= 0 && AColIdx < m_BMP.RawWidth() && ABuffSize >= m_BMP.RawHeight())
    {
        const int   LBMPWidth   = YCWidthToBmpWidth(m_BMP.RawWidth());
        BYTE        *LSrc       = m_BMP.DataBMP + AColIdx;
        BYTE        *LDst       = static_cast<BYTE *>(ABuff);
        long        LRslt       = 0;

        for (int I = 0; I < m_BMP.RawHeight(); I ++)
        {
            *LDst = *LSrc;
            LDst ++;
            LSrc += LBMPWidth;
            LRslt ++;
        }

        ASSERT(LRslt == m_BMP.RawHeight());

        return LRslt;
    }

    return 0;
}

void CYCBMPDisplayer::ClearSelectedAreas()
{
    m_BMP.SelectedAreas.clear();

    UpdateUIBuff(utAllSelectedAreas);

    DoOnClearSelectedAreas();
}

int CYCBMPDisplayer::AppendSelectedLine(const CYCLine &ALine)
{
    InsertSelectedLine(SelectedLinesCount(), ALine);

    return SelectedLinesCount() - 1;
}

void CYCBMPDisplayer::InsertSelectedLine(int AIdx, const CYCLine &ALine)
{
    if (((m_Options & opLineSelectable) == opLineSelectable) && 
        ((INT64)m_BMP.SelectedLines.size() < m_MaxSelectedLinesCount))
    {
        CYCLine LNewLine = ALine;

        if (AIdx == SelectedLinesCount())
            m_BMP.SelectedLines.push_back(ALine);
        else if ((AIdx < 0) || (AIdx > SelectedLinesCount()))
            YCThrowOutOfRangeException(0, SelectedLinesCount(), AIdx);
        else m_BMP.SelectedLines.insert(m_BMP.SelectedLines.begin() + AIdx, LNewLine);

        UpdateUIBuff();
    }
}

void CYCBMPDisplayer::SetSelectedLine(int AIdx, const CYCLine &ALine)
{
    CYCLine LNewLine = ALine;

    if (AIdx == SelectedLinesCount())
        AppendSelectedLine(ALine);
    else if ((AIdx < 0) || (AIdx > SelectedLinesCount()))
        YCThrowOutOfRangeException(0, SelectedLinesCount(), AIdx);
    else m_BMP.SelectedLines[AIdx] = LNewLine;

    UpdateUIBuff();
}

double CYCBMPDisplayer::LineLengthAt(int AIdx)
{
    CYCLine     &LLine = m_BMP.SelectedLines[AIdx];

    return YCHypotenuseLength(LLine.DeltaX() * m_BMP.PixelRealWidthuM, LLine.DeltaY() * m_BMP.PixelRealHeightuM);
}

void CYCBMPDisplayer::ClearSelectedLines()
{
    m_BMP.SelectedLines.clear();

    UpdateUIBuff(utAllSelectedLines);

    DoOnClearSelectedLines();
}

bool CYCBMPDisplayer::SaveDisplayerImage(LPCSTR AFileName, bool AIsForceDir/* = true*/)
{
    CImage      LImage;
    CRect       LClientRect;
    CDC         LMemDC;
    CBitmap     LMemBmp;
    char        LFilePath[MAX_PATH];

    if (strcpy_s(LFilePath, sizeof(LFilePath), AFileName) == 0)
    {
        PathRemoveFileSpec(LFilePath);
    }
    else LFilePath[0] = 0;

    if ((strlen(LFilePath) != 0) && !PathFileExists(LFilePath))
    {
        if (AIsForceDir)
            CreateDirectory(LFilePath, NULL);
        else return false;
    }

    this->GetClientRect(&LClientRect);
    LMemDC.CreateCompatibleDC(&m_UIBuff.DC);
    LMemBmp.CreateCompatibleBitmap(&m_UIBuff.DC, LClientRect.Width(), LClientRect.Height());
    CBitmap *LOldMemBmp = LMemDC.SelectObject(&LMemBmp);

    LMemDC.BitBlt(0, 0, LClientRect.Width(), LClientRect.Height(), &m_UIBuff.DC, 0, 0, SRCPAINT);
    LImage.Attach(LMemBmp);
    LImage.Save(AFileName);
    LMemDC.SelectObject(LOldMemBmp);

    return true;
}

bool CYCBMPDisplayer::SaveImage(LPCSTR AFileName, bool AIsForceDir/* = true*/)
{
    char        LFilePath[MAX_PATH];

    if (strcpy_s(LFilePath, sizeof(LFilePath), AFileName) == 0)
    {
        PathRemoveFileSpec(LFilePath);
    }
    else LFilePath[0] = 0;

    if ((strlen(LFilePath) != 0) && !PathFileExists(LFilePath))
    {
        if (AIsForceDir)
            CreateDirectory(LFilePath, NULL);
        else return false;
    }

    YCSaveBMPToFileRawBW8(AFileName, m_BMP.DataBMP, m_BMP.RawWidth(), m_BMP.RawHeight());

    return true;
}

long CYCBMPDisplayer::BMPToClient(const long ABMPLength) const
{
    return YCRoundL(ABMPLength * m_ZoomRate);
}

POINT CYCBMPDisplayer::BMPToClient(const POINT &ABMPPoint) const
{
    POINT LRslt =
    {
        YCRoundI((m_UIBuff.DrawArea.left + YCRoundI((ABMPPoint.x - m_BMP.VisibleArea.left) * m_ZoomRate))),
        YCRoundI((m_UIBuff.DrawArea.top  + YCRoundI((ABMPPoint.y - m_BMP.VisibleArea.top)  * m_ZoomRate)))
    };

    return LRslt;
}

SIZE CYCBMPDisplayer::BMPToClient(const SIZE &ABMPSize) const
{
    SIZE    LRslt;

    LRslt.cx = BMPToClient(ABMPSize.cx);
    LRslt.cy = BMPToClient(ABMPSize.cy);

    return LRslt;
}

RECT CYCBMPDisplayer::BMPToClient(const RECT &ABMPRect) const
{
    union
    {
        RECT    LRslt;
        POINT   LPnts[2];
    };

    LPnts[0] = BMPToClient(*(POINT *)((void *)&ABMPRect));
    LPnts[1] = BMPToClient(*((POINT *)((void *)&ABMPRect) + 1));

    return LRslt;
}

long CYCBMPDisplayer::ClientToBMP(const long AClientLength) const
{
    ASSERT(m_ZoomRate != 0);

    return YCRoundL(AClientLength / m_ZoomRate);
}

POINT CYCBMPDisplayer::ClientToBMP(const POINT &AClientPoint) const
{
    ASSERT(m_ZoomRate != 0);

    POINT LRslt =
    {
        YCRoundI((m_BMP.VisibleArea.left + (AClientPoint.x - m_UIBuff.DrawArea.left) / m_ZoomRate)),
        YCRoundI((m_BMP.VisibleArea.top + (AClientPoint.y - m_UIBuff.DrawArea.top) / m_ZoomRate))
    };

    return LRslt;
}

SIZE CYCBMPDisplayer::ClientToBMP(const SIZE &AClientSize) const
{
    SIZE    LRslt;

    LRslt.cx = ClientToBMP(AClientSize.cx);
    LRslt.cy = ClientToBMP(AClientSize.cy);

    return LRslt;
}

RECT CYCBMPDisplayer::ClientToBMP(const RECT &AClientRect) const
{
    ASSERT(m_ZoomRate != 0);

    union
    {
        RECT    LRslt;
        POINT   LPnts[2];
    };

    LPnts[0] = ClientToBMP(*(POINT *)((void *)&AClientRect));
    LPnts[1] = ClientToBMP(*((POINT *)((void *)&AClientRect) + 1));

    return LRslt;
}

void CYCBMPDisplayer::InitBMPInfoRW8()
{
    ASSERT(m_BMP.Info == NULL);

    if (!m_BMP.Info)
    {
        // BMP head buffer
        m_BMP.Info = (BITMAPINFO*)new char[(sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD))];

        //Get Size of Bmp DataBMP 
        m_BMP.Info->bmiHeader.biSize                = sizeof(BITMAPINFOHEADER);
        m_BMP.Info->bmiHeader.biWidth               = 0;
        m_BMP.Info->bmiHeader.biHeight              = 0;
        m_BMP.Info->bmiHeader.biPlanes              = 1;
        m_BMP.Info->bmiHeader.biBitCount            = 8;
        m_BMP.Info->bmiHeader.biCompression         = BI_RGB;
        m_BMP.Info->bmiHeader.biSizeImage           = 0;
        m_BMP.Info->bmiHeader.biXPelsPerMeter       =
            m_BMP.Info->bmiHeader.biYPelsPerMeter   = 120;
        m_BMP.Info->bmiHeader.biClrUsed             = 256;
        m_BMP.Info->bmiHeader.biClrImportant        = 256;

        for (WORD I = 0; I < 256; I ++)
        {
            m_BMP.Info->bmiColors[I].rgbRed      = (BYTE)I;
            m_BMP.Info->bmiColors[I].rgbGreen    = (BYTE)I;
            m_BMP.Info->bmiColors[I].rgbBlue     = (BYTE)I;
            m_BMP.Info->bmiColors[I].rgbReserved = 0;
        }
    }
}

void CYCBMPDisplayer::UpdateUIBuff(enmUpdateTypes AUpdateType/* = utAll*/)
{
    if (!IsInUpdating() && (HDC)m_UIBuff.DC)
    {
        CRect   LDestArea(m_UIBuff.DrawArea);
        CRect   LSrcArea(m_BMP.VisibleArea);
        CRect   LInvalidArea(0, 0, 0, 0);

        m_UIBuff.DC.SetStretchBltMode(HALFTONE);
        m_UIBuff.DC.SetTextColor(RGB(255, 0, 0));
        m_UIBuff.DC.SetBkMode(TRANSPARENT);


        if (m_BMP.DataBMP == NULL || !m_BMP.DataValid)
        { 
            CBrush Brush(HS_DIAGCROSS, clGreen);

            m_UIBuff.DC.SelectObject(&Brush);
            m_UIBuff.DC.Rectangle(&LDestArea);
        }
        else
        {
            CPen    *LOldPen = NULL;
            CPen    LRedPen(PS_SOLID, 1, RGB(255, 0, 0));
            CBrush  *LOldBrush = NULL;

            m_UIBuff.DC.SetStretchBltMode(HALFTONE);
            m_UIBuff.DC.SetTextColor(RGB(255, 0, 0));
            m_UIBuff.DC.SetBkMode(TRANSPARENT);

            if (IsIncluded(AUpdateType, utReticle))
            {
                // 清除背景
                LOldPen   = static_cast<CPen *>(m_UIBuff.DC.SelectStockObject(NULL_PEN));
                LOldBrush = static_cast<CBrush *>(m_UIBuff.DC.SelectStockObject(WHITE_BRUSH));

                m_UIBuff.DC.Rectangle(-1, -1, m_UIBuff.ClientWidth() + 1, m_UIBuff.ClientHeight() + 1);

                m_UIBuff.DC.SelectObject(LOldPen);
                m_UIBuff.DC.SelectObject(LOldBrush);

                LInvalidArea |= CRect(0, 0, m_UIBuff.ClientWidth(), m_UIBuff.ClientHeight());
            }

            ////////////////////////////////
            // 畫出影像(上下反轉)
            //
            DrawDibDraw(
                m_UIBuff.DibHandle,
                m_UIBuff.DC,
                m_UIBuff.DrawArea.left,     // x-coordinate of upper-left corner of dest. rect. 
                m_UIBuff.DrawArea.top,      // y-coordinate of upper-left corner of dest. rect. 
                m_UIBuff.DrawArea.Width(),  // width of destination rectangle 
                m_UIBuff.DrawArea.Height(), // height of destination rectangle 
                &m_BMP.Info->bmiHeader ,    // address of structure with bitmap info. 
                m_BMP.DataBMP,
                m_BMP.VisibleArea.left,
                m_BMP.VisibleArea.top,
                m_BMP.VisibleArea.Width(),  // source rectangle width
                m_BMP.VisibleArea.Height(), // source rectangle height 
                DDF_HALFTONE);

            LInvalidArea |= m_UIBuff.DrawArea;
            //
            // 畫出影像
            ////////////////////////////////

#ifdef _DEBUG
            {
                char    LStr[16];

                sprintf_s(LStr, sizeof(LStr), "% 10d", m_ShowBMPCount);
                m_UIBuff.DC.TextOutA(10, m_UIBuff.ClientHeight() - 20, LStr, static_cast<int>(strlen(LStr)));
            }
#endif            
            //////////////////////////////////////////////////
            // 限制影像輸出於m_UIBuff.DrawArea區域
            //
            {
                CRgn    LDrawAreaRgn;

                LDrawAreaRgn.CreateRectRgn(
                    m_UIBuff.DrawArea.left,
                    m_UIBuff.DrawArea.top,
                    m_UIBuff.DrawArea.right,
                    m_UIBuff.DrawArea.bottom);

                m_UIBuff.DC.SelectClipRgn(&LDrawAreaRgn);
            }
            //
            // 限制影像輸出於m_UIBuff.DrawArea區域
            //////////////////////////////////////////////////            

            //////////////////////////////////////////////////            
            // 畫出被選取區域的框線
            //
            LOldPen   = static_cast<CPen *>(m_UIBuff.DC.SelectObject(&LRedPen));
            LOldBrush = static_cast<CBrush *>(m_UIBuff.DC.SelectStockObject(NULL_BRUSH));

            for (int I = 0; I < SelectedAreasCount(); I ++)
            {
                CRect LSelectedArea = m_BMP.SelectedAreas[I];

                LSelectedArea.NormalizeRect();

                if (!LSelectedArea.IsRectEmpty() && !(LSelectedArea & m_BMP.VisibleArea).IsRectEmpty())
                {
                    CString LStr;

                    LSrcArea = BMPToClient(LSelectedArea);

                    m_UIBuff.DC.SelectStockObject(NULL_BRUSH);
                    m_UIBuff.DC.Rectangle(&LSrcArea);
                    LInvalidArea |= LSrcArea;

                    ///////////////////////////////////////////
                    // 畫出resize標塊於4個角落
                    //
                    {
                        CBrush              LRedBrush(RGB(255, 0, 0));
                        std::vector<CRect>  LResizeAreas;

                        PrepareResizeAreas(&LSrcArea, &LResizeAreas);
                        m_UIBuff.DC.SelectObject(&LRedBrush);

                        for (UINT LResizeAreaIdx = 0; LResizeAreaIdx < LResizeAreas.size(); LResizeAreaIdx ++)
                            m_UIBuff.DC.Rectangle(&LResizeAreas[LResizeAreaIdx]);
                    }
                    //
                    // 畫出resize標塊於4個角落
                    ///////////////////////////////////////////

                    ///////////////////////////////////////////
                    // 畫出十字線
                    //
                    if (IsIncluded(m_Options, opSelectedAreaReticleVisible))
                    {
                        m_UIBuff.DC.MoveTo(LSrcArea.CenterPoint().x, LSrcArea.top);
                        m_UIBuff.DC.LineTo(LSrcArea.CenterPoint().x, LSrcArea.bottom);
                        m_UIBuff.DC.MoveTo(LSrcArea.left , LSrcArea.CenterPoint().y);
                        m_UIBuff.DC.LineTo(LSrcArea.right, LSrcArea.CenterPoint().y);
                    }
                    //
                    // 畫出十字線
                    ///////////////////////////////////////////

                    ///////////////////////////////////////////
                    // 畫出編號
                    //
                    LSrcArea &= m_UIBuff.DrawArea;

                    LStr.Format("%d", I);
                    m_UIBuff.DC.TextOut(LSrcArea.left + 10, LSrcArea.top + 10, LStr);
                    //
                    // 畫出編號
                    ///////////////////////////////////////////
                }
            }
            //
            // 畫出被選取區域的框線
            //////////////////////////////////////////////////            

            //////////////////////////////////////////////////            
            // 畫出距離量測線
            //
            for (int I = 0; I < SelectedLinesCount(); I ++)
            {
                CYCLine LSelectedLine = m_BMP.SelectedLines[I];

                if (!LSelectedLine.IsLineEmpty() &&
                    (m_BMP.VisibleArea.PtInRect(LSelectedLine.Point1) || m_BMP.VisibleArea.PtInRect(LSelectedLine.Point2)))
                {
                    CString LStr;
                    POINT   LPnt1, LPnt2;

                    LPnt1 = BMPToClient(LSelectedLine.Point1);
                    LPnt2 = BMPToClient(LSelectedLine.Point2);

                    m_UIBuff.DC.MoveTo(LPnt1);
                    m_UIBuff.DC.LineTo(LPnt2);
                    LSrcArea.SetRect(LPnt1.x, LPnt1.y, LPnt2.x, LPnt2.y);
                    LSrcArea.NormalizeRect();
                    LInvalidArea |= LSrcArea;


                    ///////////////////////////////////////////
                    // 畫出編號
                    //
                    /*LSrcArea &= m_UIBuff.DrawArea;

                    LStr.Format("%d", I);
                    m_UIBuff.DC.TextOut(LSrcArea.left + 10, LSrcArea.top + 10, LStr);*/
                    //
                    // 畫出編號
                    ///////////////////////////////////////////
                }
            }
            //
            // 畫出距離量測線
            //////////////////////////////////////////////////            


            //////////////////////////////////////////////////            
            // 畫出Feature
            //
            for (int I = 0; I < static_cast<int>(m_PrivateFeatures.size()); I ++)
            {
                m_PrivateFeatures[I]->Draw(&m_UIBuff.DC);
            }

            for (int I = 0; I < static_cast<int>(m_Features.size()); I ++)
            {
                m_Features[I]->Draw(&m_UIBuff.DC);
            }
            //
            // 畫出Feature
            //////////////////////////////////////////////////            

#if 0
            //////////////////////////////////////////////////            
            // 畫出標線
            //
            if (IsIncluded(m_Options, opReticleVisible))
            {
                LDestArea = m_UIBuff.DrawArea;

                m_UIBuff.DC.MoveTo(LDestArea.left + LDestArea.Width() / 2, LDestArea.top);
                m_UIBuff.DC.LineTo(LDestArea.left + LDestArea.Width() / 2, LDestArea.bottom);

                m_UIBuff.DC.MoveTo(LDestArea.left , LDestArea.top + LDestArea.Height() / 2);
                m_UIBuff.DC.LineTo(LDestArea.right, LDestArea.top + LDestArea.Height() / 2);
            }
            //
            // 畫出標線
            //////////////////////////////////////////////////            
#endif

            m_UIBuff.DC.SelectObject(LOldPen);
            m_UIBuff.DC.SelectObject(LOldBrush);
            m_UIBuff.DC.SelectClipRgn(NULL);
        }

        m_IsUIBuffChanged = false;

        if (m_EventSinker)
            m_EventSinker->OnCustomDraw(this, &m_UIBuff.DC);

        PaintToClient(&LInvalidArea);
    }
    else
    {
        m_IsUIBuffChanged = true;
    }
}

void CYCBMPDisplayer::SyncUIBuff()
{
    ASSERT(m_hWnd);

    if (m_hWnd)
    {
        CClientDC   LDC(this);
        CRect       LRect;

        if (m_UIBuff.DC.m_hDC)
            m_UIBuff.DC.SelectObject((CBitmap *)NULL);
        else m_UIBuff.DC.CreateCompatibleDC(&LDC);

        if (m_UIBuff.Bitmap.m_hObject)
            m_UIBuff.Bitmap.DeleteObject();

        GetClientRect(&LRect);

        m_UIBuff.Bitmap.CreateCompatibleBitmap(&LDC, LRect.Width(), LRect.Height());
        m_UIBuff.DC.SelectObject(&m_UIBuff.Bitmap);

        YCAdjRectToInsideAnother(m_UIBuff.DrawArea, LRect, false);
        AdjAreaByZoomRate();
    }
}

void CYCBMPDisplayer::AdjAreaByZoomRate()
{
    if (m_BMP.Info && m_hWnd)
    {   
        double LCriticalZoomRateMax = max(m_UIBuff.ClientWidth()  * 1.0 / m_BMP.RawWidth(),
            /**/                          m_UIBuff.ClientHeight() * 1.0 / m_BMP.RawHeight());
        double LCriticalZoomRateMin = min(m_UIBuff.ClientWidth()  * 1.0 / m_BMP.RawWidth(),
            /**/                          m_UIBuff.ClientHeight() * 1.0 / m_BMP.RawHeight());

        if (m_ZoomRate < LCriticalZoomRateMin)
        {
            //  在這情況下(即長和寬經過縮放後仍在clientrect的範圍內)，整張bmp圖被縮到小於等於顯示的clientrect，
            //  故調整顯示區(即m_UIBuff.DrawArea)的長寬比和BMP的長寬比一樣           
            m_BMP.VisibleArea.SetRect(0, 0, m_BMP.RawWidth(), m_BMP.RawHeight());

            m_UIBuff.DrawArea.left   = m_UIBuff.ClientWidth() / 2 - static_cast<int>((BMPToClient(m_BMP.RawWidth()) / 2.0));
            m_UIBuff.DrawArea.top    = m_UIBuff.ClientHeight() / 2 - static_cast<int>((BMPToClient(m_BMP.RawHeight()) / 2.0));
            m_UIBuff.DrawArea.right  = m_UIBuff.DrawArea.left + BMPToClient(m_BMP.RawWidth());
            m_UIBuff.DrawArea.bottom = m_UIBuff.DrawArea.top + BMPToClient(m_BMP.RawHeight());
        }
        else if (m_ZoomRate < LCriticalZoomRateMax)
        {
            // 這個情況下(即長 "或" 寬經過縮放後仍在clientrect的範圍內)，需要調整顯示的區域(即m_UIBuff.DrawArea);

            if (ClientToBMP(m_UIBuff.ClientWidth()) > m_BMP.RawWidth())
            {
                // 較高型
                m_UIBuff.DrawArea.left   = m_UIBuff.ClientWidth() / 2 - BMPToClient(m_BMP.RawWidth()) / 2;
                m_UIBuff.DrawArea.top    = 0;
                m_UIBuff.DrawArea.right  = m_UIBuff.DrawArea.left + BMPToClient(m_BMP.RawWidth());
                m_UIBuff.DrawArea.bottom = m_UIBuff.ClientHeight();
            }
            else if (ClientToBMP(m_UIBuff.ClientHeight()) > m_BMP.RawHeight())
            {
                // 較寬型
                m_UIBuff.DrawArea.left   = 0;
                m_UIBuff.DrawArea.top    = m_UIBuff.ClientHeight() / 2 - BMPToClient(m_BMP.RawHeight()) / 2;
                m_UIBuff.DrawArea.right  = m_UIBuff.ClientWidth();
                m_UIBuff.DrawArea.bottom = m_UIBuff.DrawArea.top + BMPToClient(m_BMP.RawHeight());
            }

            CPoint LBMPVisibleAreaCenterPoint = m_BMP.VisibleArea.CenterPoint();

            m_BMP.VisibleArea.left   = LBMPVisibleAreaCenterPoint.x - ClientToBMP(m_UIBuff.ClientWidth()) / 2;
            m_BMP.VisibleArea.top    = LBMPVisibleAreaCenterPoint.y - ClientToBMP(m_UIBuff.ClientHeight()) / 2;
            m_BMP.VisibleArea.right  = m_BMP.VisibleArea.left + ClientToBMP(m_UIBuff.ClientWidth());
            m_BMP.VisibleArea.bottom = m_BMP.VisibleArea.top + ClientToBMP(m_UIBuff.ClientHeight());
        }
        else
        {
            // 在這情況下(即clientrect經zoomrate轉換後仍在bmp rect的範圍內)
            m_UIBuff.DrawArea.SetRect(0, 0, m_UIBuff.ClientWidth(), m_UIBuff.ClientHeight());

            CPoint   LPoint = m_BMP.VisibleArea.CenterPoint();

            m_BMP.VisibleArea.left   = LPoint.x - ClientToBMP(m_UIBuff.ClientWidth()) / 2;
            m_BMP.VisibleArea.top    = LPoint.y - ClientToBMP(m_UIBuff.ClientHeight()) / 2;
            m_BMP.VisibleArea.right  = m_BMP.VisibleArea.left + ClientToBMP(m_UIBuff.ClientWidth());
            m_BMP.VisibleArea.bottom = m_BMP.VisibleArea.top + ClientToBMP(m_UIBuff.ClientHeight());
        }

        YCAdjRectToInsideAnother(m_UIBuff.DrawArea, CRect(0, 0, m_UIBuff.ClientWidth(), m_UIBuff.ClientHeight()), false);
        YCAdjRectToInsideAnother(m_BMP.VisibleArea, CRect(0, 0, m_BMP.RawWidth(), m_BMP.RawHeight()), false);

        TRACE("Client Left : %d, Top : %d, Right : %d, Bottom : %d\n", 0, 0, m_UIBuff.ClientWidth(), m_UIBuff.ClientHeight());
        TRACE("Client Draw Left : %d, Top : %d, Right : %d, Bottom : %d\n", m_UIBuff.DrawArea.left, m_UIBuff.DrawArea.top, m_UIBuff.DrawArea.right, m_UIBuff.DrawArea.bottom);
        TRACE("BMP Left : %d, Top : %d, Right : %d, Bottom : %d\n", 0, 0, m_BMP.RawWidth(), m_BMP.RawHeight());
        TRACE("BMP Visiable Left : %d, Top : %d, Right : %d, Bottom : %d\n", m_BMP.VisibleArea.left, m_BMP.VisibleArea.top, m_BMP.VisibleArea.right, m_BMP.VisibleArea.bottom);
        TRACE("ZoomRate : %.3f\n", m_ZoomRate);

        ASSERT(m_BMP.VisibleArea.Width() <= m_BMP.RawWidth() && m_BMP.VisibleArea.Height() <= m_BMP.RawHeight());
        UpdateUIBuff();
    }
}

void CYCBMPDisplayer::OnDestroy()
{
    __super::OnDestroy();

    ClipCursor(NULL);

    // TODO: Add your message handler code here
    m_UIBuff.DC.DeleteDC();
    m_UIBuff.Bitmap.DeleteObject();
    m_UIBuff.DrawArea.SetRectEmpty();

    DrawDibClose(m_UIBuff.DibHandle);
    m_UIBuff.DibHandle = NULL;
}

void CYCBMPDisplayer::OnSize(UINT nType, int cx, int cy)
{
    __super::OnSize(nType, cx, cy);

    // TODO: Add your message handler code here
    SyncUIBuff();
}

void CYCBMPDisplayer::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    if (m_BMP.Info && m_UIBuff.DrawArea.PtInRect(point))
    {
        CPoint  LBMPPoint = ClientToBMP(point);

        if (m_ActiveMouseAction == maNone)
        {
            switch (m_ActiveUserOperation)
            {
            case uoMoveBMPVisibleArea   :   
                {
                    m_ActiveMouseAction = maMoveBMPVisibleArea;

                    m_MovingBMPVisibleAreaParams.LBtnDownPos = point;
                    m_MovingBMPVisibleAreaParams.BMPVisibleArea = m_BMP.VisibleArea;
                }
                break;

            case uoSelectArea :
                {
                    ///////////////////////////////////////
                    // 開始框選
                    //
                    m_ActiveMouseAction = maSelectArea;

                    if (((m_Options & opAreaSelectable) == opAreaSelectable) &&
                        (((INT64)m_BMP.SelectedAreas.size() < m_MaxSelectedAreasCount) || (m_MaxSelectedAreasCount == 1)))
                    {
                        // 如果只能選取一個框框，則把舊的選取框覆蓋掉
                        if (m_MaxSelectedAreasCount == 1)
                            m_BMP.SelectedAreas.clear();

                        if ((INT64)m_BMP.SelectedAreas.size() < m_MaxSelectedAreasCount)
                        {
                            m_BMP.SelectedAreas.push_back(CRect(LBMPPoint, LBMPPoint));
                            m_BMP.OperatingSelectedAreaIdx = static_cast<int>(m_BMP.SelectedAreas.size()) - 1;
                        }
                    }
                    else m_ActiveMouseAction = maNone;
                    //
                    // 開始框選
                    ///////////////////////////////////////
                }
                break;

            case uoSelectLine :
                {
                    //                    可以選取線條                      且           目前選取的線條數量小於限定值
                    if (IsIncluded(m_Options, opLineSelectable) &&
                        (((INT64)m_BMP.SelectedLines.size() < m_MaxSelectedLinesCount) || (m_MaxSelectedLinesCount == 1)))
                    {                   
                        CYCLine LLine;

                        LLine.SetPoint1(LBMPPoint);
                        LLine.SetPoint2(LBMPPoint);

                        // 如果只能選取一條線，則新的線會把舊的線覆蓋過去
                        if (m_MaxSelectedLinesCount == 1)
                            m_BMP.SelectedLines.clear();

                        if ((INT64)m_BMP.SelectedLines.size() < m_MaxSelectedLinesCount)
                        {
                            m_BMP.SelectedLines.push_back(LLine);
                            m_ActiveMouseAction = maSelectLine;
                        }
                    }
                    else
                    {
                        m_ActiveMouseAction = maNone;
                    }
                }
                break;

            default : 
                {
                    m_ActiveMouseAction = maNone;

                    // 檢查是否點選在之前選取的框框內
                    for (int I = 0; I < SelectedAreasCount(); I ++)
                    {
                        CRect   &LSelectedArea = m_BMP.SelectedAreas[I];

                        std::vector<CRect>  LResizeAreas;
                        CRect               LUISelectedArea;

                        LUISelectedArea = BMPToClient(LSelectedArea);
                        PrepareResizeAreas(&LUISelectedArea, &LResizeAreas);

                        int LResizeAreaIdx = 0;

                        for (LResizeAreaIdx = 0; LResizeAreaIdx < static_cast<int>(min(LResizeAreas.size(), 8)); LResizeAreaIdx ++)
                        {
                            if (LResizeAreas[LResizeAreaIdx].PtInRect(point))
                            {
                                const enmMouseAction  LMAs[8] =
                                {
                                    maResizeLT, maResizeT, maResizeRT,
                                    maResizeL ,            maResizeR,
                                    maResizeLB, maResizeB, maResizeRB 
                                };

                                m_ActiveMouseAction = LMAs[LResizeAreaIdx];                            
                                m_BMP.OperatingSelectedAreaIdx = I;

                                break;
                            }
                        } 

                        if (m_ActiveMouseAction == maNone && LSelectedArea.PtInRect(LBMPPoint))
                        {
                            ///////////////////////////////////////
                            // 點在框內，但不在上述的角落上
                            ///////////////////////////////////////
                            m_ActiveMouseAction = maMoveSelectedArea;

                            LBMPPoint = BMPToClient(LSelectedArea.CenterPoint());
                            ClientToScreen(&LBMPPoint);
                            SetCursorPos(LBMPPoint.x, LBMPPoint.y);

                            m_BMP.OperatingSelectedAreaIdx = I;
                        } // if (LSelectedArea.PtInRect(LBMPPoint))
                    } // for (int I = 0; I < SelectedAreasCount(); I ++)

                    if (m_ActiveMouseAction == maNone)
                    {                
                        m_MovingBMPVisibleAreaParams.LBtnDownPos.SetPoint(0, 0);
                        m_MovingBMPVisibleAreaParams.BMPVisibleArea.SetRectEmpty();
                    }
                }
            } 

            if (m_ActiveMouseAction != maNone)
            {
                RECT LCursorClipRect(m_UIBuff.DrawArea);

                ClientToScreen(&LCursorClipRect);
                ClipCursor(&LCursorClipRect);
            }
        } // if (m_ActiveMouseAction == maNone)
    }

    __super::OnLButtonDown(nFlags, point);
}

void CYCBMPDisplayer::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    const CPoint    LBMPPoint   = ClientToBMP(point);

    BeginUpdate();
    m_MousePointTextFeature.SetPoint(LBMPPoint);

    if (m_ActiveMouseAction != maNone)
    {
        enmUpdateType   LUpdateType = utAllSelectedAreas;

        switch (m_ActiveMouseAction)
        {
        case maSelectLine :
            {
                CYCLine &LLine = m_BMP.SelectedLines.back();

                LLine.SetPoint2(LBMPPoint);

                switch (m_Options & (opSelectHLine | opSelectVLine))
                {
                case opSelectVLine : LLine.Point2.x = LLine.Point1.x; break;
                case opSelectHLine : LLine.Point2.y = LLine.Point1.y; break;
                }
            }
            break;

        case maSelectArea       :
        case maResizeRB         :
        case maResizeLT         :
        case maResizeLB         :
        case maResizeRT         :
        case maResizeR          :
        case maResizeL          :
        case maResizeB          :
        case maResizeT          :
        case maMoveSelectedArea :
            {
                CRect   &LSelectedArea = m_BMP.SelectedAreas[m_BMP.OperatingSelectedAreaIdx];

                switch (m_ActiveMouseAction)
                {
                case maSelectArea :
                case maResizeRB   :
                    {
                        LSelectedArea.right  = LBMPPoint.x;
                        LSelectedArea.bottom = LBMPPoint.y;
                    }
                    break;

                case maResizeLT :
                    {
                        LSelectedArea.left = LBMPPoint.x;
                        LSelectedArea.top  = LBMPPoint.y;
                    }
                    break;

                case maResizeLB :
                    {
                        LSelectedArea.left   = LBMPPoint.x;
                        LSelectedArea.bottom = LBMPPoint.y;
                    }
                    break;

                case maResizeRT :
                    {
                        LSelectedArea.right = LBMPPoint.x;
                        LSelectedArea.top   = LBMPPoint.y;
                    }
                    break;

                case maResizeL :
                    {
                        LSelectedArea.left = LBMPPoint.x;
                    }
                    break;

                case maResizeT :
                    {
                        LSelectedArea.top = LBMPPoint.y;
                    }
                    break;

                case maResizeR :
                    {
                        LSelectedArea.right = LBMPPoint.x;
                    }
                    break;

                case maResizeB :
                    {
                        LSelectedArea.bottom = LBMPPoint.y;
                    }
                    break;

                case maMoveSelectedArea :
                    {
                        LSelectedArea.OffsetRect(LBMPPoint.x - LSelectedArea.CenterPoint().x, LBMPPoint.y - LSelectedArea.CenterPoint().y);
                    }
                    break;
                }       

                DoOnSelectedAreaSizing(m_BMP.OperatingSelectedAreaIdx);
            }
            break;

        case maMoveBMPVisibleArea :
            {
                CSize LPointDiff = ClientToBMP(point - m_MovingBMPVisibleAreaParams.LBtnDownPos);

                m_BMP.VisibleArea = m_MovingBMPVisibleAreaParams.BMPVisibleArea - LPointDiff;
                YCAdjRectToInsideAnother(m_BMP.VisibleArea, CRect(0, 0, m_BMP.RawWidth(), m_BMP.RawHeight()), false);
                LUpdateType = utAll;
            }
            break;
        }

        UpdateUIBuff(LUpdateType);
    }

    EndUpdate();

    if (m_EventSinker)
        m_EventSinker->OnMouseMove(this, point);

    __super::OnMouseMove(nFlags, point);
}

void CYCBMPDisplayer::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    //SetCursor(LoadCursor(NULL, IDC_ARROW));
    ClipCursor(NULL);
    enum enmUpdateType LUT = utAllSelectedAreas;

    switch (m_ActiveMouseAction)
    {
    case maSelectArea :
    case maResizeLT   :
    case maResizeRT   :
    case maResizeLB   :
    case maResizeRB   : 
    case maResizeL    :
    case maResizeT    :
    case maResizeR    :
    case maResizeB    :
        {
            CRect   &LSelectedArea = m_BMP.SelectedAreas[m_BMP.OperatingSelectedAreaIdx];

            YCAdjRectToInsideAnother(LSelectedArea, CRect(0, 0, m_BMP.RawWidth(), m_BMP.RawHeight()), true);

            if (m_ActiveMouseAction == maSelectArea)
            {
                if (LSelectedArea.IsRectEmpty())
                    m_BMP.SelectedAreas.pop_back();
                else DoOnSelectArea();
            }
            else DoOnSelectedAreaSized(m_BMP.OperatingSelectedAreaIdx);

            m_BMP.OperatingSelectedAreaIdx = -1;
        }
        break;

    case maMoveSelectedArea :
        {
            CRect   &LSelectedArea = m_BMP.SelectedAreas[m_BMP.OperatingSelectedAreaIdx];

            YCAdjRectToInsideAnother(LSelectedArea, CRect(0, 0, m_BMP.RawWidth(), m_BMP.RawHeight()), false);
            m_BMP.OperatingSelectedAreaIdx = -1;

            m_MovingBMPVisibleAreaParams.LBtnDownPos.SetPoint(0, 0);
            m_MovingBMPVisibleAreaParams.BMPVisibleArea.SetRectEmpty();
        }
        break;

    case maSelectLine :
        {
            CYCLine &LLine = m_BMP.SelectedLines.back();

            LLine.SetPoint2(ClientToBMP(point));

            switch (m_Options & (opSelectHLine | opSelectVLine))
            {
            case opSelectVLine : LLine.Point2.x = LLine.Point1.x; break;
            case opSelectHLine : LLine.Point2.y = LLine.Point1.y; break;
            }

            if (LLine.IsLineEmpty())
                m_BMP.SelectedLines.pop_back();
            else DoOnSelectLine();
        }
        break;
    }   

    if (m_ActiveMouseAction != maNone)
    {
        m_ActiveMouseAction = maNone;
        UpdateUIBuff(LUT);
    }

    __super::OnLButtonUp(nFlags, point);
}

void CYCBMPDisplayer::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default   
    if (IsBMPVisibleAreaMovable())
    {
        CPoint  LBMPPoint(ClientToBMP(point));

        MoveBMPVisibleAreaCenterTo(LBMPPoint);
    }

    __super::OnLButtonDblClk(nFlags, point);
}

void CYCBMPDisplayer::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    __super::OnRButtonDown(nFlags, point);
}

void CYCBMPDisplayer::OnRButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    __super::OnRButtonUp(nFlags, point);
}

BOOL CYCBMPDisplayer::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    // TODO: Add your message handler code here and/or call default
    if ((m_Options & opZoomable) == opZoomable)
    {
        if (zDelta > 0)
        {
            SetZoomRate(m_ZoomRate + m_ZoomRateStep);
        }
        else if (zDelta < 0)
        {
            if (m_ZoomRate > 0.2)
                SetZoomRate(m_ZoomRate - m_ZoomRateStep);
        }
    }

    return __super::OnMouseWheel(nFlags, zDelta, pt);
}

void CYCBMPDisplayer::OnContextMenu(CWnd* pWnd, CPoint point)
{
    // TODO: Add your message handler code here
    enum enmMenuItemID
    {
        IDM_mniShowReticle = 6000,
        IDM_mniHideReticle,
        IDM_mniShowSelectedAreaReticle,
        IDM_mniHideSelectedAreaReticle,
        IDM_mniShowMousePoint,
        /**/IDM_mniHideMousePoint,
        /**/IDM_mniShowMousePointLT,
        /**/IDM_mniShowMousePointT,
        /**/IDM_mniShowMousePointRT,
        /**/IDM_mniShowMousePointLB,
        /**/IDM_mniShowMousePointB,
        /**/IDM_mniShowMousePointRB,
        //---------------------
        IDM_mniAction,
        /**/IDM_mniMoveBMPVisibleArea,
        /**///---------------------
        /**/IDM_mniSelectArea,
        /**///---------------------
        /**/IDM_mniSelectLine,
        /**/IDM_mniSelectVLine,
        /**/IDM_mniSelectHLine,
        /**///---------------------
        /**/IDM_mniClearSelectedAreas,
        /**/IDM_mniClearSelectedLines,
        //----------------------
        IDM_mniZoomIn,
        IDM_mniZoomOut,
        IDM_mniZoom,
        /**/IDM_mniZoom0_2X,
        /**/IDM_mniZoom0_4X,
        /**/IDM_mniZoom0_7X,
        /**/IDM_mniZoom1_0X,
        /**/IDM_mniZoom1_5X,
        /**/IDM_mniZoom2_0X,
        /**/IDM_mniZoom4_0X,
        //---------------------
        IDM_mniFitSize,
        //---------------------
        IDM_mniSaveToFile
    };

    if (m_BMP.DataValid)
    {

        CMenu   LMenu, LSubMenu;
        long    LItemID;
        long    LMenuItemFlags = 0;

        LMenu.CreatePopupMenu();

        // 顯示顯示標線功能項
        if (IsIncluded(m_VisibleMenuItems, miShowReticle))
        {
            if (IsReticleVisible())
                LMenu.AppendMenu(MF_STRING, IDM_mniHideReticle, "Hide Reticle");
            else LMenu.AppendMenu(MF_STRING, IDM_mniShowReticle, "Show Reticle");
        }

        // 顯示選取區顯示標線功能項
        if (IsIncluded(m_VisibleMenuItems, miShowSelectedAreaReticle))
        {
            if (IsSelectedAreaReticleVisible())
                LMenu.AppendMenu(MF_STRING, IDM_mniHideSelectedAreaReticle, "Hide Selected Area Reticle");
            else LMenu.AppendMenu(MF_STRING, IDM_mniShowSelectedAreaReticle, "Show Selected Area Reticle");
        }

        // 顯示滑鼠座標
        if (IsIncluded(m_VisibleMenuItems, miShowMousePoint))
        {
            LSubMenu.CreateMenu();

            LSubMenu.AppendMenu(MF_STRING, IDM_mniHideMousePoint, "Hide");
            LSubMenu.AppendMenu(MF_STRING | (m_ShowMousePointOption == smpLeftTop     ? MF_CHECKED : MF_UNCHECKED), IDM_mniShowMousePointLT, "Left Top");
            LSubMenu.AppendMenu(MF_STRING | (m_ShowMousePointOption == smpTop         ? MF_CHECKED : MF_UNCHECKED), IDM_mniShowMousePointT , "Top");
            LSubMenu.AppendMenu(MF_STRING | (m_ShowMousePointOption == smpRightTop    ? MF_CHECKED : MF_UNCHECKED), IDM_mniShowMousePointRT, "Right Top");
            LSubMenu.AppendMenu(MF_STRING | (m_ShowMousePointOption == smpLeftBottom  ? MF_CHECKED : MF_UNCHECKED), IDM_mniShowMousePointLB, "Left Bottom");
            LSubMenu.AppendMenu(MF_STRING | (m_ShowMousePointOption == smpBottom      ? MF_CHECKED : MF_UNCHECKED), IDM_mniShowMousePointB , "Bottom");
            LSubMenu.AppendMenu(MF_STRING | (m_ShowMousePointOption == smpRightBottom ? MF_CHECKED : MF_UNCHECKED), IDM_mniShowMousePointRB, "Right Bottom");


            LMenu.AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)LSubMenu.m_hMenu, "Show Mouse Point");
        }


        if (IsIntersected(m_VisibleMenuItems, (miMoveBMPVisibleArea | miSelectArea | miSelectLine)))
        {
            LSubMenu.Detach();
            LSubMenu.CreateMenu();

            // 顯示移動顯示區域功能項
            if (IsIncluded(m_VisibleMenuItems, miMoveBMPVisibleArea))
            {
                LSubMenu.AppendMenu(MF_STRING | (m_ActiveUserOperation == uoMoveBMPVisibleArea ? MF_CHECKED : MF_UNCHECKED), 
                    IDM_mniMoveBMPVisibleArea, "Move BMP");
            }

            // 顯示選取區載功能項
            if (IsIncluded(m_VisibleMenuItems, miSelectArea))
            {
                if (LSubMenu.GetMenuItemCount() > 0)
                    LSubMenu.AppendMenu(MF_SEPARATOR);

                LSubMenu.AppendMenu(MF_STRING | (m_ActiveUserOperation == uoSelectArea ? MF_CHECKED : MF_UNCHECKED),
                    IDM_mniSelectArea, "Select Area");
            }

            // 顯示選取線功能項
            if (IsIncluded(m_VisibleMenuItems, miSelectLine))
            {
                if (LSubMenu.GetMenuItemCount() > 0)
                    LSubMenu.AppendMenu(MF_SEPARATOR);

                LMenuItemFlags = MF_STRING |
                    (((m_ActiveUserOperation == uoSelectLine) && 
                    ((m_Options & (opSelectVLine | opSelectHLine)) == opNone)) ? MF_CHECKED : MF_UNCHECKED);
                LSubMenu.AppendMenu(LMenuItemFlags, IDM_mniSelectLine, "Select Line");

                LMenuItemFlags = MF_STRING |
                    (((m_ActiveUserOperation == uoSelectLine) &&
                    (m_Options & (opSelectVLine | opSelectHLine)) == opSelectVLine) ? MF_CHECKED : MF_UNCHECKED);
                LSubMenu.AppendMenu(LMenuItemFlags, IDM_mniSelectVLine, "Select Vertical Line");

                LMenuItemFlags = MF_STRING | 
                    (((m_ActiveUserOperation == uoSelectLine) &&
                    (m_Options & (opSelectVLine | opSelectHLine)) == opSelectHLine) ? MF_CHECKED : MF_UNCHECKED);
                LSubMenu.AppendMenu(LMenuItemFlags, IDM_mniSelectHLine, "Select Horizontal Line");
            }

            if (m_BMP.SelectedAreas.size() > 0 || m_BMP.SelectedLines.size() > 0)
            {
                if (LSubMenu.GetMenuItemCount() > 0)
                    LSubMenu.AppendMenu(MF_SEPARATOR);

                if (m_BMP.SelectedAreas.size() > 0)
                    LSubMenu.AppendMenu(MF_STRING, IDM_mniClearSelectedAreas, "Clear Selected Areas");

                if (m_BMP.SelectedLines.size() > 0)
                    LSubMenu.AppendMenu(MF_STRING, IDM_mniClearSelectedLines, "Clear Selected Lines");
            }

            if (LMenu.GetMenuItemCount() > 0)
                LMenu.AppendMenu(MF_SEPARATOR);

            LMenu.AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)LSubMenu.m_hMenu, "Action");
        }

        // 顯示Zoom功能項
        if ((m_VisibleMenuItems & miZoom) == miZoom)
        {
            if (LMenu.GetMenuItemCount() > 0)
                LMenu.AppendMenu(MF_SEPARATOR);

            LMenu.AppendMenu(MF_STRING, IDM_mniZoomIn, "Zoom In");
            LMenu.AppendMenu(MF_STRING, IDM_mniZoomOut, "Zoom Out");

            LSubMenu.Detach();
            LSubMenu.CreateMenu();

            LSubMenu.AppendMenu(MF_STRING, IDM_mniZoom0_2X, "0.2X");
            LSubMenu.AppendMenu(MF_STRING, IDM_mniZoom0_4X, "0.4X");
            LSubMenu.AppendMenu(MF_STRING, IDM_mniZoom0_7X, "0.7X");
            LSubMenu.AppendMenu(MF_STRING, IDM_mniZoom1_0X, "1.0X");
            LSubMenu.AppendMenu(MF_STRING, IDM_mniZoom1_5X, "1.5X");
            LSubMenu.AppendMenu(MF_STRING, IDM_mniZoom2_0X, "2.0X");
            LSubMenu.AppendMenu(MF_STRING, IDM_mniZoom4_0X, "4.0X");
            LSubMenu.AppendMenu(MF_SEPARATOR);
            LSubMenu.AppendMenu(MF_STRING, IDM_mniFitSize, "Fit size");
            LMenu.AppendMenu(MF_POPUP | MF_STRING, (UINT_PTR)LSubMenu.m_hMenu, "Zoom");
        }

        // 顯示儲存檔案
        LMenu.AppendMenu(MF_SEPARATOR);
        LMenu.AppendMenu(MF_STRING, IDM_mniSaveToFile, "Save To File");

        LItemID = LMenu.TrackPopupMenuEx(TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RETURNCMD, point.x, point.y, this, NULL);
        LMenu.DestroyMenu();

        switch (LItemID)
        {
        case IDM_mniShowReticle :
        case IDM_mniHideReticle : SetIsReticleVisible(LItemID == IDM_mniShowReticle);
            break;

        case IDM_mniShowSelectedAreaReticle :
        case IDM_mniHideSelectedAreaReticle : SetIsSelectedAreaReticleVisible(LItemID == IDM_mniShowSelectedAreaReticle);
            break;

        case IDM_mniHideMousePoint :
            SetShowMousePointOption(smpNone);
            break;

        case IDM_mniShowMousePointLT :
            SetShowMousePointOption(smpLeftTop);
            break;

        case IDM_mniShowMousePointT :
            SetShowMousePointOption(smpTop);
            break;

        case IDM_mniShowMousePointRT :
            SetShowMousePointOption(smpRightTop);
            break;

        case IDM_mniShowMousePointLB :
            SetShowMousePointOption(smpLeftBottom);
            break;

        case IDM_mniShowMousePointB :
            SetShowMousePointOption(smpBottom);
            break;

        case IDM_mniShowMousePointRB :
            SetShowMousePointOption(smpRightBottom);
            break;

        case IDM_mniMoveBMPVisibleArea : 
            {
                SetIsBMPVisibleAreaMovable(true);
                SetActiveUserOperation(m_ActiveUserOperation == uoMoveBMPVisibleArea ? uoNone : uoMoveBMPVisibleArea);
            }
            break;

        case IDM_mniSelectArea  : 
            {
                SetIsAreaSelectable(true);
                SetActiveUserOperation(m_ActiveUserOperation == uoSelectArea ? uoNone : uoSelectArea);
            }
            break;

        case IDM_mniSelectLine :
            {
                if ((m_ActiveUserOperation == uoSelectLine) && !(m_Options & (opSelectVLine | opSelectHLine)))
                    SetActiveUserOperation(uoNone);
                else
                {
                    SetOptions((m_Options | opLineSelectable) & ~(opSelectHLine | opSelectVLine));
                    SetActiveUserOperation(uoSelectLine);
                }
            }
            break;

        case IDM_mniSelectVLine :
            {
                if ((m_ActiveUserOperation == uoSelectLine) && (m_Options & opSelectVLine))
                    SetActiveUserOperation(uoNone);
                else
                {
                    SetOptions((m_Options | opLineSelectable) & ~opSelectHLine | opSelectVLine);
                    SetActiveUserOperation(uoSelectLine);
                }
            }
            break;

        case IDM_mniSelectHLine :
            {
                if ((m_ActiveUserOperation == uoSelectLine) && (m_Options & opSelectHLine))
                    SetActiveUserOperation(uoNone);
                else
                {
                    SetOptions((m_Options | opLineSelectable) & ~opSelectVLine | opSelectHLine);
                    SetActiveUserOperation(uoSelectLine);
                }
            }
            break;

        case IDM_mniClearSelectedAreas :
            {
                ClearSelectedAreas();
                UpdateUIBuff(utAllSelectedAreas);
            }    
            break;

        case IDM_mniClearSelectedLines :   
            {
                ClearSelectedLines();
                UpdateUIBuff(utAllSelectedLines);
            }
            break;

        case IDM_mniZoomIn : 
            {
                SetIsZoomable(true);
                SetZoomRate(m_ZoomRate + m_ZoomRateStep);
            }
            break;

        case IDM_mniZoomOut :   
            {
                SetIsZoomable(true);
                if (m_ZoomRate > m_ZoomRateStep)
                    SetZoomRate(m_ZoomRate - m_ZoomRateStep);
            }
            break;

        case IDM_mniZoom0_2X : SetIsZoomable(true); SetZoomRate(0.2); break;
        case IDM_mniZoom0_4X : SetIsZoomable(true); SetZoomRate(0.4); break;
        case IDM_mniZoom0_7X : SetIsZoomable(true); SetZoomRate(0.7); break;
        case IDM_mniZoom1_0X : SetIsZoomable(true); SetZoomRate(1.0); break;
        case IDM_mniZoom1_5X : SetIsZoomable(true); SetZoomRate(1.5); break;
        case IDM_mniZoom2_0X : SetIsZoomable(true); SetZoomRate(2.0); break;
        case IDM_mniZoom4_0X : SetIsZoomable(true); SetZoomRate(4.0); break;
        case IDM_mniFitSize  : SetIsZoomable(true); BMPFitUISize(); break;

        case IDM_mniSaveToFile :
            {
                CFileDialog     LDlg(
                    FALSE,
                    "bmp",
                    "*.bmp",
                    OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
                    "Bitmap File(*.bmp)|*.bmp|All File(*.*)|*.*||",
                    this,
                    NULL);

                if (LDlg.DoModal() == IDOK)
                    YCSaveBMPToFileRawBW8(LDlg.GetPathName(), m_BMP.DataBMP, m_BMP.RawWidth(), m_BMP.RawHeight());
            }
            break;
        }
    }
}

void CYCBMPDisplayer::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    // TODO: Add your message handler code here
    CRect   LClipBox;

    dc.GetClipBox(&LClipBox);
    PaintToClient(&LClipBox);

    // Do not call __super::OnPaint() for painting messages
}

void CYCBMPDisplayer::PaintToClient(CRect *AArea)
{
    if (m_hWnd)
    {
        CClientDC dc(this);

        dc.BitBlt(AArea->left, AArea->top, AArea->Width(), AArea->Height(), &m_UIBuff.DC, AArea->left, AArea->top, SRCCOPY);
    }
}

void CYCBMPDisplayer::DoOnSelectArea()
{
    if (m_EventSinker)
        m_EventSinker->OnSelectArea(this);
}

void CYCBMPDisplayer::DoOnClearSelectedAreas()
{
    if (m_EventSinker)
        m_EventSinker->OnClearSelectedAreas(this);
}

void CYCBMPDisplayer::DoOnSelectedAreaSizing(int AIndex)
{
    if (m_EventSinker)
        m_EventSinker->OnSelectedAreaSizing(this, AIndex);
}

void CYCBMPDisplayer::DoOnSelectedAreaSized(int AIndex)
{
    if (m_EventSinker)
        m_EventSinker->OnSelectedAreaSized(this, AIndex);
}

void CYCBMPDisplayer::DoOnZoom()
{
    if (m_EventSinker)
        m_EventSinker->OnZoom(this);
}

void CYCBMPDisplayer::DoOnSelectLine()
{
    if (m_EventSinker)
        m_EventSinker->OnSelectLine(this);
}

void CYCBMPDisplayer::DoOnClearSelectedLines()
{
    if (m_EventSinker)
        m_EventSinker->OnClearSelectedLines(this);
}

bool CYCBMPDisplayer::PrepareResizeAreas(IN const CRect &ASelectedArea, OUT std::vector<CRect> *AResizeAreas)
{
    ASSERT(AResizeAreas);

    if (AResizeAreas)
    {
        AResizeAreas->push_back(CRect(ASelectedArea.left, ASelectedArea.top, ASelectedArea.left, ASelectedArea.top));
        AResizeAreas->push_back(CRect(ASelectedArea.CenterPoint().x, ASelectedArea.top, ASelectedArea.CenterPoint().x, ASelectedArea.top));
        AResizeAreas->push_back(CRect(ASelectedArea.right, ASelectedArea.top, ASelectedArea.right, ASelectedArea.top));
        AResizeAreas->push_back(CRect(ASelectedArea.left, ASelectedArea.CenterPoint().y, ASelectedArea.left, ASelectedArea.CenterPoint().y));
        AResizeAreas->push_back(CRect(ASelectedArea.right, ASelectedArea.CenterPoint().y, ASelectedArea.right, ASelectedArea.CenterPoint().y));
        AResizeAreas->push_back(CRect(ASelectedArea.left, ASelectedArea.bottom, ASelectedArea.left, ASelectedArea.bottom));
        AResizeAreas->push_back(CRect(ASelectedArea.CenterPoint().x, ASelectedArea.bottom, ASelectedArea.CenterPoint().x, ASelectedArea.bottom));
        AResizeAreas->push_back(CRect(ASelectedArea.right, ASelectedArea.bottom, ASelectedArea.right, ASelectedArea.bottom));

        for (int LResizeAreaIdx = 0; LResizeAreaIdx < 8; LResizeAreaIdx ++)
        {
            ((*AResizeAreas)[LResizeAreaIdx]).InflateRect(3, 3);
        } 

        return true;
    }

    return false;
}

int CYCBMPDisplayer::AddFeature(CYCBMPDisplayerFeature *AFeature)
{
    int I = static_cast<int>(m_Features.IndexOf(AFeature));

    if (I == -1)
    {
        ASSERT(AFeature->m_Displayer == NULL);

        AFeature->m_Displayer = this;
        m_Features.push_back(AFeature);
        I = static_cast<int>(m_Features.size()) - 1;

        UpdateFeature(AFeature);
    }

    return I;
}

bool CYCBMPDisplayer::RemoveFeature(CYCBMPDisplayerFeature *AFeature)
{
    int I = static_cast<int>(m_Features.IndexOf(AFeature));

    if (I != -1)
    {
        ASSERT(AFeature->m_Displayer == this);

        AFeature->m_Displayer = NULL;
        m_Features.erase(m_Features.begin() + I);

        if (AFeature->m_IsOwnedByDisplayer)
            delete AFeature;

        UpdateFeature(NULL);

        return true;
    }

    return  false;
}

void CYCBMPDisplayer::DeleteFeature(int AIdx)
{
    CYCBMPDisplayerFeature *AFeature = FeatureAt(AIdx);

    RemoveFeature(AFeature);
}

void CYCBMPDisplayer::UpdateFeature(CYCBMPDisplayerFeature *AFeature)
{
    UpdateUIBuff();

    // 1.先清空畫布

    // 2.畫上影像

    // 3.畫上Feature

    //if (AFeature)
    //    AFeature->Draw(&m_UIBuff.DC);
}
//
// CYCBMPDisplayer
///////////////////////////////////////////////////



///////////////////////////////////////////////////
// CYCBMPDisplayerFeature
//
IMPLEMENT_DYNAMIC(CYCBMPDisplayerFeature, CObject)


CYCBMPDisplayerFeature::CYCBMPDisplayerFeature()
: CObject()
, m_Displayer(NULL)
, m_IsOwnedByDisplayer(false)
, m_UpdateCount(0)
, m_DisableUpdateCount(0)
, m_IsVisible(true)
, m_LineColor(clRed)
, m_CoorType(ctBMP)
{
}

CYCBMPDisplayerFeature::~CYCBMPDisplayerFeature()
{
    m_IsOwnedByDisplayer = false;
    SetDisplayer(NULL);
}

void CYCBMPDisplayerFeature::SetDisplayer(CYCBMPDisplayer *ADisplayer)
{
    if (m_Displayer != ADisplayer)
    {
        if (m_Displayer)
            m_Displayer->RemoveFeature(this);

        if (ADisplayer)
            ADisplayer->AddFeature(this);
    }
}

void CYCBMPDisplayerFeature::SetIsVisible(bool AValue)
{
    if (m_IsVisible != AValue)
    {
        m_IsVisible = AValue;

        Update();
    }
}

void CYCBMPDisplayerFeature::SetCaption(LPCSTR AValue)
{
    CString LStr = AValue;

    if (m_Caption != LStr)
    {
        m_Caption = LStr;

        Update();
    }
}

void CYCBMPDisplayerFeature::SetLineColor(COLORREF AValue)
{
    if (m_LineColor != AValue)
    {
        m_LineColor = AValue;
        Update();
    }
}

void CYCBMPDisplayerFeature::Update()
{
    if (m_DisableUpdateCount)
        m_UpdateCount ++;
    else
    {
        if (m_Displayer)
            m_Displayer->UpdateFeature(this);

        m_UpdateCount = 0;
    }
}

void CYCBMPDisplayerFeature::EndUpdate()
{
    m_DisableUpdateCount --;

    if (m_DisableUpdateCount == 0)
        Update();
}
//
// CYCBMPDisplayerFeature
///////////////////////////////////////////////////


///////////////////////////////////////////////////
// CYCRetangleFeature
//
IMPLEMENT_SERIAL(CYCRetangleFeature, CYCBMPDisplayerFeature, 0x0001)

CYCRetangleFeature::CYCRetangleFeature()
: CYCBMPDisplayerFeature()
, m_Rect(0, 0, 100, 100)
{
}

CYCRetangleFeature::CYCRetangleFeature(const RECT &AValue)
: CYCBMPDisplayerFeature()
, m_Rect(AValue)
{
}

CYCRetangleFeature::CYCRetangleFeature(int AX, int AY, int AWidth, int AHeight)
: CYCBMPDisplayerFeature()
, m_Rect(AX, AY, AX + AWidth, AY + AHeight)
{
}

void CYCRetangleFeature::SetRect(const RECT &AValue)
{
    if (m_Rect != AValue)
    {
        m_Rect = AValue;

        Update();
    }
}

void CYCRetangleFeature::SetRect(int AX, int AY, int AWidth, int AHeight)
{
    SetRect(CRect(AX, AY, AX + AWidth, AY + AHeight));
}

void CYCRetangleFeature::SetWidth(int AValue)
{
    if (m_Rect.Width() != AValue)
    {
        m_Rect.left = AValue / 2;
        m_Rect.right = m_Rect.left + AValue;

        Update();
    }
}

void CYCRetangleFeature::SetHeight(int AValue)
{
    if (m_Rect.Height() != AValue)
    {
        m_Rect.top = AValue / 2;
        m_Rect.bottom = m_Rect.top + AValue;

        Update();
    }
}

void CYCRetangleFeature::SetCenter(const POINT &AValue)
{
    if (Center() != AValue)
    {
        m_Rect.MoveToXY(AValue);

        Update();
    }
}

void CYCRetangleFeature::OffsetCenter(const POINT &AValue)
{
    if (AValue.x != 0 && AValue.y != 0)
    {
        m_Rect.OffsetRect(AValue);

        Update();
    }
}

IMPLEMENT_CYCBMPDisplayerFeature_Draw(CYCRetangleFeature)
{
    if (m_Displayer && AUIDC && IsVisible())
    {
        CPen    LPen(PS_SOLID, 1, m_LineColor);
        CPen    *LOldPen = (CPen *)AUIDC->SelectObject(&LPen);
        CRect   LRect = m_Rect;
        bool    LFinish = false;

        // 座標轉換
        LRect = m_Displayer->BMPToClient(LRect);

        // 劃線條
        AUIDC->SelectStockObject(NULL_BRUSH);
        AUIDC->Rectangle(LRect);
        AUIDC->SelectObject(LOldPen);

        // 劃標題
        if (m_Caption != "")
        {           
            COLORREF LFntColor = AUIDC->GetTextColor();

            AUIDC->SetTextColor(m_LineColor);
            AUIDC->SetBkMode(TRANSPARENT);
            AUIDC->TextOutA(LRect.left + 5, LRect.top + 5, m_Caption);
            AUIDC->SetTextColor(LFntColor);
        }
    }
}

//
// CYCRetangleFeature
///////////////////////////////////////////////////


///////////////////////////////////////////////////
// CYCCrossFeature
//
IMPLEMENT_SERIAL(CYCCrossFeature, CYCBMPDisplayerFeature, 0x0001)


CYCCrossFeature::CYCCrossFeature()
: CYCBMPDisplayerFeature()
, m_Width(100)
, m_Height(100)
{
    m_Center.x = m_Center.y = 0;
}

void CYCCrossFeature::SetCenter(const POINT &AValue)
{
    SetCenter(AValue.x, AValue.y);
}

void CYCCrossFeature::SetCenter(int AX, int AY)
{
    if (m_Center.x != AX || m_Center.y != AY)
    {
        m_Center.x = AX;
        m_Center.y = AY;

        Update();
    }
}

void CYCCrossFeature::SetWidth(int AValue)
{
    if (m_Width != AValue)
    {
        m_Width = AValue;
        Update();
    }
}

void CYCCrossFeature::SetHeight(int AValue)
{
    if (m_Height != AValue)
    {
        m_Height = AValue;
        Update();
    }
}

void CYCCrossFeature::SetWidthHeight(int AWidth, int AHeight)
{
    if (AWidth != m_Width || AHeight != m_Height)
    {
        BeginUpdate();

        m_Width = AWidth;
        m_Height = AHeight;

        EndUpdate();

        Update();
    }
}

IMPLEMENT_CYCBMPDisplayerFeature_Draw(CYCCrossFeature)
{
    if (m_Displayer && AUIDC && IsVisible())
    {
        CPen    LPen(PS_SOLID, 1, m_LineColor);
        CPen    *LOldPen = (CPen *)AUIDC->SelectObject(&LPen);
        POINT   LPnt1, LPnt2;
        bool    LFinish = false;

        for (int LStep = 0; !LFinish; LStep ++)
        {
            switch (LStep)
            {
            case 0 :
                LPnt1.x = m_Center.x - m_Width / 2;
                LPnt2.x = LPnt1.x + m_Width;
                LPnt1.y = LPnt2.y = m_Center.y;
                break;

            case 2 :
                LPnt1.x = LPnt2.x = m_Center.x;
                LPnt1.y = m_Center.y - m_Height / 2;
                LPnt2.y = LPnt1.y + m_Height;
                break;

            case 1 :
            case 3 :
                LPnt1 = m_Displayer->BMPToClient(LPnt1);
                LPnt2 = m_Displayer->BMPToClient(LPnt2);

                AUIDC->MoveTo(LPnt1);
                AUIDC->LineTo(LPnt2);
                break;

            case 4 :
                LFinish = true;

            }
        }

        AUIDC->SelectObject(LOldPen);

        if (m_Caption != "")
        {           
            CRect LTxtRect(m_Center, m_Center);

            LTxtRect.InflateRect(m_Width / 2, m_Height / 2);
            LTxtRect = m_Displayer->BMPToClient(LTxtRect);

            COLORREF LFntColor = AUIDC->GetTextColor();

            AUIDC->SetTextColor(m_LineColor);
            AUIDC->SetBkMode(TRANSPARENT);
            AUIDC->TextOutA(LTxtRect.left + LTxtRect.Width() / 4, LTxtRect.top + LTxtRect.Height() / 4, m_Caption);
            AUIDC->SetTextColor(LFntColor);
        }
    }
}
//
// CYCCrossFeature
///////////////////////////////////////////////////


///////////////////////////////////////////////////
// CYCTextFeature
//
IMPLEMENT_SERIAL(CYCTextFeature, CYCBMPDisplayerFeature, 0x0001)


CYCTextFeature::CYCTextFeature()
: CYCBMPDisplayerFeature()
{
    __super::m_CoorType = ctDisp;

    m_Rect.SetRect(0, 0, 100, 100);
    m_Text.Format("%s%d", RUNTIME_CLASS(CYCTextFeature)->m_lpszClassName, GetTickCount());
}

void CYCTextFeature::SetRect(const RECT &AValue)
{
    if (m_Rect != AValue)
    {
        m_Rect = AValue;
        Update();
    }
}

IMPLEMENT_CYCBMPDisplayerFeature_Draw(CYCTextFeature)
{
    if (m_Displayer && AUIDC && IsVisible())
    {
        CPen    LPen(PS_SOLID, 1, m_LineColor);
        CPen    *LOldPen = (CPen *)AUIDC->SelectObject(&LPen);

        CRect LTxtRect(m_Rect);

        if (CoorType() == ctBMP)
        {
            LTxtRect = m_Displayer->BMPToClient(LTxtRect);
        }
        else
        {
            CRgn    LRgn;

            LRgn.CreateRectRgn(LTxtRect.left, LTxtRect.top, LTxtRect.right, LTxtRect.bottom);
            AUIDC->SelectClipRgn(&LRgn, RGN_OR);
        }

        COLORREF LFntColor = AUIDC->GetTextColor();

        AUIDC->SetTextColor(m_LineColor);
        AUIDC->SetBkMode(TRANSPARENT);
        AUIDC->TextOut(LTxtRect.left, LTxtRect.top, m_Text);
        AUIDC->SetTextColor(LFntColor);
        AUIDC->SelectObject(LOldPen);
    }
}
//
// CYCTextFeature
///////////////////////////////////////////////////



///////////////////////////////////////////////////
// CYCReticleFeature
//
IMPLEMENT_SERIAL(CYCReticleFeature, CYCBMPDisplayerFeature, 0x0001)


CYCReticleFeature::CYCReticleFeature()
: CYCBMPDisplayerFeature()
{
}

IMPLEMENT_CYCBMPDisplayerFeature_Draw(CYCReticleFeature)
{
    if (IsVisible())
    {
        CRect LDestArea = m_Displayer->m_UIBuff.DrawArea;

        m_Displayer->m_UIBuff.DC.MoveTo(LDestArea.left + LDestArea.Width() / 2, LDestArea.top);
        m_Displayer->m_UIBuff.DC.LineTo(LDestArea.left + LDestArea.Width() / 2, LDestArea.bottom);

        m_Displayer->m_UIBuff.DC.MoveTo(LDestArea.left , LDestArea.top + LDestArea.Height() / 2);
        m_Displayer->m_UIBuff.DC.LineTo(LDestArea.right, LDestArea.top + LDestArea.Height() / 2);
    }
}
//
// CYCReticleFeature
///////////////////////////////////////////////////





IMPLEMENT_SERIAL(CYCMousePointTextFeature, CYCTextFeature, 0x0001)


CYCMousePointTextFeature::CYCMousePointTextFeature()
: CYCTextFeature()
{
    m_Point.x = m_Point.y = 0;
    SetText("(   0,    0)");
}

void CYCMousePointTextFeature::SetPoint(const POINT& AValue)
{
    if (m_Point.x != AValue.x || m_Point.y != AValue.y)
    {
        m_Point = AValue;

        CString LStr;

        LStr.Format("(% 4d, % 4d)", m_Point.x, m_Point.y);
        SetText(LStr);
    }
}



#undef CoorYToMemY

