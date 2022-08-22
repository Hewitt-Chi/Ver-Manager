#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

////////////////////////////////////////////////////////////
//
//  �ϥΤ覡�G1.constructor
//            2.�]�wbmp size
//            3.�]�w�䥦�ݩ�(�i�_�ؿ��ơA�i�_��ܼнu�A�i�_����A�i�_��j�Y�p�A��ܭ��v�A��U�нu)
//            4.Create
//            5.�վ��A����m
//            6.ShowBMPBMP, ShowBMPRaw
//            7.�ؿ��ơA���X�Q�ؿ諸���
//            8.Destroy
//
//
//
//
class CYCBMPDisplayer;

__interface IYCBMPDisplayerEventSinker
{
public:
    virtual void OnMouseMove(CYCBMPDisplayer *ASender, POINT APoint)        = NULL;
    virtual void OnSelectArea(CYCBMPDisplayer *ASender)                     = NULL;
    virtual void OnClearSelectedAreas(CYCBMPDisplayer *ASender)             = NULL;
    virtual void OnSelectedAreaSizing(CYCBMPDisplayer *ASender, int AIndex) = NULL;
    virtual void OnSelectedAreaSized(CYCBMPDisplayer *ASender, int AIndex)  = NULL;
    virtual void OnZoom(CYCBMPDisplayer *ASender)                           = NULL;
    virtual void OnSelectLine(CYCBMPDisplayer *ASender)                     = NULL;
    virtual void OnClearSelectedLines(CYCBMPDisplayer *ASender)             = NULL;
    virtual void OnCustomDraw(CYCBMPDisplayer *ASender, CDC *ADC)           = NULL;
};



///////////////////////////////////////////////////
// CYCBMPDisplayerFeature
//
#define   VIRTUAL_CYCBMPDisplayerFeature_Draw()                 virtual void Draw(CDC *AUIDC)
#define IMPLEMENT_CYCBMPDisplayerFeature_Draw(AClass)           void AClass::Draw(CDC *AUIDC)
#define  OVERRIDE_CYCBMPDisplayerFeature_Draw                   VIRTUAL_CYCBMPDisplayerFeature_Draw


class CYCBMPDisplayerFeature : public CObject
{
    friend CYCBMPDisplayer;

    DECLARE_DYNAMIC(CYCBMPDisplayerFeature)

public:
    enum enmCoorType { ctBMP, ctDisp };

    CYCBMPDisplayerFeature();
    virtual ~CYCBMPDisplayerFeature();

    // Displayer
    void SetDisplayer(CYCBMPDisplayer *ADisplayer);

    inline enmCoorType CoorType() const
    { return m_CoorType; };

    inline void SetCoorType(enmCoorType AValue)
    { if (m_CoorType != AValue) { m_CoorType = AValue; Update(); } };

    // Is owned by displayer
    inline bool IsOwnedByDisplayer()
    { return m_IsOwnedByDisplayer; };

    inline void SetIsOwnedByDisplayer(bool AValue)
    { m_IsOwnedByDisplayer = AValue; };

    // is visible
    inline bool IsVisible() const
    { return m_IsVisible; };

    void SetIsVisible(bool AValue);

    // caption
    inline LPCSTR Caption() const
    { return m_Caption; };

    void SetCaption(LPCSTR AValue);

    // line/font color
    inline COLORREF LineColor()
    { return m_LineColor; };

    void SetLineColor(COLORREF AValue);

    // begin update
    inline void BeginUpdate()
    { m_DisableUpdateCount ++; }

    // end update
    void EndUpdate();

    // update
    void Update();

    VIRTUAL_CYCBMPDisplayerFeature_Draw() = NULL;

protected:
    // �p�G�Otrue�A��Displayer destroy�ɡA�|�N�o��feature����C
    bool            m_IsOwnedByDisplayer;
    bool            m_IsVisible;
    CString         m_Caption;
    COLORREF        m_LineColor;
    enmCoorType     m_CoorType;
    int             m_UpdateCount;
    int             m_DisableUpdateCount;
    CYCBMPDisplayer *m_Displayer;

};

