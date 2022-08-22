// CMirrorButton.cpp : implementation file
//

#include "stdafx.h"
#include "MirrorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMirrorButton

CMirrorButton::CMirrorButton()
{
}

CMirrorButton::~CMirrorButton()
{
}

BEGIN_MESSAGE_MAP(CMirrorButton, CButton)
    //{{AFX_MSG_MAP(CMirrorButton)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMirrorButton message handlers


void CMirrorButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
    GetParent()->PostMessage(MIRROR_BTN_DOWN,GetDlgCtrlID());
    CButton::OnLButtonDown(nFlags, point);
}

void CMirrorButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
    GetParent()->PostMessage(MIRROR_BTN_UP,GetDlgCtrlID());
    CButton::OnLButtonUp(nFlags, point);
}