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


    // 是否可關閉
    bool    IsClosable() const;
    void    SetIsClosable(bool AValue);


    // 是否可移動
    bool    IsMovable() const;
    void    SetIsMovable(bool AValue);


    // 是否自動縮放控制項
    bool    IsAutoStretchChilds() const;
    void    SetIsAutoStretchChilds(bool AValue);


    // 設定背景圖
    void    SetBackgroundResID(WORD AValue);
    bool    LoadBackgroundImageFile(LPCSTR AFileName);


    // 在不是active的情況下是否要執行UpdateDialogControls()
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


    virtual void    OnCustomPaint(CDC *ADC)    {   } // 保留


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