class CYCLineFeature : public CYCBMPDisplayerFeature
{

};


///////////////////////////////////////////////////
// CYCRetangleFeature
//
class CYCRetangleFeature : public CYCBMPDisplayerFeature
{
    DECLARE_SERIAL(CYCRetangleFeature)

public :
    CYCRetangleFeature();
    CYCRetangleFeature(const RECT &AValue);
    CYCRetangleFeature(int AX, int AY, int AWidth, int AHeight);

    inline const CRect& Rect() const
    { return m_Rect; };

    void SetRect(const RECT &AValue);
    void SetRect(int AX, int AY, int AWidth, int AHeight);

    inline int Width() const
    { return m_Rect.Width(); };

    void SetWidth(int AValue);

    inline int Height() const
    { return m_Rect.Height(); };

    void SetHeight(int AValue);

    inline CPoint Center() const
    { return m_Rect.CenterPoint(); };

    void SetCenter(const POINT &AValue);
    void SetCenter(const CPoint &AValue);

    void OffsetCenter(const POINT &AValue);
    void OffsetCenter(const CPoint &AValue);

    OVERRIDE_CYCBMPDisplayerFeature_Draw();

private:
    CRect       m_Rect;

};
//
// CYCRetangleFeature
///////////////////////////////////////////////////

class CYCCircleFeature : public CYCBMPDisplayerFeature
{

};

class CYCPolyLineFeature : public CYCBMPDisplayerFeature
{

};

class CYCPolygonFeature : public CYCBMPDisplayerFeature
{

};

class CYCCrossFeature : public CYCBMPDisplayerFeature
{
    DECLARE_SERIAL(CYCCrossFeature)

public:
    CYCCrossFeature();

    inline const POINT& Center() const
    { return m_Center; };

    void SetCenter(const POINT &AValue);
    void SetCenter(int AX, int AY);

    inline int Width()
    { return m_Width; };

    void SetWidth(int AValue);

    inline int Height()
    { return m_Height; };

    void SetHeight(int AValue);
    void SetWidthHeight(int AWidth, int AHeight);

    OVERRIDE_CYCBMPDisplayerFeature_Draw();

private:
    POINT       m_Center;
    int         m_Width;
    int         m_Height;

};


class CYCTextFeature : public CYCBMPDisplayerFeature
{
    DECLARE_SERIAL(CYCTextFeature)

public:
    CYCTextFeature();

    inline LPCSTR Text() const
    { return m_Text; }

    inline void SetText(LPCSTR AValue)
    { if (AValue && strcmp(m_Text, AValue) != 0) { m_Text = AValue; Update(); }; }

    inline const RECT& Rect() const
    { return m_Rect; }

    void SetRect(const RECT &AValue);
    inline void SetRect(int ALeft, int ATop, int AWidth, int AHeight)
    { SetRect(CRect(ALeft, ATop, ALeft + AWidth, ATop + AHeight)); }


    OVERRIDE_CYCBMPDisplayerFeature_Draw();

private:
    CRect       m_Rect;
    CString     m_Text;

};



class CYCReticleFeature : public CYCBMPDisplayerFeature
{
    DECLARE_SERIAL(CYCReticleFeature)

public:
    CYCReticleFeature();

    OVERRIDE_CYCBMPDisplayerFeature_Draw();

};



class CYCMousePointTextFeature : public CYCTextFeature
{
    DECLARE_SERIAL(CYCMousePointTextFeature)

public:
    CYCMousePointTextFeature();

    inline const POINT& Point() const
    { return m_Point; }

    void SetPoint(const POINT& AValue);
    inline void SetPoint(int AX, int AY)
    { SetPoint(CPoint(AX, AY)); }

private:
    POINT   m_Point;

};



class CYCBMPDisplayer : public CWnd
{
    friend class CYCReticleFeature;

