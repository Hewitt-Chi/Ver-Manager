// dlgSpectrum.cpp : implementation file
//

#include "stdafx.h"

#include "YCUtils.h"
#include "YCSpectrum.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


void YCInsertSort(std::vector<strYCDoublePoint> &AValues, strYCDoublePoint AValue)
{
    for (int I = (int)AValues.size() - 1; I >= 0; I --)
    {
        if (AValue.X >= AValues[I].X)
        {
            AValues.insert(AValues.begin() + I + 1, AValue);
            return ;
        }
    }

    AValues.insert(AValues.begin(), AValue);
}

BOOL CYCSpectrum::m_IsClassRegistered = CYCSpectrum::RegisterThisClass();
char *CYCSpectrum::m_ClassName = "CYCSpectrum";

// CYCSpectrum dialog

IMPLEMENT_DYNAMIC(CYCSpectrum, CWnd)

CYCSpectrum::CYCSpectrum()
: CWnd(), m_IsEraseReticleEnabled(false)
, m_IsGridLineVisible(true), m_FixXAxis(false), m_FixYAxis(false)
, m_MouseMoveEventSinker(NULL)
{
}

CYCSpectrum::~CYCSpectrum()
{
    ClearSpectrum();
}

void CYCSpectrum::ClearSpectrum()
{
    while (m_CurveDatas.size())
    {
        for (int I = 0; I < (int)m_CurveDatas.front()->Datas.size(); I ++)
            delete m_CurveDatas.front()->Datas[I];

        delete m_CurveDatas[0];
        m_CurveDatas.pop_front();
    }

    UpdateBufferChart(false);

}

void CYCSpectrum::DoDataExchange(CDataExchange* pDX)
{
    CWnd::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CYCSpectrum, CWnd)
    ON_WM_PAINT()
    ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CYCSpectrum message handlers
BOOL CYCSpectrum::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{

    if (message == WM_EXITSIZEMOVE)
    {
        UpdateBufferChart(true);    
    }

    return CWnd::OnWndMsg(message, wParam, lParam, pResult);
}

void CYCSpectrum::OnPaint()
{
    // DrawMouseReticle(m_MousePoint);

    CPaintDC dc(this); // device context for painting

    // TODO: Add your message handler code here
    // Do not call CWnd::OnPaint() for painting messages   
    CRect   LRect = m_BufferChart.ChartArea;

    dc.BitBlt(LRect.left, LRect.top, LRect.Width(), LRect.Height(), &m_BufferChart.DC, LRect.left, LRect.top, SRCCOPY);

    m_IsEraseReticleEnabled = false;
}

void CYCSpectrum::SetLevelValue(double AValue)
{
}

void YCInsertSort(std::vector<double> &AValues, double AValue)
{
    for (int I = (int)AValues.size() - 1; I >= 0; I --)
    {
        if (AValue >= AValues[I])
        {
            AValues.insert(AValues.begin() + I + 1, AValue);
            return ;
        }
    }

    AValues.insert(AValues.begin(), AValue);
}

void CYCSpectrum::SetSpectrum(const std::vector<double> &AValue)
{
}

int CYCSpectrum::AddSpectrum(const std::vector<strYCDoublePoint> &AValue, COLORREF AColor)
{
    if (AValue.size() > 0)
    {
        strCurveData *LData = new strCurveData();

        LData->Datas.push_back(new strSpectrumData());

        LData->MinY = AValue[0].Y;
        LData->MaxY = AValue[0].Y;
        LData->MinX = AValue[0].X;
        LData->MaxX = AValue[0].X;
        LData->BaseValue = 0;
        LData->IsBaseValueValid = false;

        for (int I = 0; I < (int)AValue.size(); I ++)
        {
            YCInsertSort(LData->Datas[0]->Datas, AValue[I]);

            if (AValue[I].Y > LData->MaxY)
                LData->MaxY = AValue[I].Y;
            else if (AValue[I].Y < LData->MinY)
                LData->MinY = AValue[I].Y;
        }

        LData->MaxY += abs((LData->MaxY - LData->MinY) * 0.1);
        LData->MinY -= abs((LData->MaxY - LData->MinY) * 0.1);
        LData->MinX = LData->Datas[0]->Datas.front().X;
        LData->MaxX = LData->Datas[0]->Datas.back().X;
        LData->Color = AColor;

        m_CurveDatas.push_back(LData);

        UpdateXYRange();
        UpdateBufferChart(false);

        return (int)m_CurveDatas.size() - 1;
    }

    return -1;
}

