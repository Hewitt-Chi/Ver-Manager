#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


// CYCSpectrum dialog

__interface IYCMouseMoveEventSinker
{
public:
    virtual void OnMouseMove(CWnd *ASender, UINT nFlags, CPoint point) = 0;

};

class CYCSpectrum : public CWnd
{
    DECLARE_DYNAMIC(CYCSpectrum)

public:
    // Dialog Data
    enum enmPeakType { ptType1, ptType2, ptType3 };

    CYCSpectrum();   // standard constructor
    virtual ~CYCSpectrum();

    inline void SetFixXAxis(bool AValue)
    { m_FixXAxis = AValue; };

    inline void SetFixYAxis(bool AValue)
    { m_FixYAxis = AValue; };

    void SetSpectrumMaxMinX(int AIdx, double AMaxValue, double AMinValue);
    void SetSpectrumMaxMinY(int AIdx, double AMaxValue, double AMinValue);

    void SetPeakType(enmPeakType AValue);
    void SetLevelValue(double AValue);
    void SetSpectrum(const std::vector<double> &AValue);
    int  AddSpectrum(const std::vector<strYCDoublePoint> &AValue, COLORREF  AColor);
    void AddSpectrumData(int AIdx, const std::vector<strYCDoublePoint> &AValue);
    void SetSpectrum(int AIdx, const std::vector<strYCDoublePoint> &AValue);
    void SetBaseValue(int AIdx, double AValue);
    void AddPoint(int AIdx, double AX, double AY, COLORREF AColor = clLimeGreen);
    void ClearBaseValue(int AIdx);
    void ClearSpectrum();
    void FindPeak(int AIdx);
    void GetMousePointData(int AIdx, double &AX, double &AY);
    double YOf(int AIdx, double AX, double ATolance = 1.0);

    inline bool IsGridLineVisible() const
    { return m_IsGridLineVisible; };

    inline void SetIsGridLineVisible(bool AValue)
    {
        if (m_IsGridLineVisible != AValue)
        {
            m_IsGridLineVisible = AValue;
            UpdateBufferChart(false); 
        }
    };

    inline int  SpectrumCount() const
    { return (int)m_CurveDatas.size(); };

    template <class T>
    void SetSpectrum(T *AValue, int ACount)
    {
        std::vector<double> LValues;

        TRACE("\n");

        for (int I = 0; I < ACount; I ++)
        {
            LValues.push_back(AValue[I]);

#ifdef _DEBUG
            TRACE("%d ", AValue[I]);

            if ((I > 0) && ((I % 8) == 0))
            {
                TRACE("\n");
            }
#endif
        }

        TRACE("\n");

        SetSpectrum(LValues);
    };

    void UpdateBufferChart(bool AIsRecreateDC);

    inline IYCMouseMoveEventSinker*   MouseMoveEventSinker() const
    { return m_MouseMoveEventSinker; };

    inline void SetMouseMoveEventSinker(IYCMouseMoveEventSinker *AValue)
    { m_MouseMoveEventSinker = AValue; };

    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

protected:
    static BOOL m_IsClassRegistered;
    static char *m_ClassName;

    static BOOL RegisterThisClass();

    virtual void PreSubclassWindow();
    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    afx_msg void OnPaint();

    DECLARE_MESSAGE_MAP()

private:
    struct strPointData
    {
        strYCDoublePoint  Point;
        COLORREF        Color;
    };

    struct strSpectrumData
    {
        std::vector<strYCDoublePoint> Datas;
        std::vector<int>            Peaks;
    };

    struct strCurveData
    {
        double                          MaxX;
        double                          MinX;
        double                          MaxY;
        double                          MinY;
        std::vector<strSpectrumData *>  Datas;
        std::vector<strPointData>       Points;
        double                          BaseValue;
        bool                            IsBaseValueValid;
        COLORREF                        Color;

        inline double XSpan() const
        { return MaxX - MinX; };
        
        inline double YSpan() const
        { return MaxY - MinY; };
    };

    bool m_FixXAxis;
    bool m_FixYAxis;
    
    std::deque<strCurveData *>  m_CurveDatas;
    
    enmPeakType         m_PeakType;

    struct
    {
        CDC     DC;
        CBitmap Bitmap;
        CRect   ChartArea;
        CRect   GridArea;
    } m_BufferChart;


    CPoint  m_MousePoint;
    
    bool m_IsEraseReticleEnabled;
    bool m_IsGridLineVisible;

    IYCMouseMoveEventSinker *m_MouseMoveEventSinker;

    void RedrawCurve();
    void RedrawCoordinate();
    void DataToImg(int ACurveIdx, double AX, double AY, OUT POINT *APoint);
    void ImgToData(int ACurveIdx, int AImgX, int AImgY, OUT double *AX, OUT double *AY);
    void UpdatePeaks();
    void UpdateScrollBar();
    void DrawMouseReticle(CPoint APoint);
    void UpdateXYRange();
};

extern void YCInsertSort(std::vector<strYCDoublePoint> &AValues, strYCDoublePoint AValue);
