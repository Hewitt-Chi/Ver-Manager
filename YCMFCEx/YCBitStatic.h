#pragma once

#ifdef __SHOW_Include_File
#pragma message("#include "__FILE__)
#endif

#if 0
#define __OLD_Paint

class CYCBitStatic3 : public CStatic
{
    DECLARE_DYNAMIC(CYCBitStatic3)

public:
    CYCBitStatic3();    
    virtual ~CYCBitStatic3();

    inline WORD BitmapResourceID() const
    { return LOWORD(m_BitmapResourceID); };

    void SetBitmapResourceID(WORD AId);

    inline bool IsBmpTransparent() const
    { return m_IsBmpTransparent; };

    void SetIsBmpTransparent(bool AValue);

    inline COLORREF BmpTransparentColor() const
    { return m_BmpTransparentColor; };

    void SetBmpTransparentColor(COLORREF AValue);

    inline bool AutoSize() const
    { return m_AutoSize; };

    void SetAutoSize(bool AValue);

    inline COLORREF BkColor() const
    { return m_BkColor; };

    void SetBkColor(COLORREF AValue);

    inline enmYCLayout Layout() const
    { return m_Layout; };

    void SetLayout(enmYCLayout AValue);

    // override;
    virtual void PreSubclassWindow();
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

    afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
#if 1
    afx_msg void OnPaint();
#endif
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
    CDC         m_IconDC;
    CBitmap     m_IconBmp;

    CDC     m_DBBmpDC;
    CBitmap m_DBBmp;

    void CreateIconBmp();
    void DestroyIconBmp();

    DECLARE_MESSAGE_MAP()

private:
    CString     m_Text;

    DWORD       m_BitmapResourceID;
    bool        m_IsBmpTransparent;
    COLORREF    m_BmpTransparentColor;
    COLORREF    m_BkColor;
    bool        m_AutoSize;
    enmYCLayout   m_Layout;
#ifdef __OLD_Paint
    bool        m_IsPainting;
#endif

    CFont       m_Font;
};
#endif


class CYCBitStatic : public CStatic
{
    DECLARE_DYNAMIC(CYCBitStatic)

public:
    CYCBitStatic();    
    virtual ~CYCBitStatic();

    // icon的res id
    inline WORD BitmapResourceID() const
    { return LOWORD(m_BitmapResourceID); };

    void SetBitmapResourceID(WORD AId);

    // icon是否透明
    inline bool IsBmpTransparent() const
    { return m_IsBmpTransparent; };

    void SetIsBmpTransparent(bool AValue);

    // icon透明的顏色
    inline COLORREF BmpTransparentColor() const
    { return m_BmpTransparentColor; };

    void SetBmpTransparentColor(COLORREF AValue);

    // 背景顏色
    inline COLORREF BkColor() const
    { return m_BkColor; };

    void SetBkColor(COLORREF AValue);

    // Icon 放置的位置
    inline enmYCLayout Layout() const
    { return m_Layout; };

    void SetLayout(enmYCLayout AValue);


    // Font name
    inline LPCSTR FontName() const
    { return m_FontName; }

    inline void SetFontName(LPCSTR AValue)
    { m_FontName = AValue; }


    // font color
    inline COLORREF FontColor() const               { return m_FontColor; }
    inline void     SetFontColor(COLORREF AValue)   { m_FontColor = AValue; }


    // override;
    virtual void PreSubclassWindow();

protected:
    CBitmap     m_IconBmp;
    CBitmap     m_BkBmp;
    CString     m_Text;

    void CreateIconBmp();
    void DestroyIconBmp();

    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);

    DECLARE_MESSAGE_MAP()

private:

    DWORD       m_BitmapResourceID;
    bool        m_IsBmpTransparent;
    COLORREF    m_BmpTransparentColor;
    COLORREF    m_BkColor;
    enmYCLayout   m_Layout;
    CFont       m_Font;
    CString     m_FontName;
    COLORREF    m_FontColor;


    void CreateBkBmp();
};
