#if !defined(AFX_BMPBUTTON_H__3BF0180F_6B3B_42FD_AD9A_7A1C365E10AC__INCLUDED_)
#define AFX_BMPBUTTON_H__3BF0180F_6B3B_42FD_AD9A_7A1C365E10AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BmpButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBmpButton window

class CBmpButton : public CButton
{
    // Construction
public:
    CBmpButton();

    // Attributes
public:
    CBitmap Ebitmap, Dbitmap;
    BITMAP Ebmp, Dbmp;
    int EbmpHeight, EbmpWidth;
    int DbmpHeight, DbmpWidth;
    int ClickShift;
    UINT EnableBmpID, DisableBmpID;
    bool EnableBitmapLoad, DisableBitmapLoad, Transparent, EdgeOff;
    COLORREF crMask;

    // Operations
public:
    void SetTransparentColor(COLORREF color);    //set specific color to transparent
    bool LoadDisableBitmap(UINT ID);    //load bitmap(disable state)
    bool LoadBitmap(UINT ID);    //load bitmap(enable state)
    bool LoadBitmap(LPCSTR lpCursorName);

    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CBmpButton)
public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

    // Implementation
public:
    void SetEdgeOff();
    virtual ~CBmpButton();

    // Generated message map functions
protected:
    //{{AFX_MSG(CBmpButton)

    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    //}}AFX_MSG
    bool ReDrawBitmap(CDC *pDC, bool disable);

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMPBUTTON_H__3BF0180F_6B3B_42FD_AD9A_7A1C365E10AC__INCLUDED_)