    DECLARE_DYNAMIC(CYCBMPDisplayer)

public:
    //////////////////////////////////////////////
    // Data type
    //
    // ��ܩ�Popup menu�W������
    enum enmMenuItem
    {
        miNone                      = 0x00000000,
        miShowReticle               = 0x00000001,
        miShowSelectedAreaReticle   = 0x00000002,
        miShowMousePoint            = 0x00000004,
        miZoom                      = 0x00000100,
        miMoveBMPVisibleArea        = 0x00000200,
        miSelectArea                = 0x00000400,
        miSelectLine                = 0x00000800,
        miAll                       = 0xFFFFFFFF
    };

    typedef DWORD       enmMenuItems;


    // �i����ϥΪ��ﶵ
    enum enmOption
    {
        opNone                          = 0x0000,
        opReticleVisible                = 0x0001,
        opSelectedAreaReticleVisible    = 0x0002, // ��ܪ��F��
        opBMPVisibleAreaMovable         = 0x0100,
        opAreaSelectable                = 0x0200,
        opLineSelectable                = 0x0400,
        opZoomable                      = 0x0800, // �i�i�檺�ʧ@
        opSelectVLine                   = 0x1000,
        opSelectHLine                   = 0x2000
    };

    typedef DWORD       enmOptions;

    // �ثe���ʧ@               
    enum enmUserOperation
    {
        uoNone = 0,
        uoMoveBMPVisibleArea,
        uoSelectArea,
        uoSelectLine
    };


    // ��ܷƹ��y�Ц�m
    enum enmShowMousePointOption
    {
        smpNone,
        smpLeftTop,
        smpTop,
        smpRightTop,
        smpLeftBottom,
        smpBottom,
        smpRightBottom
    };
    //
    // Data type
    //////////////////////////////////////////////


    CYCBMPDisplayer();
    virtual ~CYCBMPDisplayer(void);

    // property
    inline enmMenuItems VisibleMenuItems() const
    { return m_VisibleMenuItems; }

    inline void SetVisibleMenuItems(enmMenuItems AValue) // AValue is one or more value of enmMenuItem
    { m_VisibleMenuItems = AValue; }

    //
    inline enmOptions Options() const
    { return m_Options; }

    void SetOptions(enmOptions AValue);

    //
    inline bool IsReticleVisible() const
    { return (m_Options & opReticleVisible) == opReticleVisible; }

    void SetIsReticleVisible(bool AValue);

    //
    inline bool IsSelectedAreaReticleVisible() const
    { return (m_Options & opSelectedAreaReticleVisible) == opSelectedAreaReticleVisible; }

    void SetIsSelectedAreaReticleVisible(bool AValue);

    //
    inline bool IsBMPVisibleAreaMovable() const
    { return (m_Options & opBMPVisibleAreaMovable) == opBMPVisibleAreaMovable; }

    void SetIsBMPVisibleAreaMovable(bool AValue);

    //
    inline bool IsAreaSelectable() const
    { return (m_Options & opAreaSelectable) == opAreaSelectable; }

    void SetIsAreaSelectable(bool AValue);

    // 
    inline bool IsLineSelectable() const
    { return (m_Options & opLineSelectable) == opLineSelectable; }

    void SetIsLineSelectable(bool AValue);

    //
    inline bool IsZoomable() const
    { return (m_Options & opZoomable) == opZoomable; }

    void SetIsZoomable(bool AValue);

    //
    inline double ZoomRate() const
    { return m_ZoomRate; }

    void SetZoomRate(double AValue);

    //
    inline double ZoomRateStep() const
    { return m_ZoomRateStep; }

    inline void SetZoomRateStep(double AValue)
    { m_ZoomRateStep = AValue; }

    //    
    inline int MaxSelectedAreasCount() const
    { return m_MaxSelectedAreasCount; }

    void SetMaxSelectedAreasCount(int AValue);

    //
    inline int MaxSelectedLinesCount() const
    { return m_MaxSelectedLinesCount; }

    void SetMaxSelectedLinesCount(int AValue);

    //
    inline double PixelRealWidthuM() const
    { return m_BMP.PixelRealWidthuM; }

    void SetPixelRealWidthuM(double AValue);

    //
    inline double PixelRealHeightuM() const
    { return m_BMP.PixelRealHeightuM; }

    void  SetPixelRealHeightuM(double AValue);

