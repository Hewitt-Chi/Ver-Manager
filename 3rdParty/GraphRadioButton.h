#pragma once


// CGraphRadioButton

class CGraphRadioButton : public CButton
{
    friend CButtonST;

    DECLARE_DYNAMIC(CGraphRadioButton)

public:
    CGraphRadioButton();
    virtual ~CGraphRadioButton();

    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    virtual void PreSubclassWindow();

    DWORD SetIcon(int nIconIn, int nIconOut = NULL, int nIconDisable = NULL);
    DWORD SetIcon(HICON hIconIn, HICON hIconOut = NULL,HICON hIconDisable = NULL);

protected:
    DECLARE_MESSAGE_MAP()

    afx_msg void OnPaint();

private:
    typedef struct _STRUCT_ICONS
    {
        HICON        hIcon;            // Handle to icon
        DWORD        dwWidth;        // Width of icon
        DWORD        dwHeight;        // Height of icon
    } STRUCT_ICONS;

    STRUCT_ICONS    m_csIcons[3];

    void PrepareImageRect(BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, DWORD dwWidth, DWORD dwHeight, CRect* rpImage);    
    void DrawTheIcon(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpTitle);    
    void FreeResources(BOOL bCheckForNULL = TRUE);
    HICON CreateGrayscaleIcon(HICON hIcon);

};