void CYCSpectrum::AddSpectrumData(int AIdx, const std::vector<strYCDoublePoint> &AValue)
{
    if (AValue.size() > 0)
    {
        strCurveData    *LData = m_CurveDatas[AIdx];
        strSpectrumData *LSpecData = new strSpectrumData();

        LData->Datas.push_back(LSpecData);

        double LMinY = LData->MinY;
        double LMaxY = LData->MaxY;
        double LMinX = LData->MinX;
        double LMaxX = LData->MaxX;

        for (int I = 0; I < (int)AValue.size(); I ++)
        {
            YCInsertSort(LSpecData->Datas, AValue[I]);

            if (AValue[I].Y > LMaxY)
                LMaxY = AValue[I].Y;
            else if (AValue[I].Y < LMinY)
                LMinY = AValue[I].Y;
        }

        LMinY -= abs((LMaxY - LMinY) * 0.1);
        LMaxY += abs((LMaxY - LMinY) * 0.1);
        LMinX = LSpecData->Datas.front().X;
        LMaxX = LSpecData->Datas.back().X;

        if (LMinX < LData->MinX)
            LData->MinX = LMinX;

        if (LMinY < LData->MinY)
            LData->MinY = LMinY;

        if (LMaxX > LData->MaxX)
            LData->MaxX = LMaxX;

        if (LMaxY > LData->MaxY)
            LData->MaxY = LMaxY;

        UpdateXYRange();
        UpdateBufferChart(false);
    }
}

void CYCSpectrum::SetSpectrum(int AIdx, const std::vector<strYCDoublePoint> &AValue)
{
}

void CYCSpectrum::SetBaseValue(int AIdx, double AValue)
{
    m_CurveDatas[AIdx]->BaseValue = AValue;
    m_CurveDatas[AIdx]->IsBaseValueValid = true;

    UpdateBufferChart(false);
}

void CYCSpectrum::AddPoint(int AIdx, double AX, double AY, COLORREF AColor/* = clLimeGreen*/)
{
    strPointData LData = { { AX, AY}, AColor };
    m_CurveDatas[AIdx]->Points.push_back(LData);

    UpdateBufferChart(false);
}

void CYCSpectrum::ClearBaseValue(int AIdx)
{
    m_CurveDatas[AIdx]->IsBaseValueValid = false;

    UpdateBufferChart(false);
}

void CYCSpectrum::SetPeakType(CYCSpectrum::enmPeakType AValue)
{
    if (m_PeakType != AValue)
    {
        m_PeakType = AValue;

        UpdatePeaks();
        UpdateBufferChart(false);
    }
}

void CYCSpectrum::SetSpectrumMaxMinX(int AIdx, double AMaxValue, double AMinValue)
{
    if (AIdx >= 0 && AIdx < (int)m_CurveDatas.size())
    {
        m_CurveDatas[AIdx]->MaxX = AMaxValue;
        m_CurveDatas[AIdx]->MinX = AMinValue;

        UpdateBufferChart(false);
    }
}

void CYCSpectrum::SetSpectrumMaxMinY(int AIdx, double AMaxValue, double AMinValue)
{
    if (AIdx >= 0 && AIdx < (int)m_CurveDatas.size())
    {
        m_CurveDatas[AIdx]->MaxY = AMaxValue;
        m_CurveDatas[AIdx]->MinY = AMinValue;

        UpdateBufferChart(false);
    }
}

