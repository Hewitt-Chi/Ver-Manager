#if !defined(AFX_COLORBUTTON_H__0E800805_ED0D_4A78_A98E_2528F20D0B5C__INCLUDED_)
#define AFX_COLORBUTTON_H__0E800805_ED0D_4A78_A98E_2528F20D0B5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorButton window

class CColorButton : public CButton
{
// Construction
public:
    CColorButton();

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CColorButton)
    public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    //}}AFX_VIRTUAL

// Implementation
public:

    void SetTextColor(COLORREF color);  // Set Text color
    void SetBKColor(COLORREF color);    // Set Background color
    virtual ~CColorButton();
    DWORD SetIcon(int nIconIn, int nIconOut);
    DWORD SetIcon(HICON hIconIn, HICON hIconOut);


    afx_msg void OnMouseMove(UINT nFlags, CPoint point);

    // Generated message map functions
protected:
    COLORREF m_BKColor, m_TextColor;  
    //{{AFX_MSG(CColorButton)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG


    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBUTTON_H__0E800805_ED0D_4A78_A98E_2528F20D0B5C__INCLUDED_)
