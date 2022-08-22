#pragma once


typedef void (CObject::*TYCListCtrlCellButtonClickEventFunc)(CObject *ASender, int ACellX, int ACellY);


struct strYCListCtrlCellButtonClickEvent
{
    CObject     *Sinker;

    TYCListCtrlCellButtonClickEventFunc
        /**/    EventFunc;


    strYCListCtrlCellButtonClickEvent() : Sinker(NULL), EventFunc(NULL)
    {
    }


    strYCListCtrlCellButtonClickEvent(CObject *AObject, TYCListCtrlCellButtonClickEventFunc  AEventFunc)
        : Sinker(AObject), EventFunc(AEventFunc)
    {
    }


    inline void operator()(CObject *ASender, int ACellX, int ACellY) const
    {
        if (Sinker && EventFunc)
            (Sinker->*EventFunc)(ASender, ACellX, ACellY);
    }
};


#define NewYCListCtrlCellButtonClickEvent(__Object, __EventFunc) \
    strYCListCtrlCellButtonClickEvent(__Object, static_cast<TYCListCtrlCellButtonClickEventFunc>(__EventFunc))


class CYCListCtrl : public CListCtrl
{
    DECLARE_DYNAMIC(CYCListCtrl)

public:
    enum enmCellType  { ctNormal, ctButton, ctCheck, ctCheckButton };


    strYCListCtrlCellButtonClickEvent
        /**/    m_ButtonClickEvent;


    CYCListCtrl();


    virtual void PreSubclassWindow();
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);



    int         RowHeight() const;
    void        SetRowHeight(int AValue);

    enmCellType CellType(int ACellX, int ACellY) const;
    void        SetCellType(int ACellX, int ACellY, enmCellType AValue);
    void        SetColumnCellType(int ACellX, enmCellType AValue);
    void        SetRowCellType(int ACellY, enmCellType AValue);

    bool        IsCellChecked(int ACellX, int ACellY) const;
    void        SetIsCellChecked(int ACellX, int ACellY, bool AValue);
    void        SetColumnIsCellChecked(int ACellX, bool AValue);
    void        SetRowIsCellChecked(int ACellY, bool AValue);

    bool        IsCellEnabled(int ACellX, int ACellY) const;
    void        SetIsCellEnabled(int ACellX, int ACellY, bool AValue);
    void        SetColumnIsCellEnabled(int ACellX, bool AValue);
    void        SetRowIsCellEnabled(int ACellY, bool AValue);

    COLORREF    CellBkColor(int ACellX, int ACellY) const;
    void        SetCellBkColor(int ACellX, int ACellY, COLORREF AValue);
    void        SetColumnCellBkColor(int ACellX, COLORREF AValue);
    void        SetRowCellBkColor(int ACellY, COLORREF AValue);

    COLORREF    CellTextColor(int ACellX, int ACellY) const;
    void        SetCellTextColor(int ACellX, int ACellY, COLORREF AValue);
    void        SetColumnCellTextColor(int ACellX, COLORREF AValue);
    void        SetRowCellTextColor(int ACellY, COLORREF AValue);

protected:
    virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	afx_msg void OnStyleChanging(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void MeasureItem(LPMEASUREITEMSTRUCT pMeasureItemStruct);
    afx_msg void OnNMCustomDraw(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnInsertitem(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnDeleteitem(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);



    DECLARE_MESSAGE_MAP()

private:
    typedef std::deque<enmCellType>     TCellTypeDeque;


    struct strCellData
    {
        enmCellType CellType;
        bool        IsEnabled;
        bool        IsChecked;
        COLORREF    BkColor;
        COLORREF    TextColor;
    };

    typedef std::deque<strCellData>     TCellDataDeque;


    //=======================================
    int         m_RowHeight;

    std::deque<TCellDataDeque>
        /**/    m_CellDatas;


    TCellTypeDeque
        /**/    m_ColCellTypes;


    POINT       m_LButtonDownCell;
    POINT       m_FocusedCell;


    static const strCellData&
        /**/    DefaultCellData();

    void        CellRectToCheckBoxItemRect(LPCRECT   ACellRect, LPRECT ACheckBoxRect);
    void        RedrawCell(int ACellX, int ACellY);
    void        RedrawColumn(int ACellX);
    void        RedrawRow(int ACellY);
    void        SetFocusedCell(const POINT &ACell);
    void        OffsetFocusedCell(int AOffsetX, int AOffsetY);
    void        GetThisSubItemRect(int ACellX, int ACellY, OUT CRect &ARect);
};


