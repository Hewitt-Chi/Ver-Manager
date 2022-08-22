// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CColorButton

CColorButton::CColorButton()
{
    m_BKColor = ::GetSysColor(COLOR_BTNFACE);
    m_TextColor = ::GetSysColor(COLOR_BTNTEXT);
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
    //{{AFX_MSG_MAP(CColorButton)
        // NOTE - the ClassWizard will add and remove mapping macros here.
        ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    // TODO: Add your code to draw the specified item
    CString windowText;
    CDC dc;
    dc.Attach(lpDrawItemStruct->hDC);     //Get device context object
    CRect rt;
    rt = lpDrawItemStruct->rcItem;        //Get button rect

    dc.FillSolidRect(rt, m_BKColor); //Fill button with blue color
    this->GetWindowText(windowText);
    CString strTemp;
    GetWindowText(strTemp); // Get the caption which have been set
    dc.SetTextColor(m_TextColor);
    dc.DrawText(strTemp,rt,DT_CENTER|DT_VCENTER|DT_SINGLELINE); 
   UINT state = lpDrawItemStruct->itemState; //Get state of the button
   if ( (state & ODS_SELECTED) )            // If it is pressed
   {
     dc.DrawEdge(rt,EDGE_SUNKEN,BF_RECT);    // Draw a sunken face
   }
   else
   {
     dc.DrawEdge(rt,EDGE_RAISED,BF_RECT);    // Draw a raised face
   }

   if ( (state & ODS_FOCUS ) )       // If the button is focused
   {
    // Draw a focus rect which indicates the user 
    // that the button is focused
    dc.SetTextColor(0x000000);
    int iChange = 3;
    rt.top += iChange;
    rt.left += iChange;
    rt.right -= iChange;
    rt.bottom -= iChange;
    dc.DrawFocusRect(rt);
  }
  dc.Detach();
}

void CColorButton::SetBKColor(COLORREF color)
{
    m_BKColor = color;
}

void CColorButton::SetTextColor(COLORREF color)
{
    m_TextColor = color;
}

void CColorButton::OnMouseMove(UINT nFlags, CPoint point)
{
    if (nFlags==MK_LBUTTON)
    {
        //SetBKColor(0x00ff00);
        //RedrawWindow(); 
        
    }
    
    CButton::OnMouseMove(nFlags, point);
}