void CYCSpectrum::UpdateBufferChart(bool AIsRecreateDC)
{
    if (m_hWnd)
    {
        ////////////////////////////////////////////////////
        // 更新m_BufferChart中的Resource使其符合
        // Dialog的ClientArea一樣
        //    
        if (AIsRecreateDC && m_BufferChart.DC.m_hDC)
        {
            // 把舊有的dc刪除
            m_BufferChart.DC.DeleteDC();
            m_BufferChart.Bitmap.DeleteObject();
        }

        if (m_hWnd && !m_BufferChart.DC.m_hDC)
        {
            // 建立新的dc
            CRect   LClientRect;

            this->GetClientRect(&LClientRect);
            m_BufferChart.Bitmap.CreateCompatibleBitmap(&CClientDC(this), LClientRect.Width(), LClientRect.Height());

            m_BufferChart.DC.CreateCompatibleDC(&CClientDC(this));
            m_BufferChart.DC.SelectObject(&m_BufferChart.Bitmap);

            // 計算圖表的顯示區域
            GetClientRect(&m_BufferChart.ChartArea);
            m_BufferChart.GridArea = m_BufferChart.ChartArea;
            m_BufferChart.GridArea.InflateRect(-10, -10);
        }
        //
        // 更新m_BufferChart中的Resource使其符合
        // Dialog的ClientArea一樣    
        ////////////////////////////////////////////////////

        if (m_BufferChart.DC.m_hDC)
        {
            ///////////////////////////////////////
            // 畫底色(清除畫面)
            //
            CRect   LClientRect;
            CBrush  LNewBrush(RGB(0, 0, 0));
            CBrush  *LOldBrush = m_BufferChart.DC.SelectObject(&LNewBrush);

            GetClientRect(&LClientRect);
            m_BufferChart.DC.Rectangle(&LClientRect);
            m_BufferChart.DC.SelectObject(LOldBrush);
            //
            // 畫底色(清除畫面)
            ///////////////////////////////////////

            // 畫座標(包含單位)
            RedrawCoordinate();

            // 畫資曲線圖
            RedrawCurve();

            // 呼叫CYCSpectrum更新
            Invalidate();
        }
    }
}

void CYCSpectrum::RedrawCoordinate()
{
    CDC &LDC = m_BufferChart.DC;

    if (LDC.m_hDC)
    {
        CPen    LPen(PS_SOLID, 1, RGB(255, 255, 255));
        CPen    *LOldPen = LDC.SelectObject(&LPen);
        CBrush  *LOldBrush = (CBrush  *)LDC.SelectStockObject(BLACK_BRUSH);
        POINT   LLine[3] = 
        {
            {m_BufferChart.GridArea.left , m_BufferChart.GridArea.top}, 
            {m_BufferChart.GridArea.left , m_BufferChart.GridArea.bottom}, 
            {m_BufferChart.GridArea.right, m_BufferChart.GridArea.bottom}
        };

        LDC.SetBkMode(TRANSPARENT);
        LDC.SetTextColor(RGB(255, 255, 255));

        // 畫出軸線        
        //LDC.Polyline(LLine, 3);
        LDC.Rectangle(m_BufferChart.GridArea);

        if (m_IsGridLineVisible)
        {
            for (int I = 1; I < 4; I ++)
            {      
                ///////////////////////////////////////
                // 畫出y軸(spectrum value)上的刻度
                //
                LLine[0].x = m_BufferChart.GridArea.left;
                LLine[0].y = m_BufferChart.GridArea.bottom - (I * m_BufferChart.GridArea.Height() / 4);
                LLine[1].x = m_BufferChart.GridArea.right;
                LLine[1].y = m_BufferChart.GridArea.bottom - (I * m_BufferChart.GridArea.Height() / 4);

                LDC.Polyline(&LLine[0], 2);

#if 0
                if (I > 0)
                {
                    // 標出刻度數值
                    CString LStr;

                    LStr.Format("%.1f", m_MaxSpectrumValue / 10.0 * I);
                    LDC.TextOutA(m_BufferChart.GridArea.left - 55, LLine[0].y - 5, LStr, LStr.GetLength());
                }
#endif
                //
                // 畫出y軸(rpm)上的刻度
                ///////////////////////////////////////

                ///////////////////////////////////////
                // 畫出x軸(sec)上的刻度
                //
                LLine[0].x = m_BufferChart.GridArea.left + (I * m_BufferChart.GridArea.Width() / 4);
                LLine[0].y = m_BufferChart.GridArea.bottom - 1;
                LLine[1].x = m_BufferChart.GridArea.left + (I * m_BufferChart.GridArea.Width() / 4);
                LLine[1].y = m_BufferChart.GridArea.top;

                LDC.Polyline(&LLine[0], 2);

#if 0
                if (I > 0)
                {
                    // 標出刻度數值
                    CString LStr;

                    LStr.Format("%.1f", m_PixelCount / 10.0 * I);
                    LDC.TextOut(LLine[0].x - 10, m_BufferChart.GridArea.bottom + 10, LStr, LStr.GetLength());
                }
#endif
                //
                // 畫出x軸(sec)上的刻度
                ///////////////////////////////////////
            }
        }
#if 0
        // 畫出x軸單位        
        LDC.TextOutA(m_BufferChart.GridArea.right + 3, m_BufferChart.ChartArea.bottom - 10, "idx", 3);

        // 畫出y軸單位        
        LDC.TextOutA(m_BufferChart.GridArea.left - 28, m_BufferChart.ChartArea.top - 22, "val", 3);

        // 畫出圓點       
        LDC.TextOutA(m_BufferChart.GridArea.left - 10, m_BufferChart.ChartArea.bottom + 10, "0", 1);
#endif

        LDC.SelectObject(LOldBrush);
        LDC.SelectObject(LOldPen);
    }
}

