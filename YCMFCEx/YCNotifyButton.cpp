#include "StdAfx.h"

#include "YCNotifyButton.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CYCNotifyButton, CButton)


CYCNotifyButton::CYCNotifyButton(void)
: CButton()
{
}

CYCNotifyButton::~CYCNotifyButton(void)
{
}


BEGIN_MESSAGE_MAP(CYCNotifyButton, CButton)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MBUTTONDOWN()
    ON_WM_MBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


void CYCNotifyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    CButton::OnLButtonDown(nFlags, point);

    SendNotifyMessageToParent(CM_ButtonLButtonDown, nFlags, point);
}

void CYCNotifyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    CButton::OnLButtonUp(nFlags, point);

    SendNotifyMessageToParent(CM_ButtonLButtonUp, nFlags, point);
}

void CYCNotifyButton::OnMButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    CButton::OnMButtonDown(nFlags, point);

    SendNotifyMessageToParent(CM_ButtonMButtonDown, nFlags, point);
}

void CYCNotifyButton::OnMButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    CButton::OnMButtonUp(nFlags, point);
    SendNotifyMessageToParent(CM_ButtonMButtonUp, nFlags, point);
}

void CYCNotifyButton::OnRButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    CButton::OnRButtonDown(nFlags, point);
    SendNotifyMessageToParent(CM_ButtonRButtonDown, nFlags, point);
}

void CYCNotifyButton::OnRButtonUp(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default
    CButton::OnRButtonUp(nFlags, point);

    SendNotifyMessageToParent(CM_ButtonRButtonUp, nFlags, point);
}

void CYCNotifyButton::SendNotifyMessageToParent(UINT AMessage, UINT AFlags, CPoint &APoint)
{
    CWnd *LParent = GetParent();

    if (LParent)
    {
        strButtonUpDownNotification     LNtfn = {AFlags, APoint};

        LParent->SendMessage(AMessage, (WPARAM)GetDlgCtrlID(), (LPARAM)&LNtfn);
    }
}