    //
    inline enmUserOperation ActiveUserOperation() const
    { return m_ActiveUserOperation; }

    void SetActiveUserOperation(enmUserOperation AValue);

    //
    inline CSize BMPSize() const
    { return CSize(m_BMP.RawWidth(), m_BMP.RawHeight()); }

    inline void  SetBMPSize(const SIZE &ASize)
    { SetBMPSize(ASize.cx, ASize.cy); }

    void SetBMPSize(int AWidth, int AHeight);

    //
    SIZE ClientSize() const;

    inline const CRect& BMPVisibleWindow() const
    { return m_BMP.VisibleArea; }

    inline const CRect& UIVisibleWindow() const
    { return m_UIBuff.DrawArea; }

    //
    inline enmShowMousePointOption  ShowMousePointOption() const
    { return m_ShowMousePointOption; }

    void SetShowMousePointOption(enmShowMousePointOption AValue);

    //
    inline IYCBMPDisplayerEventSinker *EventSinker() const
    { return m_EventSinker; }

    inline void SetEventSinker(IYCBMPDisplayerEventSinker *AValue)
    { m_EventSinker = AValue; }



    //////////////////////////////////////////////////
    // working
    //
    //
    inline void BeginUpdate()
    { m_UpdateCount ++; }

    void EndUpdate();

    //
    void BMPFitUISize(); // �վ�BMP�j�p���ŦXUI���ئT
    void UIFitBMPSize(); // �վ�UI�j�p���ŦXbmp���ئT

    //
    void MoveBMPVisibleAreaCenterTo(enmYCLayout ALayout);
    void MoveBMPVisibleAreaCenterTo(const POINT &APoint);
    void MoveBMPVisibleAreaCenterTo(long AX, long AY);

    void ShowBMPBMP(void *ABMP, int ABMPSize); // ABMP size must be >= (YCWidthToBmpWidth(BMPSize().cx) * BMPSize().cy
    void ShowBMPRaw(void *ABMP, int ABMPSize); // ABMP size must be >= BMPSize().cx * BMPSize().cy
    void ClearBMPData();
    void ReadBMPBMP(OUT void *ABMP, IN int ABMPSize) const;
    void ReadBMPRaw(OUT void *ABMP, IN int ABMPSize) const;

    inline int SelectedAreasCount() const
    { return (int)m_BMP.SelectedAreas.size(); }

    inline const CRect& SelectedAreaAt(int AIdx) const
    { return m_BMP.SelectedAreas[AIdx]; } // BMP coor

    inline CSize SelectedAreaSize(int AIdx) const // BMP coor
    { return m_BMP.SelectedAreas[AIdx].Size(); }

    inline CSize SelectedAreaSize() const
    { return SelectedAreaSize(0); } // BMP coor

    int   AppendSelectedArea(const CRect &AArea);
    void  InsertSelectedArea(int AIdx, const CRect &AArea);
    void  SetSelectedArea(int AIdx, const CRect &AArea);
    long  ReadSelectedDataBMP(OUT void *ABuff, int ABuffSize, int ASelectedIdx = 0) const; // ABuff size must be >= (YCWidthToBmpWidth(SelectedAreaSize().cx) * SelectedAreaSize().cy
    long  ReadSelectedDataRaw(OUT void *ABuff, int ABuffSize, int ASelectedIdx = 0) const; // ABuff size must be >= SelectedAreaSize().cx * SelectedAreaSize().cy
    long  ReadRow(OUT void *ABuff, int ABuffSize, int ARowIdx) const;
    long  ReadCol(OUT void *ABuff, int ABuffSize, int AColIdx) const;
    void  ClearSelectedAreas();

    inline int SelectedLinesCount() const
    { return (int)m_BMP.SelectedLines.size(); }

    inline const CYCLine& SelectedLineAt(int AIdx) const
    { return m_BMP.SelectedLines[AIdx]; }

    int    AppendSelectedLine(const CYCLine &ALine);
    void   InsertSelectedLine(int AIdx, const CYCLine &ALine);
    void   SetSelectedLine(int AIdx, const CYCLine &ALine);
    double LineLengthAt(int AIdx);
    void   ClearSelectedLines();

