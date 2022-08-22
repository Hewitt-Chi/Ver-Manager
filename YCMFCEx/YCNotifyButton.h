#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

class CYCNotifyButton : public CButton
{
    DECLARE_DYNAMIC(CYCNotifyButton)

public:
    enum enmCMButton
    {
        CM_ButtonLButtonDown = (WM_USER + WM_LBUTTONDOWN),
        CM_ButtonLButtonUp   = (WM_USER + WM_LBUTTONUP),
        CM_ButtonMButtonDown = (WM_USER + WM_MBUTTONDOWN),
        CM_ButtonMButtonUp   = (WM_USER + WM_MBUTTONUP),
        CM_ButtonRButtonDown = (WM_USER + WM_RBUTTONDOWN),
        CM_ButtonRButtonUp   = (WM_USER + WM_RBUTTONUP),
    };

    struct strButtonUpDownNotification
    {
        UINT    Flags;
        CPoint  &Point;
    };


    CYCNotifyButton(void);
    virtual ~CYCNotifyButton(void);
    
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

protected:

    void SendNotifyMessageToParent(UINT AMessage, UINT AFlags, CPoint &APoint);

    DECLARE_MESSAGE_MAP()

};