void CYCSpectrum::RedrawCurve()
{
    if (m_BufferChart.DC.m_hDC)
    {
        POINT   LPoint = {m_BufferChart.GridArea.left, m_BufferChart.GridArea.bottom};
        CPen    LPen; 
        CPen    *LOldPen = NULL;

        m_BufferChart.DC.SetBkMode(TRANSPARENT);

        for (int LCurveIdx = 0; LCurveIdx < (int)m_CurveDatas.size(); LCurveIdx ++)
        {
            strCurveData *LCurveData = m_CurveDatas[LCurveIdx];

            LPen.CreatePen(PS_SOLID, 1, LCurveData->Color);
            LOldPen = (CPen *)m_BufferChart.DC.SelectObject(&LPen);

            ////////////////////////////////////
            // 畫出曲線
            //
            for (int LDataIdx = 0; LDataIdx < (int)LCurveData->Datas.size(); LDataIdx ++)
            {
                strSpectrumData             *LSpectrumData = LCurveData->Datas[LDataIdx];
                std::vector<strYCDoublePoint> *LPntData      = &LSpectrumData->Datas;

                for (int I = 0; I < (int)LPntData->size(); I ++)
                {
                    DataToImg(LCurveIdx, (*LPntData)[I].X, (*LPntData)[I].Y, &LPoint);

                    if (I == 0)
                        m_BufferChart.DC.MoveTo(LPoint);
                    else m_BufferChart.DC.LineTo(LPoint);
                }
            }
            //
            // 畫出像數值
            ////////////////////////////////////

            ////////////////////////////////////
            // 畫出水平標準線
            //
            if (LCurveData->IsBaseValueValid)
            {
                POINT LPnt;

                DataToImg(LCurveIdx, LCurveData->MinX, m_CurveDatas[LCurveIdx]->BaseValue, &LPnt);

                m_BufferChart.DC.MoveTo(m_BufferChart.GridArea.left , LPnt.y);
                m_BufferChart.DC.LineTo(m_BufferChart.GridArea.right, LPnt.y);
            }
            //
            // 畫出水平標準線(白色)
            ////////////////////////////////////

            m_BufferChart.DC.SelectObject(&LOldPen);
            LPen.DeleteObject();
        }

        ////////////////////////////////////
        // 畫出Peak點(clLime)
        //
        for (int LCurveIdx = 0; LCurveIdx < (int)m_CurveDatas.size(); LCurveIdx ++)
        {
            strCurveData *LCurveData = m_CurveDatas[LCurveIdx];

            for (int LDataIdx = 0; LDataIdx < (int)LCurveData->Datas.size(); LDataIdx ++)
            {
                strSpectrumData     *LSpectrumData = LCurveData->Datas[LDataIdx];
                std::vector<int>    *LPeakData     = &LSpectrumData->Peaks;

                for (int I = 0; I < (int)LPeakData->size(); I ++)
                {
                    POINT   LData;
                    CBrush  LTheBrush(clLime);

                    DataToImg(LCurveIdx, LSpectrumData->Datas[(*LPeakData)[I]].X, LSpectrumData->Datas[(*LPeakData)[I]].Y, &LData);

                    CRect LRect(LData, CSize(5, 5));

                    LRect.OffsetRect(-2, -2);
                    m_BufferChart.DC.FillRect(&LRect, &LTheBrush);
                }
            }
        }
        //
        // 畫出Peak點(clLime)
        ////////////////////////////////////

        ////////////////////////////////////
        // 畫出點
        //
        for (int LCurveIdx = 0; LCurveIdx < (int)m_CurveDatas.size(); LCurveIdx ++)
        {
            strCurveData    *LCurve = m_CurveDatas[LCurveIdx];

            for (int I = 0; I < (int)LCurve->Points.size(); I ++)
            {
                POINT   LData;
                CBrush  LTheBrush(LCurve->Points[I].Color);

                DataToImg(LCurveIdx, LCurve->Points[I].Point.X, LCurve->Points[I].Point.Y, &LData);

                CRect LRect(LData, CSize(5, 5));

                LRect.OffsetRect(-2, -2);
                m_BufferChart.DC.FillRect(&LRect, &LTheBrush);
            }
        }
        //
        // 畫出點
        ////////////////////////////////////
    }
}