    bool  SaveDisplayerImage(LPCSTR AFileName, bool AIsForceDir = true);
    bool  SaveImage(LPCSTR AFileName, bool AIsForceDir = true);

    long  BMPToClient(const long  ABMPLength) const;
    POINT BMPToClient(const POINT &ABMPPoint) const;
    SIZE  BMPToClient(const SIZE  &ABMPSize) const;
    RECT  BMPToClient(const RECT  &ABMPRect) const;
    long  ClientToBMP(const long  AClientLength) const;
    POINT ClientToBMP(const POINT &AClientPoint) const;
    SIZE  ClientToBMP(const SIZE  &AClientSize) const;
    RECT  ClientToBMP(const RECT  &AClientRect) const;

    inline int  FeatureCount() const
    { return static_cast<int>(m_Features.size()); }

    CYCBMPDisplayerFeature* FeatureAt(int AIdx)
    { return (CYCBMPDisplayerFeature *)m_Features[AIdx]; }

    int         AddFeature(CYCBMPDisplayerFeature *AFeature);
    bool        RemoveFeature(CYCBMPDisplayerFeature *AFeature);
    void        DeleteFeature(int AIdx);
    void        UpdateFeature(CYCBMPDisplayerFeature *AFeature);

    afx_msg void OnDestroy();
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnPaint();

protected:
    ///////////////////////////////
    // Date Type / typedef
    //
    enum enmUpdateType
    {
        utReticle               = 0x00000001,
        utOperatingSelectedArea = 0x00000002,
        utAllSelectedAreas      = 0x00000004,
        utOperatingSelectedLine = 0x00000008,
        utAllSelectedLines      = 0x00000010,
        utMousePoint            = 0x00000020,
        utAll                   = 0xFFFFFFFF,
    };

    typedef DWORD       enmUpdateTypes;
    //
    // Date Type / typedef
    ///////////////////////////////


    void InitBMPInfoRW8();
    void UpdateUIBuff(enmUpdateTypes AUpdateType = utAll);
    void SyncUIBuff();
    inline bool IsInUpdating() const
    { return m_UpdateCount > 0; }

    void AdjAreaByZoomRate();
    void PaintToClient(CRect *AArea);

    void DoOnSelectArea();
    void DoOnClearSelectedAreas();
    void DoOnSelectedAreaSizing(int AIndex);
    void DoOnSelectedAreaSized(int AIndex);
    void DoOnZoom();
    void DoOnSelectLine();
    void DoOnClearSelectedLines();

    DECLARE_MESSAGE_MAP()

private:
    /////////////////////////////////////
    // DataBMP type / typedef
    //
    enum enmMouseAction
    {
        maNone,
        maSelectArea,
        maResizeLT,
        maResizeRT, 
        maResizeLB,
        maResizeRB,
        maResizeL,
        maResizeT,
        maResizeR,
        maResizeB,
        maMoveSelectedArea,
        maMoveBMPVisibleArea,
        maSelectLine
    };

    //
    // DataBMP type / typedef
    /////////////////////////////////////



    /////////////////////////////////////
    // Properties
    //
    // �i�H����ιB�@���\�঳���ǡA��enmOption
    enmOptions                  m_Options;

    // �i�H��ܩ�popup menu�W���\�঳���ǡA��enmMenuItem
    enmMenuItems                m_VisibleMenuItems;

    // �ثe����ܤ�v
    double                       m_ZoomRate;

    // �C���ۨϥ��Y��\��ɪ��W�[��֭�
    double                       m_ZoomRateStep;

    // �̦h�i������϶��ƶq
    int                         m_MaxSelectedAreasCount;

    // �̦h�i������u�ƶq
    int                         m_MaxSelectedLinesCount;

    // event sinker
    IYCBMPDisplayerEventSinker  *m_EventSinker;
    //
    // Properties
    /////////////////////////////////////



    /////////////////////////////////////
    // Working data
    // ��s������
    int                         m_UpdateCount;

