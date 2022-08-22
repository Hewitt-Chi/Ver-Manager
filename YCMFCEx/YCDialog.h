#pragma once


#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif


#define   VIRTUAL_CYCDialog_OnUpdateCommandUI()             virtual void OnUpdateCommandUI(CCmdUI *ACmdUI)
#define IMPLEMENT_CYCDialog_OnUpdateCommandUI(AClass)       void AClass::OnUpdateCommandUI(CCmdUI *ACmdUI)
#define  OVERRIDE_CYCDialog_OnUpdateCommandUI               VIRTUAL_CYCDialog_OnUpdateCommandUI


#define   VIRTUAL_CYCDialog_OnKickIdle()                    virtual LRESULT OnKickIdle(WPARAM wParam, LPARAM lParam)
#define IMPLEMENT_CYCDialog_OnKickIdle(AClass)              LRESULT AClass::OnKickIdle(WPARAM wParam, LPARAM lParam)
#define  OVERRIDE_CYCDialog_OnKickIdle                      VIRTUAL_CYCDialog_OnKickIdle


class CYCDialog : public CDialog
{
    DECLARE_DYNAMIC(CYCDialog)

public:
    CYCDialog(UINT AResId, CWnd* pParent = NULL);
#if 0
    CYCDialog(UINT AResId, LPCSTR ABackgroundFile, WORD AIconResId, CWnd* pParent = NULL);
#endif
    CYCDialog(UINT AResId, WORD ABackgroundResId, WORD AIconResId, CWnd* pParent = NULL);
    virtual ~CYCDialog();


    virtual void    PreSubclassWindow();
    virtual INT_PTR DoModal(); // override
    virtual BOOL    OnInitDialog();


    // �O�_�i����
    bool    IsClosable() const;
    void    SetIsClosable(bool AValue);


    // �O�_�i����
    bool    IsMovable() const;
    void    SetIsMovable(bool AValue);


    // �O�_�۰��Y�񱱨
    bool    IsAutoStretchChilds() const;
    void    SetIsAutoStretchChilds(bool AValue);


    // �]�w�I����
    void    SetBackgroundResID(WORD AValue);
    bool    LoadBackgroundImageFile(LPCSTR AFileName);


    // �b���Oactive�����p�U�O�_�n����UpdateDialogControls()
    bool    IsInactiveUDCsEnabled() const;
    void    SetIsInactiveUDCsEnabled(bool AValue);


    // 
    bool    IsToolTipsEnabled() const;
    void    SetIsToolTipsEnabled(bool AValue);

protected:
    short       m_BckgndOffsetX;
    short       m_BckgndOffsetY;
    bool        m_IsBkBmpIncludeNCArea;

    int         m_Width;
    int         m_Height;
    HICON       m_hIcon;
    CBitmap     m_BkBmp;

    LONG        m_StretchDlgClientWidth;
    LONG        m_StretchDlgClientHeight;


    // override
    virtual void    DoDataExchange(CDataExchange* pDX); // DDX/DDV support 
	virtual void    OnOK();
    virtual void    OnCancel();
	virtual void    PreInitDialog();

    afx_msg void    OnWindowPosChanged(WINDOWPOS* lpwndpos);
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg LRESULT OnNcHitTest(CPoint point);
    afx_msg BOOL    OnEraseBkgnd(CDC* pDC);
    afx_msg void    OnPaint();
    afx_msg void    WMUpdateCommandUI(CCmdUI *ACmdUI); 
    afx_msg LRESULT WMKickIdle(WPARAM wParam, LPARAM lParam); 
    afx_msg BOOL    WMNotifyTTNNeedText(UINT AId, NMHDR *ANMHDR, LRESULT *AResult);


    VIRTUAL_CYCDialog_OnUpdateCommandUI();
    VIRTUAL_CYCDialog_OnKickIdle();


    virtual void    OnCustomPaint(CDC *ADC)    {   } // �O�d


    DECLARE_MESSAGE_MAP()

private:
    bool    m_IsClosable;
    bool    m_IsMovable;
    bool    m_IsAutoStretchChilds;
    bool    m_IsInactiveUDCsEnabled;
    bool    m_IsToolTipsEnabled;


    //void    CreateBkDC(CDC *ADC);
    bool    PaintToDC(CDC *ADC);

};


extern void    YCStretchChild(CWnd *AWnd, float AScaleRateX, float AScaleRateY);