void CYCSpectrum::DataToImg(int ACurveIdx, double AX, double AY, OUT POINT *APoint)
{
    const double LMaxY = m_CurveDatas[ACurveIdx]->MaxY;
    const double LMinY = m_CurveDatas[ACurveIdx]->MinY;
    const double LMaxX = m_CurveDatas[ACurveIdx]->MaxX;
    const double LMinX = m_CurveDatas[ACurveIdx]->MinX;
    const double LYSpan = LMaxY - LMinY;
    const double LXSpan = LMaxX - LMinX;

    APoint->x = m_BufferChart.GridArea.left   + (long)(((AX - LMinX) / LXSpan) * m_BufferChart.GridArea.Width())  + 1;
    APoint->y = m_BufferChart.GridArea.bottom - (long)(((AY - LMinY) / LYSpan) * m_BufferChart.GridArea.Height()) - 1;
}

void CYCSpectrum::ImgToData(int ACurveIdx, int AImgX, int AImgY, OUT double *AX, OUT double *AY)
{
    const double LMaxY = m_BufferChart.GridArea.bottom;
    const double LMinY = m_BufferChart.GridArea.top;
    const double LMaxX = m_BufferChart.GridArea.right;
    const double LMinX = m_BufferChart.GridArea.left;
    const double LYSpan = LMaxY - LMinY;
    const double LXSpan = LMaxX - LMinX;

    if (AX)
        *AX = m_CurveDatas[ACurveIdx]->MinX
        + (((AImgX - LMinX) * 1.0 / LXSpan) * m_CurveDatas[ACurveIdx]->XSpan());

    if (AY)
        *AY = m_CurveDatas[ACurveIdx]->MinY
        + (((AImgY - LMaxY) * -1.0 / LYSpan) * m_CurveDatas[ACurveIdx]->YSpan());
}

