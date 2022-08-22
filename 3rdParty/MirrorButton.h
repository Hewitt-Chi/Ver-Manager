#if !defined(AFX_CMirrorButton_H__0D8AB689_E5ED_435A_84BB_787BA6DE7F8E__INCLUDED_)
#define AFX_CMirrorButton_H__0D8AB689_E5ED_435A_84BB_787BA6DE7F8E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CMirrorButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMirrorButton window
#define MIRROR_BTN_DOWN WM_USER+0x100
#define MIRROR_BTN_UP WM_USER+0x101

class CMirrorButton : public CButton
{
// Construction
public:
    CMirrorButton();

// Attributes
public:

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMirrorButton)
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CMirrorButton();

    // Generated message map functions
protected:
    //{{AFX_MSG(CMirrorButton)
        // NOTE - the ClassWizard will add and remove member functions here.
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMirrorButton_H__0D8AB689_E5ED_435A_84BB_787BA6DE7F8E__INCLUDED_)