    // UIBuff�O�_���ܰ�
    bool                        m_IsUIBuffChanged;

    // �ثe���檺�u�@
    enmUserOperation            m_ActiveUserOperation;

    // �ثe�ƹ����ʧ@
    enmMouseAction              m_ActiveMouseAction;

    // ��ܷƹ��y�Ъ��ﶵ
    enmShowMousePointOption     m_ShowMousePointOption;

    // �ƹ��y��(�y�Шt�ΡGbmp)
    //CPoint                      m_BMPMousePoint;

    // ����BMP��VisibleArea�ɩһݭn�Ψ쪺�Ѽ�
    struct strMovingBMPVisibleAreaParams
    {
        // �ƹ����U�k��ɪ���m
        CPoint  LBtnDownPos;

        // BMP����ܰϰ�
        CRect   BMPVisibleArea;

    } m_MovingBMPVisibleAreaParams;

    // BMP buffer(�s��bmp���������)
    struct strBMP
    {
        // Bmp������Y
        BITMAPINFO          *Info;

        // bmp��ƪ��Ȧs�ϡA��j�p��WidthToBMPWidth(m_BMP.Info->bmiHeader.biWidth) * m_BMP.Info->bmiHeader.biHeight
        BYTE                *DataBMP;

        // �O�_�����
        bool                DataValid;

        // �ثe����ܰϰ�
        CRect               VisibleArea;

        // bmp���C��pixel���u��width(in um)
        double               PixelRealWidthuM;

        // bmp���C��pixel���u��height(in um)
        double               PixelRealHeightuM;

        // �Q������ϰ�
        std::deque<CRect>   SelectedAreas;

        // �Q������u
        std::deque<CYCLine> SelectedLines;

        // �Q�ާ@������ϰ���ޭ�
        int                 OperatingSelectedAreaIdx;

        strBMP()
            : Info(NULL)
            , DataBMP(NULL)
            , DataValid(false)
            , VisibleArea(0, 0 , LONG_MAX, LONG_MAX)
            , PixelRealHeightuM(1)
            , PixelRealWidthuM(1)
            , OperatingSelectedAreaIdx(-1)
        {
        }

        ~strBMP()
        {
            if (Info)
                YCfree(Info);

            if (DataBMP)
                YCfree(DataBMP);
        }

        inline long RawWidth() const
        {
            if (Info)
                return Info->bmiHeader.biWidth;
            else return 0;
        }

        inline long RawHeight() const
        {
            if (Info)            
                return Info->bmiHeader.biHeight;
            else return 0;
        }

    } m_BMP;

    // dc double buffer (�s��uiø�Ͻw�İϪ����)
    struct strUIBuff
    {
        CDC         DC;
        CBitmap     Bitmap;

        // ¹�s���ϰ�
        CRect       DrawArea;

        // DrawDib...ø���ϥΪ�handle
        HDRAWDIB    DibHandle;

        inline strUIBuff()
        {
            DrawArea.SetRectEmpty();
        }

        inline long ClientWidth()
        {
            BITMAP  LBmp;

            Bitmap.GetBitmap(&LBmp);

            return LBmp.bmWidth;
        }

        inline long ClientHeight()
        {
            BITMAP  LBmp;

            Bitmap.GetBitmap(&LBmp);

            return LBmp.bmHeight;
        }

    } m_UIBuff;

#ifdef _DEBUG
    // ��ܲĴX�i�v��
    DWORD                               m_ShowBMPCount;
#endif

    CYCReticleFeature                   m_ReticleFeature;
    CYCMousePointTextFeature            m_MousePointTextFeature;

    // �ثe��feature
    CYCDeque<CYCBMPDisplayerFeature *>  m_Features;
    CYCDeque<CYCBMPDisplayerFeature *>  m_PrivateFeatures;

    bool PrepareResizeAreas(IN const CRect &ASelectedArea, OUT std::vector<CRect> *AResizeAreas);


protected:
    static BOOL m_IsClassRegistered;
    static char *m_ClassName;
    static BOOL RegisterThisClass();

    virtual void PreSubclassWindow();

};