void CYCSpectrum::UpdatePeaks()
{
#if 0
    m_SpectrumPeaks.clear();

    switch (m_PeakType)
    {
    case ptType1 :
        {
            std::vector<int>   LGroupIdxs;

            for (size_t LIdx = 0; LIdx < m_SpectrumValues.size(); LIdx ++)
            {
                if (m_SpectrumValues[LIdx] >= m_LevelValue)
                {
                    LGroupIdxs.push_back(LIdx);
                }
                else
                {
                    if (LGroupIdxs.size() > 0)
                    {
                        m_SpectrumPeaks.push_back((LGroupIdxs.front() + LGroupIdxs.back()) / 2);
                        LGroupIdxs.clear();

                        TRACE("Peek #%d value %d\n", m_SpectrumPeaks.size() - 1, m_SpectrumPeaks.back());
                    }
                }
            }

            if (LGroupIdxs.size() > 0)
            {
                m_SpectrumPeaks.push_back((LGroupIdxs.front() + LGroupIdxs.back()) / 2);
                LGroupIdxs.clear();

                TRACE("Peek #%d value %d\n", m_SpectrumPeaks.size() - 1, m_SpectrumPeaks.back());
            }
        }
        break;

    case ptType2 :
        {
            std::vector<double >   LSlides;

            LSlides.resize(m_SpectrumValues.size());

            if (m_SpectrumValues.size() >= 7)
            {
                for (size_t LIdx = 3; LIdx < m_SpectrumValues.size() - 3; LIdx ++)
                {
                    strYCDoublePoint    LPoints[] =
                    {
                        strYCDoublePoint(LIdx - 3, m_SpectrumValues[LIdx - 3]), 
                        strYCDoublePoint(LIdx - 2, m_SpectrumValues[LIdx - 2]), 
                        strYCDoublePoint(LIdx - 1, m_SpectrumValues[LIdx - 1]), 
                        strYCDoublePoint(LIdx    , m_SpectrumValues[LIdx    ]), 
                        strYCDoublePoint(LIdx + 1, m_SpectrumValues[LIdx + 1]), 
                        strYCDoublePoint(LIdx + 2, m_SpectrumValues[LIdx + 2]), 
                        strYCDoublePoint(LIdx + 3, m_SpectrumValues[LIdx + 3]), 
                    };

                    double LA;

                    YCAnalyzeLine(7, LPoints, &LA, NULL);

                    LSlides[LIdx] = LA;

                    TRACE("LSlides[%d] = %.3f\n", LIdx, LA);
                } // for (size_t LIdx = 2; LIdx < m_SpectrumValues.size() - 2; LIdx ++)

                LSlides[0] = LSlides[1] = LSlides[2]/* = LSlides[3]*/;
                LSlides[LSlides.size() - 1] = LSlides[LSlides.size() - 2] = LSlides[LSlides.size() - 3]/* = LSlides[LSlides.size() - 4]*/;

                m_SpectrumValues = LSlides;
                m_MaxSpectrumValue = YCMax<double>(&m_SpectrumValues[0], m_SpectrumValues.size());
                m_MinSpectrumValue = YCMin<double>(&m_SpectrumValues[0], m_SpectrumValues.size());
                m_LevelValue = (m_MaxSpectrumValue + m_MinSpectrumValue) / 2.0;

                UpdateBufferChart(false);
                UpdateScrollBar();
            }
        }
        break;


    case ptType3 :
        {
            m_PeakType = ptType2;

            UpdatePeaks();

            m_PeakType = ptType3;

            std::vector<double>   LSlides = m_SpectrumValues;
            std::vector<double>   LdSlides;

            LdSlides.resize(LSlides.size());

            for (size_t LIdx = 3; LIdx < LSlides.size() - 3; LIdx ++)
            {
                strYCDoublePoint    LPoints[7] =
                {
                    strYCDoublePoint(LIdx - 3, LSlides[LIdx - 3]), 
                    strYCDoublePoint(LIdx - 2, LSlides[LIdx - 2]), 
                    strYCDoublePoint(LIdx - 1, LSlides[LIdx - 1]), 
                    strYCDoublePoint(LIdx    , LSlides[LIdx    ]), 
                    strYCDoublePoint(LIdx + 1, LSlides[LIdx + 1]), 
                    strYCDoublePoint(LIdx + 2, LSlides[LIdx + 2]), 
                    strYCDoublePoint(LIdx + 3, LSlides[LIdx + 3]), 
                };

                double LA;

                YCAnalyzeLine(7, LPoints, &LA, NULL);

                //LdSlides[LIdx] = LSlides[LIdx] - LSlides[LIdx - 1];
                LdSlides[LIdx] = LA;

                TRACE("LdSlides[%d] = %.3f\n", LIdx, LdSlides[LIdx]);

            } // for (size_t LIdx = 1; LIdx < LSlides.size() - 1; LIdx ++)

            LdSlides[0] = LdSlides[1] = LdSlides[2] = LdSlides[3];
            LdSlides[LdSlides.size() - 1] = LdSlides[LdSlides.size() - 2] = LdSlides[LdSlides.size() - 3] = LdSlides[LdSlides.size() - 4];

            m_SpectrumValues = LdSlides;
            m_MaxSpectrumValue = YCMax<double>(&m_SpectrumValues[0], m_SpectrumValues.size());
            m_MinSpectrumValue = YCMin<double>(&m_SpectrumValues[0], m_SpectrumValues.size());
            m_LevelValue = (m_MaxSpectrumValue + m_MinSpectrumValue) / 2.0;

            UpdateBufferChart(false);
            UpdateScrollBar();
        }
        break;

    }
#endif
}

