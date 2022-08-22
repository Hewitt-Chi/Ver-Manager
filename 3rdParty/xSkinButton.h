#if !defined(AFX_MYB_H__3832DDEF_0C12_11D5_B6BE_00E07D8144D0__INCLUDED_)
#define AFX_MYB_H__3832DDEF_0C12_11D5_B6BE_00E07D8144D0__INCLUDED_

#if 0
#define CM_ButtonLButtonDown        (WM_USER + WM_LBUTTONDOWN)
#define CM_ButtonLButtonUp          (WM_USER + WM_LBUTTONUP)
#define CM_ButtonMButtonDown        (WM_USER + WM_MBUTTONDOWN)
#define CM_ButtonMButtonUp          (WM_USER + WM_MBUTTONUP)
#define CM_ButtonRButtonDown        (WM_USER + WM_RBUTTONDOWN)
#define CM_ButtonRButtonUp          (WM_USER + WM_RBUTTONUP)
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainApp.h : header file
/** 15/03/2001 v1.00
* ing.davide.pizzolato@libero.it
** 29/03/2001 v1.10
* Milan.Gardian@LEIBINGER.com
* - mouse tracking
** 02/04/2001 v1.20
* ing.davide.pizzolato@libero.it
* - new CreateRgnFromBitmap
** 14/04/2001 v1.21
* - OnMouseLeave cast fixed
* - Over bitmap consistency check
** 25/04/2001 v1.30
* Fable@aramszu.net
* - ExtCreateRegion replacement
** 24/06/2001 v1.40
* - check & radio button add on
* - added "focus" bitmap
* - fixed CreateRgnFromBitmap bug
* - fixed shortcut bug
** 27/10/2001 v1.41
* - fixed memory leakage in CreateRgnFromBitmap
*/

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

#define WM_CXSHADE_RADIO WM_USER+0x100
/////////////////////////////////////////////////////////////////////////////
// CxSkinButton window
class CxSkinButton : public CButton
{
    // Construction
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


    typedef struct strButtonUpDownNotification
    {
        UINT    Flags;
        CPoint  &Point;
    } TButtonUpDownNotification, *PstrButtonUpDownNotification;

    CxSkinButton();
    virtual ~CxSkinButton();

    void SetFont(LPCTSTR lpszFaceName, int nPointSize, BOOL bRedraw = TRUE);
    void SetFont(LOGFONT * pLogFont, BOOL bRedraw = TRUE);
    int  SetFontPosition(int nHPos, int nVPos);
    void SetToolTipText(CString s);
    COLORREF SetTextColor(COLORREF new_color);
    void SetSkin(UINT normal,UINT down, UINT over=0, UINT disabled=0, UINT focus=0,UINT mask=0,
        /**/    short drawmode=1,short border=1,short margin=4);

    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void PreSubclassWindow();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg BOOL OnClicked();
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
    afx_msg LRESULT OnRadioInfo(WPARAM, LPARAM);
    afx_msg LRESULT OnBMSetCheck(WPARAM, LPARAM);
    afx_msg LRESULT OnBMGetCheck(WPARAM, LPARAM);

protected:
    CFont        m_font;
    COLORREF    m_rgbText;
    COLORREF    m_rgbBackground;
    CBrush *    m_pBrush;
    BOOL        m_bBold;
    int            m_nXMargin;
    int         m_nYMargin;
    HICON        m_hIcon;
    int            m_nFormat;

#define FONT_CENTER        1    //水平置中
#define FONT_LEFT        2   //靠左
#define FONT_RIGHT        3   //靠右
#define FONT_VCENTER    4    //垂直置中
#define FONT_TOP        5   //靠上
#define FONT_BOTTOM        6   //靠下

    bool            m_Checked;                    //radio & check buttons
    DWORD            m_Style;                    //radio & check buttons
    bool            m_tracking;
    bool            m_button_down;
    CToolTipCtrl    m_tooltip;
    CBitmap         m_bNormal;
    CBitmap         m_bDown;
    CBitmap         m_bDisabled;
    CBitmap         m_bMask;
    CBitmap         m_bOver;
    CBitmap         m_bFocus; //skin bitmaps
    short            m_FocusRectMargin;        //dotted margin offset
    COLORREF        m_TextColor;            //button text color
    HRGN            m_hClipRgn;                //clipping region
    BOOL            m_Border;                //0=flat;1=3D;
    short            m_DrawMode;                //0=normal;1=stretch;2=tiled;

    void    RelayEvent(UINT message, WPARAM wParam, LPARAM lParam);
    HRGN    CreateRgnFromBitmap(HBITMAP hBmp, COLORREF color);
    void    FillWithBitmap(CDC* dc, HBITMAP hbmp, RECT r);
    void    DrawBitmap(CDC* dc, HBITMAP hbmp, RECT r, int DrawMode);
    int        GetBitmapWidth (HBITMAP hBitmap);
    int        GetBitmapHeight (HBITMAP hBitmap);
    void    SendNotifyMessageToParent(UINT AMessage, UINT AFlags, CPoint &APoint);


    DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
#endif // !defined(AFX_MYB_H__3832DDEF_0C12_11D5_B6BE_00E07D8144D0__INCLUDED_)