void CYCSpectrum::FindPeak(int AIdx)
{
    if (AIdx >= 0 && AIdx < (int)m_CurveDatas.size())
    {
        strCurveData *LCurve = m_CurveDatas[AIdx];

        for (int LDataIdx = 0; LDataIdx < (int)LCurve->Datas.size(); LDataIdx ++)
        {
            std::vector<strYCDoublePoint> *LDatas = &LCurve->Datas[LDataIdx]->Datas;
            std::vector<int>            *LPeaks = &LCurve->Datas[LDataIdx]->Peaks;

            LPeaks->clear();

            int LPeakIdx = 0;

            for (int I = 1; I < (int)LCurve->Datas.size(); I ++)
            {
                if ((*LDatas)[I].Y > (*LDatas)[LPeakIdx].Y)
                    LPeakIdx = I;
            }

            LPeaks->push_back(LPeakIdx);
        }

        UpdateBufferChart(false);
    }
}

void CYCSpectrum::GetMousePointData(int AIdx, double &AX, double &AY)
{
    ImgToData(AIdx, m_MousePoint.x, m_MousePoint.y, &AX, &AY);
}

double YOf(std::vector<strYCDoublePoint> &ADatas, int AIdxL, int AIdxR, double AX)
{
    strYCDoublePoint LDataM = ADatas[(AIdxL + AIdxR) / 2];

    if (AIdxR == AIdxL + 1)
    {
        strYCDoublePoint LDataL = ADatas[AIdxL];
        strYCDoublePoint LDataR = ADatas[AIdxR];

        return LDataL.Y + (AX - LDataL.X) / (LDataR.X - LDataL.X) * (LDataR.Y - LDataL.Y);
    }
    else if (AX == LDataM.X)
    {
        return LDataM.Y;
    }
    else if (AX < LDataM.X)
    {
        return YOf(ADatas, AIdxL, (AIdxL + AIdxR) / 2, AX);
    }
    else /* if (AX > LDataM.X) */
    {
        return YOf(ADatas, (AIdxL + AIdxR) / 2, AIdxR, AX);
    }
}

double CYCSpectrum::YOf(int AIdx, double AX, double ATolance/* = 1.0*/)
{
    std::vector<strYCDoublePoint> &LDatas = m_CurveDatas[AIdx]->Datas[0]->Datas;

    if (LDatas.size() > 0)
    {
        if (LDatas.size() > 1)
        {
            AX = ::YOf(LDatas, 0, (int)LDatas.size() - 1, AX);
        }
        else if (abs(AX - LDatas[0].X) <= ATolance)
        {
            AX = LDatas[0].Y;
        }

        return AX;
    }

    return 0;
}

void CYCSpectrum::OnMouseMove(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    if (m_BufferChart.GridArea.PtInRect(point))
    {
        if (m_IsEraseReticleEnabled)
            DrawMouseReticle(m_MousePoint);

        m_MousePoint = point;
        DrawMouseReticle(m_MousePoint);
        m_IsEraseReticleEnabled = true;
        //UpdateBufferChart(false);
    }

    if (m_MouseMoveEventSinker)
        m_MouseMoveEventSinker->OnMouseMove(this, nFlags, point);

    CWnd::OnMouseMove(nFlags, point);
}

void CYCSpectrum::DrawMouseReticle(CPoint APoint)
{
#if 1
    if (m_BufferChart.GridArea.PtInRect(APoint))
    {
        CClientDC   LDC(this);
        CPen        LPen(PS_SOLID, 1, clYellow);
        CPen        *LOldPen = (CPen *)LDC.SelectObject(&LPen);

        int LOldROP2 = LDC.SetROP2(R2_XORPEN);
        LDC.MoveTo(APoint.x, m_BufferChart.GridArea.top);
        LDC.LineTo(APoint.x, m_BufferChart.GridArea.bottom);

        LDC.MoveTo(m_BufferChart.GridArea.left , APoint.y);
        LDC.LineTo(m_BufferChart.GridArea.right, APoint.y);

        LPen.DeleteObject();
        LDC.SelectObject(LOldPen);
        LDC.SetROP2(LOldROP2);
    }
#endif
}

void CYCSpectrum::UpdateXYRange()
{
    double LMaxX, LMinX, LMaxY, LMinY;

    for (int I = 0; I < (int)m_CurveDatas.size(); I ++)
    {
        if (I == 0)
        {
            LMaxX = m_CurveDatas[I]->MaxX;
            LMaxY = m_CurveDatas[I]->MaxY;
            LMinX = m_CurveDatas[I]->MinX;
            LMinY = m_CurveDatas[I]->MinY;
        }
        else
        {
            if (LMaxX < m_CurveDatas[I]->MaxX)
                LMaxX = m_CurveDatas[I]->MaxX;

            if (LMaxY < m_CurveDatas[I]->MaxY)
                LMaxY = m_CurveDatas[I]->MaxY;

            if (LMinX > m_CurveDatas[I]->MinX)
                LMinX = m_CurveDatas[I]->MinX;

            if (LMinY > m_CurveDatas[I]->MinY)
                LMinY = m_CurveDatas[I]->MinY;
        }
    }

    for (int I = 0; I < (int)m_CurveDatas.size(); I ++)
    {
        if (m_FixXAxis)
        {
            m_CurveDatas[I]->MaxX = LMaxX;
            m_CurveDatas[I]->MinX = LMinX;
        }

        if (m_FixYAxis)
        {
            m_CurveDatas[I]->MaxY = LMaxY;
            m_CurveDatas[I]->MinY = LMinY;
        }
    }
}

void CYCSpectrum::PreSubclassWindow()
{


    // TODO:  Add extra initialization here
    UpdateBufferChart(true);

    __super::PreSubclassWindow();
}

BOOL CYCSpectrum::RegisterThisClass()
{
    WNDCLASS wc;   
    wc.style = 0;                                                 
    wc.lpfnWndProc = ::DefWindowProc; // must be this value
    wc.cbClsExtra = 0;                         
    wc.cbWndExtra = 0;                               
    wc.hInstance = (HINSTANCE)::GetModuleHandle(NULL);        
    wc.hIcon = NULL;     // child window has no icon         
    wc.hCursor = NULL;   // we use OnSetCursor                  
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);                
    wc.lpszMenuName = NULL;  // no menu                             
    wc.lpszClassName = m_ClassName;                          

    return AfxRegisterClass(&wc);
}